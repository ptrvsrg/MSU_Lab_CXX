#include "snake.h"

int main()
{
	setlocale(LC_ALL, "");
	int speed, location;
	cout << "Выберите уровень локации (1-3): ";
	cin >> location;
	cout << "Выберите уровень скорости (1-3): ";
	cin >> speed;

	run(location, speed);
	return 0;
}