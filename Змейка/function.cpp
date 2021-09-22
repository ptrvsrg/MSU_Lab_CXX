#include "snake.h"

// Размеры карты
int mapwidth = 20;
int mapheight = 20;

// Значения тайлов для карты
vector <int> map(mapwidth * mapheight);

// Детали головы змеи
int headxpos;
int headypos;
int direction;

// Количество пищи, которую имеет змея (Какова длина тела)
int food = 3;

// Определите, запущена ли игра
bool running;


// Основная игровая функция 
void run(int difficulty_location, int difficulty_speed)
{
	initMap(difficulty_location);
	running = true;
	int record = getRecord("record.txt", difficulty_location, difficulty_speed);

	while (running)
	{
		if (kbhit())
			changeDirection(getch());

		update();

		clearScreen();

		std::cout << "GAME PROCESSING\nCURRENT SCORE IS " << food << "\nCURRENT RECORD IS " << record << endl;

		printMap();

		switch (difficulty_speed)
		{
			case 1: 
				_sleep(400);
				break;
			case 2:
				_sleep(200);
				break;
			case 3:
				_sleep(100);
				break;
		}
		
	}

	if (food > record)
	{
		record = food;
		saveRecord("record.txt", difficulty_location, difficulty_speed, record);
		clearScreen();
		std::cout << "GAME OVER\nYOUR SCORE IS " << food << "\nNEW RECORD IS " << record << endl;
		printMap();
	}
	else
	{
		clearScreen();
		std::cout << "GAME OVER\nYOUR SCORE IS " << food << endl;
		printMap();
	}
	
}


// Изменяет направление змейки из ввода
void changeDirection(char key) 
{
	switch (key) 
	{
	case 'w':
		if (direction != 2) direction = 0;
		break;
	case 'd':
		if (direction != 3) direction = 1;
		break;
	case 's':
		if (direction != 0) direction = 2;
		break;
	case 'a':
		if (direction != 1) direction = 3;
		break;
	case ' ':
		clearScreen();
		std::cout << "PAUSE" << endl;
		printMap();
		if (getch() == ' ')
			break;
	case 'q':
		running = false;
		break;
	}
}


// Перемещает змеиную голову в новое место
void move(int dx, int dy) 
{
	int newx = headxpos + dx;
	int newy = headypos + dy;

	if (map[newx + newy * mapwidth] == -4) 
	{
		food++;
		generateFood();
	}
	else if (map[newx + newy * mapwidth] == -2)
	{
		if (newy == 0)
		{
			if (map[newx + (mapheight - 2) * mapwidth] == -4)
			{
				newy = mapheight - 2;
				food++;
				generateFood();
			}
			else if (map[newx + (mapheight - 2) * mapwidth] > 0 || map[newx + (mapheight - 2) * mapwidth] == -1)
				running = false;
			else
			{
				newy = mapheight - 2;
			}
		}
		else if (newy == mapheight - 1)
		{
			if (map[newx + mapwidth] == -4)
			{
				newy = 1;
				food++;
				generateFood();
			}
			else if (map[newx + mapwidth] > 0 || map[newx + mapwidth] == -1)
				running = false;
			else
			{
				newy = 1;
			}
		}
		else if (newx == 0)
		{
			if (map[mapwidth - 2 + newy * mapwidth] == -4)
			{
				newx = mapwidth - 2;
				food++;
				generateFood();
			}
			else if (map[mapwidth - 2 + newy * mapwidth] > 0 || map[mapwidth - 2 + newy * mapwidth] == -1)
				running = false;
			else
			{
				newx = mapwidth - 2;
			}
		}
		else if (newx == mapwidth - 1)
		{
			if (map[1 + newy * mapwidth] == -4)
			{
				newx = 1;
				food++;
				generateFood();
			}
			else if (map[1 + newy * mapwidth] > 0 || map[1 + newy * mapwidth] == -1)
				running = false;
			else
			{
				newx = 1;
			}
		}
	}
	else if (map[newx + newy * mapwidth] != 0)
		running = false;

	headxpos = newx;
	headypos = newy;
	map[headxpos + headypos * mapwidth] = food + 1;

}


