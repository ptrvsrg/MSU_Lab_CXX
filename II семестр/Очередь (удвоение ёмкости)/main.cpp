#include "queue.h"

int main()
{
	int number = 0, num_last = 0;
	int S;
	double item;
	setlocale(LC_ALL, "rus");
	cout << "Введите размер очереди: " << flush;
	cin >> S;

	if (allocate(S) == 1)
		return 1;
	while (number != 6)
	{
		num_last = number;
		cout << endl << "Выберете действие:\n1 - Добавить элемент очереди;\n2 - Получить элемент из очереди;\n3 - Удалить элемент из очереди;\n4 - Очистить память;\n5 - Вывести очередь на экран;\n6 - Выход;\nВаш выбор: " << flush;
		cin >> number;
		
		if (number == 4 && num_last == 4)
		{
			cout << "   Память уже очищена!\n" << flush;
		}
		else
		{
			switch (number)
			{
			case 1:
				cout << "   Введите элемент очереди: " << flush;
				cin >> item;

				if (push(item) == 1)
				{
					return 1;
				}

				break;
			case 2:
				top();
				break;
			case 3:
				pop();
				break;
			case 4:
				destruct();
				break;
			case 5:
				display();
				break;
			case 6:
				break;
			default:
				cout << "   Введите правильный номер действия.\n" << flush;
				break;
			}
		}
	}
	
}