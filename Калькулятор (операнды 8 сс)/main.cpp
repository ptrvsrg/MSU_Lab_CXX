#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int r1, r2, r3;
	char op, pr;

	try
	{
		cout << "Используйте следующие операнды при вводе чисел:\n\tДля 10 СС - d...\n\tДля 8 CC - o...\n\n";
		cout << "Введите r1: " << flush;
		pr = getche();
		if (pr == 'd')
			cin >> dec >> r1;
		else if (pr == 'o')
		{
			cin >> oct >> r1;

			if (!r1)
				throw "1 - неправильно введён r1!";
		}
		else
			throw "1 - неправильно введён r1!";

		cout << "Введите op: " << flush;
		cin >> op;

		cout << "Введите r2: " << flush;
		pr = getche();
		if (pr == 'd')
			cin >> dec >> r2;
		else if (pr == 'o')
		{
			cin >> oct >> r2;

			if (!r2)
				throw "2 - неправильно введён r2!";
		}
		else
			throw "2 - неправильно введён r2!";

		switch (op)
		{
		case'+': r3 = r1 + r2; break;
		case'-': r3 = r1 - r2; break;
		case'*': r3 = r1 * r2; break;
		case'/':
			if (r2 == 0)
			{
				throw "3 - деление на ноль!";
			}
			r3 = r1 / r2;
			break;
		default:
			throw "4 - неправильно введён арифметический знак!";
		}
	}
	catch (const char* x)
	{
		cerr << "\nОшибка №" << x << endl;
		exit(atoi(x));
	}

	cout << "Ответ: " << r1 << ' ' << op << ' ' << r2 << " = " << r3 << endl << flush;
	return 0;
}