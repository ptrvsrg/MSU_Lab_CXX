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
		cout << "Enter r1: " << flush;
		pr = getche();
		if (pr == 'd')
			cin >> dec >> r1;
		else if (pr == 'o')
		{
			cin >> oct >> r1;

			if (!r1)
				throw "Wrong r1!";
		}
		else
			throw "Wrong r1!";

		cout << "Enter op: " << flush;
		cin >> op;

		cout << "Enter r2: " << flush;
		pr = getche();
		if (pr == 'd')
			cin >> dec >> r2;
		else if (pr == 'o')
		{
			cin >> oct >> r2;

			if (!r2)
				throw "Wrong r2!";
		}
		else
			throw "Wrong r2!";

		switch (op)
		{
		case'+': r3 = r1 + r2; break;
		case'-': r3 = r1 - r2; break;
		case'*': r3 = r1 * r2; break;
		case'/':
			if (r2 == 0)
			{
				throw "Divide by zero";
			}
			r3 = r1 / r2;
			break;
		default:
			throw "Wrong operator";
		}
	}
	catch (const char* x)
	{
		cerr << x << endl;
		exit(atoi(x));
	}

	cout << "Ответ: " << r1 << ' ' << op << ' ' << r2 << " = " << r3 << endl << flush;
	return 0;
}