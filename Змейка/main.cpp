#include "snake.h"

int main()
{
	setlocale(LC_ALL, "");
	int speed, location;
	cout << "�������� ������� ������� (1-3): ";
	cin >> location;
	cout << "�������� ������� �������� (1-3): ";
	cin >> speed;

	run(location, speed);
	return 0;
}