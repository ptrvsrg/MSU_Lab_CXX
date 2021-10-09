//Петров Сергей
//Семинар 7, задача 18
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------------//
//////////////////////////////--- Структуры для ошибок ---//////////////////////////////
//------------------------------------------------------------------------------------//

struct error_file_not_open
{
	string file_name;
	error_file_not_open(string n_file_name) : file_name(n_file_name) {}
};

struct error_wrong_format
{
	string file_name;
	error_wrong_format(string n_file_name) : file_name(n_file_name) {}
};

struct error_repeating_number
{
	double x;
	error_repeating_number(double n_x) : x(n_x) {}
};

//---------------------------------------------------------------------------------------//
//////////////////////////////--- Структура для координат ---//////////////////////////////
//---------------------------------------------------------------------------------------//

struct coordinate
{
	double X, Y;
};

//-----------------------------------------------------------------------------------------------------//
//////////////////////////////--- Функция сравнения для сортировки по Х ---//////////////////////////////
//-----------------------------------------------------------------------------------------------------//

bool sort_x(coordinate a1, coordinate a2)
{
	return a1.X < a2.X;
}

//------------------------------------------------------------------------------------------------//
//////////////////////////////--- Унарный предикат для поиска по Х ---//////////////////////////////
//------------------------------------------------------------------------------------------------//

struct find_x
{
	double x;

	find_x(double nx) : x(nx) {}

	bool operator () (const coordinate& src) const
	{
		return src.X == x;
	}
};

//---------------------------------------------------------------------------------//
//////////////////////////////--- Требуемая функция ---//////////////////////////////
//---------------------------------------------------------------------------------//

double function(double x, string file_name)
{
	vector <coordinate> massive;
	coordinate A;
	string line;
	double temp;
	ifstream file_in(file_name);
	stringstream line_in;

	//////////////////////////////--- Проверка исключений ---//////////////////////////////

	if (!file_in.is_open())
		throw error_file_not_open(file_name);

	while (!file_in.eof()) 
	{
		getline(file_in, line);
		int count_numbers = 0;
		line_in << line;

		while (line_in >> temp)
			count_numbers++;

		line_in.clear();

		if (count_numbers != 0 && count_numbers != 2)
			throw error_wrong_format(file_name);
	}

	//////////////////////////////--- Считывание координат ---//////////////////////////////

	file_in.seekg(0, ios_base::beg);

	while (!file_in.eof())
	{
		file_in >> A.X >> A.Y;
		massive.push_back(A);
	}

	//////////////////////////////--- Проверка исключений ---//////////////////////////////

	for (int i = 0; i < massive.size(); i++)
	{
		if (count_if(massive.begin(), massive.end(), find_x(massive[i].X)) != 1)
			throw error_repeating_number(massive[i].X);
	}

	//////////////////////////////--- Сортировка по Х ---//////////////////////////////

	sort(massive.begin(), massive.end(), sort_x);

	//////////////////////////////--- Поиск Y при существующем Х ---//////////////////////////////

	if (find_if(massive.begin(), massive.end(), find_x(x)) != massive.end())
		return (*find_if(massive.begin(), massive.end(), find_x(x))).Y;

	//////////////////////////////--- Поиск Y при помощи интер- и экстраполяции ---//////////////////////////////

	else
	{
		if (x < massive[0].X)
			return massive[0].Y + (massive[1].Y - massive[0].Y) * (x - massive[0].X) / (massive[1].X - massive[0].X);
		else if (x > massive[massive.size() - 1].X)
			return massive[massive.size() - 2].Y + (massive[massive.size() - 1].Y - massive[massive.size() - 2].Y) * (x - massive[massive.size() - 2].X) / (massive[massive.size() - 1].X - massive[massive.size() - 2].X);
		else
		{
			int i = 0;
			while (x > massive[i].X)
				++i;
			return massive[i - 1].Y + (massive[i].Y - massive[i - 1].Y) * (x - massive[i - 1].X) / (massive[i].X - massive[i - 1].X);
		}
	}

	//////////////////////////////--- Закрытие файла ---//////////////////////////////

	file_in.close();
}

//----------------------------------------------------------------------------//
//////////////////////////////--- Функция main ---//////////////////////////////
//----------------------------------------------------------------------------//

int main()
{
	try
	{
		setlocale(LC_ALL, "");
		double x;
		cout << "Введите Х: ";
		cin >> x;
		cout << "Y равно " << function(x, "1.txt") << endl;
	}
	catch (error_file_not_open x)
	{
		cerr << "Error 1: Ошибка при открытии файла " << x.file_name << endl;
	}
	catch (error_wrong_format x)
	{
		cerr << "Error 2: Данные в файле " << x.file_name << " записаны в неправильном формате!!!" << endl;
	}
	catch (error_repeating_number x)
	{
		cerr << "Error 3: Координата х = " << x.x << " повторяется в файле!!!" << endl;
	}
}