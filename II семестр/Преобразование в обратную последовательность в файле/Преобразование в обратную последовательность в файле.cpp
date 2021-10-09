#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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

void function(string file_name_1, string file_name_2)
{
	vector <double> massive1, massive2;
	string line;
	double temp1, temp2;
	ifstream file_in(file_name_1);
	ofstream file_out(file_name_2);
	stringstream line_in;

	if (!file_in.is_open())
		throw error_file_not_open(file_name_1);

	while (!file_in.eof())
	{
		getline(file_in, line);
		int count_numbers = 0;
		line_in << line;

		while (line_in >> temp1)
			count_numbers++;

		line_in.clear();

		if (count_numbers != 0 && count_numbers != 2)
			throw error_wrong_format(file_name_1);
	}

	file_in.seekg(0, ios_base::beg);

	while (!file_in.eof())
	{
		getline(file_in, line);
		line_in << line;

		if (line_in >> temp1 >> temp2)
		{
			massive1.push_back(temp1);
			massive2.push_back(temp2);
		}

		line_in.clear();
	}

	massive1.insert(massive1.end(), massive2.begin(), massive2.end());

	reverse(massive1.begin(), massive1.end());

	for (int i = 0; i < massive1.size(); i++)
		file_out << massive1[i] << ' ';

	file_in.close();
	file_out.close();
}

int main()
{
	try
	{
		setlocale(LC_ALL, "");
		function("1.txt", "2.txt");
	}
	catch (error_file_not_open x)
	{
		cerr << "Error 1: Ошибка при открытии файла " << x.file_name << endl;
	}
	catch (error_wrong_format x)
	{
		cerr << "Error 2: Данные в файле " << x.file_name << " записаны в неправильном формате!!!" << endl;
	}
}
