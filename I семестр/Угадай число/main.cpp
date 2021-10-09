#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int answer = rand() % 1000000000000000001;
	int user_answer = 0;
	cout << "ИГРА ''УГАДАЙ ЧИСЛО''" << endl;
	while (user_answer != answer)
	{
		cout << "Введите свой ответ: ";
		cin >> user_answer;
		if (user_answer < answer)
			cout << "  БОЛЬШЕ" << endl;
		else
		{
			if (user_answer > answer)
				cout << "  МЕНЬШЕ" << endl;
			else
				cout << "  ПРАВИЛЬНЫЙ ОТВЕТ!!!";
		}
	}
	return 0;
}