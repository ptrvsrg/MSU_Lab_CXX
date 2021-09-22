#include "sudoku.h"

vector <char> POLE(169);
vector <char> COPY(81);
vector <char> ANS(81);
bool winner, running;
int mistake;
int cursorposx;
int cursorposy;
char value;

void filling()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			POLE[13 * i + j] = ' ';
		}
	}

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (j == 0 || j == 4 || j == 8 || j == 12)
			{
				POLE[13 * j + i] = 183;
				POLE[13 * i + j] = 183;
			}
		}
	}
}

void random()
{
	int num = 1;
	int a, b, x, y;
	srand(time(NULL));

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (num > 9)
				num -= 9;

			COPY[9 * i + j] = '0' + num;
			num++;
		}

		num += 3;
		if (num>9)
			num -= 9;
		if (i == 2 || i == 5)
			num++;
	}

	b = 1 + rand() % 100;
	for (int q = 0; q < b; q++)
	{
		int w = rand() % 2;

		a = 1 + rand() % 100;
		for (int i = 0; i < a; i++)
		{
			x = rand() % 3 * 3;
			y = 1 + rand() % 2 + x;

			for (int j = 0; j < 9; j++)
			{
				num = COPY[9 * x + j];
				COPY[9 * x + j] = COPY[9 * y + j];
				COPY[9 * y + j] = num;
			}
		}

		if (w == 0)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					ANS[9 * i + j] = COPY[9 * i + j];
				}
			}

			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					COPY[9 * j + i] = ANS[9 * i + j];
				}
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			ANS[9 * i + j] = COPY[9 * i + j];
		}
	}
}

void complication()
{
	setlocale(LC_ALL, "");
	int level, empty = 0, A[9];
	bool control;
	srand(time(NULL));
	cout << "Выберите сложность:\n  1 - лёгкий;\n  2 - средний;\n  3 - сложный;\n" << flush;

	while (empty == 0)
	{
		cin >> level;
		switch (level)
		{
		case 1:
			empty = 3;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					control = true;

					while (control)
					{
						int k = rand() % 9;
						if (A[k] != 3 && A[k] != 4 && A[k] != 5)
						{
							A[k] = empty;
							control = false;
						}
					}
				}
				empty++;
			}
			break;
		case 2:
			empty = 4;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					control = true;

					while (control)
					{
						int k = rand() % 9;
						if (A[k] != 4 && A[k] != 5 && A[k] != 6)
						{
							A[k] = empty;
							control = false;
						}
					}
				}
				empty++;
			}
			break;
		case 3:
			empty = 5;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					control = true;

					while (control)
					{
						int k = rand() % 9;
						if (A[k] != 5 && A[k] != 6 && A[k] != 7)
						{
							A[k] = empty;
							control = false;
						}
					}
				}
				empty++;
			}
			break;
		default:
			empty = 0;
			cout << "Неверно введён уровень!!!\n";
		}
	}

	cout << endl;
	int n = 0;
	for (int i = 0; i < 9; i += 3)
	{
		for (int j = 0; j < 9; j += 3)
		{
			for (int m = 0; m < A[n]; m++)
			{
				int k = rand() % 3, l = rand() % 3;
				if (COPY[9* (i + k) + j + l] != ' ')
					COPY[9 * (i + k) + j + l] = ' ';
			}
			n++;
		}
	}
}

void carry()
{
	int a = 0;
	for (int i = 1; i < 12; i++)
	{
		int b = 0;
		for (int j = 1; j < 12; j++)
		{
			while (i == 4 || i == 8)
				i++;

			while (j == 4 || j == 8)
				j++;

			if (COPY[9 * a + b] == ' ')
			{
				POLE[13 * i + j] = ' ';
			}
			else
			{
				POLE[13 * i + j] = COPY[9 * a + b];
			}
			b++;
		}
		a++;
	}
}

void printMap()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cout << POLE[13 * i + j] << " " << flush;
		}
		cout << "\n" << flush;
	}
}

void initMap()
{
	filling();
	random();
	complication();
	carry();
	mistake = 0;

	for (int i = 1; i < 13; i++)
	{
		for (int j = 1; j < 13; j++)
			if (POLE[13 * i + j] == ' ')
			{
				cursorposx = j;
				cursorposy = i;
				break;
			}

		if (cursorposy == i)
			break;
	}

	cursor();
}

void clearMap()
{
	system("cls");
}

void updateCursorPosition(char key)
{
	switch (key)
	{
	case 'w': 
		move(0, -1);
		break;
	case 'd':
		move(1, 0);
		break;
	case 's':
		move(0, 1);
		break;
	case 'a':
		move(-1, 0);
		break;
	case 'q':
		running = false;
		break;
	}

	if (key >= '1' && key <= '9' && value == ' ')
		answer(key);
}

void answer(char key)
{
	int x = cursorposx, y = cursorposy;

	if (x < 4)
		x--;
	else if (x > 4 && x < 8)
		x -= 2;
	else
		x -= 3;

	if (y < 4)
		y--;
	else if (y > 4 && y < 8)
		y -= 2;
	else
		y -= 3;

	if (ANS[9 * y + x] == key)
	{
		COPY[9 * y + x] = key;
		POLE[13 * cursorposy + cursorposx] = key;
		value = key;
		winner = false;

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (COPY[9 * i + j] != ANS[9 * i + j])
					winner = true;
	}
	else
		mistake++;
}

void move(int dx, int dy)
{
	POLE[13 * cursorposy + cursorposx] = value;
	cursorposx += dx;
	cursorposy += dy;

	if (cursorposx == 12)
		cursorposx = 1;
	if (cursorposx == 0)
		cursorposx = 11;
	if (cursorposx == 4 || cursorposx == 8)
		cursorposx += dx;
	if (cursorposy == 12)
		cursorposy = 1;
	if (cursorposy == 0)
		cursorposy = 11;
	if (cursorposy == 4 || cursorposy == 8)
		cursorposy += dy;

	cursor();
}

void cursor()
{
	value = POLE[13 * cursorposy + cursorposx];
	POLE[13 * cursorposy + cursorposx] = 30;
}

void run()
{
	initMap();
	winner = true;
	running = true;
	mistake = 0;

	while (winner && running && mistake != 3)
	{
		if (kbhit())
			updateCursorPosition(getch());
		clearMap();
		cout << "GAME BEGIN...\nNUMBER 0F MISTAKES IS " << mistake << endl;
		printMap();

		_sleep(200);
	}
	if (mistake == 3)
	{
		clearMap();
		cout << "GAME OVER\nYOU ARE LOSER\n";
		printMap(); 
		cout << "\nANSWER:";
		for (int i = 0; i < 9; i++)
		{
			cout << "\n";
			for (int j = 0; j < 9; j++)
				cout << ANS[9 * i + j] << " ";
		}
		cout << "\n";
	}
	if (!running)
	{
		clearMap();
		cout << "WHY DID YOU LEAVE THE GAME ?\nI AM OFFENDED\n";
		printMap();
	}
	if (!winner)
	{
		clearMap();
		cout << "YOU ARE WINNER!!!\nYOU ARE LORD OF SUDOKU!!!\n";
		printMap();
	}
}