#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct error_file_open
{
	string file_name;

	error_file_open(string pr_file_name)
	{
		file_name = pr_file_name;
	}
};

struct error_square
{
	string file_name;

	error_square(string pr_file_name)
	{
		file_name = pr_file_name;
	}
};

vector <double> reading_matrix_from_file(string file_name)
{
	ifstream file_in(file_name);

	if (!file_in.is_open())
		throw error_file_open(file_name);
	else
	{
		int count = 0, count_space = 0;
		double temp;
		char symbol;

		while (!file_in.eof())
		{
			file_in >> temp;
			count++;
		}

		file_in.seekg(0, ios::beg);
		file_in.clear();

		while (!file_in.eof())
		{
			file_in.get(symbol);
			if (symbol == ' ') 
				count_space++;
			if (symbol == '\n') 
				break;
		}

		if ((count_space + 1) != count / (count_space + 1))
			throw error_square(file_name);

		file_in.seekg(0, ios::beg);
		file_in.clear();
		vector <double> massive;

		for (int i = 0; i < count; i++)
		{
			file_in >> temp;
			massive.push_back(temp);
		}

		return massive;
	}
}

void function(string file_name_in1, string file_name_in2, string file_name_out)
{
	vector <double> MTR1 = reading_matrix_from_file(file_name_in1), MTR2 = reading_matrix_from_file(file_name_in2);
	ofstream file_out(file_name_out);
	int row1 = sqrt(MTR1.size()), row2 = sqrt(MTR2.size()), row_max = fmax(row1, row2);
	vector <double> MTR3(pow(row_max, 2));

	if (row1 < row2)
	{
		for (int i = 0; i < row1; i++)
			for (int j = 0; j < row2 - row1; j++)
				MTR1.insert(MTR1.begin() + row1 + row2 * i, 0);
		for (int i = 0; i < row2 * (row2 - row1); i++)
			MTR1.push_back(0);
	}

	if (row1 > row2)
	{
		for (int i = 0; i < row2; i++)
			for (int j = 0; j < row1 - row2; j++)
				MTR2.insert(MTR2.begin() + row2 + row1 * i, 0);
		for (int i = 0; i < row1 * (row1 - row2); i++)
			MTR2.push_back(0);
	}

	for (int i = 0; i < row_max; i++)
		for (int j = 0; j < row_max; j++)
		{
			double A, B;
			MTR3[i * row_max + j] = 0;
			for (int k = 0; k < row_max; k++)
			{
				A = MTR1[i * row_max + k];
				B = MTR2[k * row_max + j];
				MTR3[i * row_max + j] += A * B;
			}
		}

	for (int i = 0; i < row_max; i++)
	{
		for (int j = 0; j < row_max; j++)
			file_out << MTR3[i * row_max + j] << ' ';
		file_out << '\n';
	}
}

int main()
{
	try
	{
		setlocale(LC_ALL, "");
		function("1.txt", "2.txt", "3.txt");
	}
	catch (error_file_open x)
	{
		cerr << "Ошибка при открытии " << x.file_name << " !";
	}
	catch (error_square x)
	{
		cerr << "Матрица из файла " << x.file_name << " не квадратная!";
	}
}