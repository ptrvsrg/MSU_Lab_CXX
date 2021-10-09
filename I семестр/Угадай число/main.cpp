#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int answer = rand() % 101;
	int user_answer = 0;
	cout << "Game \"Guess the number\"" << endl;
	while (user_answer != answer)
	{
		cout << "Enter answer: ";
		cin >> user_answer;
		if (user_answer < answer)
			cout << "  more" << endl;
		else
		{
			if (user_answer > answer)
				cout << "  smaller" << endl;
			else
				cout << "  Right answer!!!";
		}
	}
	return 0;
}