// Очищает экран
void clearScreen() 
{
	system("cls");
}


// Создает новую еду на карте
void generateFood() 
{
	srand(time(NULL));
	int x = 0;
	int y = 0;

	do 
	{
		x = rand() % (mapwidth - 2) + 1;
		y = rand() % (mapheight - 2) + 1;
	} while (map[x + y * mapwidth] != 0);

	map[x + y * mapwidth] = -4;
}


// Обновляет карту
void update() 
{
	switch (direction) 
	{
	case 0: move(-1, 0);
		break;
	case 1: move(0, 1);
		break;
	case 2: move(1, 0);
		break;
	case 3: move(0, -1);
		break;
	}

	// Уменьшить значения змей на карте на 1
	for (int i = 0; i < map.size(); i++) 
	{
		if (map[i] > 0) map[i]--;
	}
}


// Инициализирует карту
void initMap(int difficulty_location)
{
	srand(time(NULL));

	do
	{
		headxpos = rand() % (mapwidth - 4) + 2;
		headypos = rand() % (mapheight - 4) + 2;
	} while (map[headxpos + headypos * mapwidth] != 0);

	map[headxpos + headypos * mapwidth] = 1;

	switch (difficulty_location)
	{
	case 1:
		for (int x = 1; x < mapwidth - 1; ++x)
		{
			map[x] = -2;
			map[x + (mapheight - 1) * mapwidth] = -2;
		}

		for (int y = 1; y < mapheight - 1; y++)
		{
			map[0 + y * mapwidth] = -2;
			map[(mapwidth - 1) + y * mapwidth] = -2;
		}

		break;
	case 2:
		for (int x = 0; x < mapwidth; ++x)
		{
			map[x] = -1;
			map[x + (mapheight - 1) * mapwidth] = -1;
		}

		for (int y = 0; y < mapheight; y++)
		{
			map[0 + y * mapwidth] = -1;
			map[(mapwidth - 1) + y * mapwidth] = -1;
		}

		break;
	case 3:
		for (int x = 0; x < mapwidth; ++x)
		{
			map[x] = -1;
			map[x + (mapheight - 1) * mapwidth] = -1;
		}

		for (int y = 0; y < mapheight; y++)
		{
			map[0 + y * mapwidth] = -1;
			map[(mapwidth - 1) + y * mapwidth] = -1;
		}

		for (int x = 3; x < mapwidth - 3; ++x)
			map[x + (mapheight/2) * mapwidth] = -1;

		for (int y = 3; y < mapheight - 3; y++)
			map[(mapwidth/2) + y * mapwidth] = -1;

		break;
	}

	// Создает первую пищу
	generateFood();
}


// Распечатывает карту на консоль
void printMap()
{
	for (int x = 0; x < mapwidth; ++x) 
	{
		for (int y = 0; y < mapheight; ++y)
			std::cout << getMapValue(map[x + y * mapwidth]) << " ";
		std::cout << endl;
	}
}


// Возвращает графический символ для отображения из значения карты
char getMapValue(int value)
{
	if (value > 0) 
		return 4;

	switch (value) 
	{
	case -1: 
		return 'X';
	case -2:
		return '.';
	case -4: 
		return '$';
	}

	return ' ';
}


// Считывание рекорда игры из файла
int getRecord(string file_name, int difficulty_location, int difficulty_speed)
{
	ifstream file_in(file_name);
	int record = 3;

	for (int i = 0; i < difficulty_speed - 1 + 3 * (difficulty_location - 1); i++)
		file_in >> record;

	file_in.close();

	return record;
}


// Запись рекорда игры в файл
void saveRecord(string file_name, int difficulty_location, int difficulty_speed, int value)
{
	fstream file(file_name);
	vector <int> massive;
	int record;

	for (int i = 0; i < 9; i++)
	{
		file >> record;
		massive.push_back(record);
	}

	file.seekg(0, ios::beg);
	massive[difficulty_speed - 1 + 3 * (difficulty_location - 1)] = value;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			file << massive[j + 3 * i] << ' ';
		file << endl;
	}

	file.close();
}