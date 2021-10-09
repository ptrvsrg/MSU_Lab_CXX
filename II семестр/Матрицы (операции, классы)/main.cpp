#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>


#define null "0"
#define identity "1"


using namespace std;

struct error_file_not_open
{
	string file_name;
	error_file_not_open(string n_file_name) : file_name(n_file_name) {}
};


struct error_initialization1
{
	int r, c;
	error_initialization1(int nr, int nc) : r(nr), c(nc) {}
};


struct error_initialization2
{
	string Category;
	error_initialization2(string nCategory) : Category(nCategory) {}
};


struct error_multiplication
{
	int r, c;
	error_multiplication(int nr, int nc) : r(nr), c(nc) {}
};


struct error_non_existence
{
	int i;
	error_non_existence(int m_i): i(m_i) {}
};


struct error_insert
{
	int i, j;
	error_insert(int m_i, int m_j) : i(m_i), j(m_j) {}
};

class Matrix : public vector <double>
{
private:

	int row;

public:

	Matrix(void): vector(0), row(0) {}


	Matrix(int r, int c, string Category) : vector(r * c), row(r)
	{
		if (Category == null)
			for (int i = 0; i < r; i++)
				for (int j = 0; j < column(); j++)
					data()[i * column() + j] = 0;
		else if (Category == identity)
			for (int i = 0; i < r; i++)
				data()[i * column() + i] = 1;
		else if(r<0 || c<0)
			throw error_initialization1(r, c);
		else
			throw error_initialization2(Category);
	}

	
	Matrix(int r, int c) : vector(r*c), row(r)
	{
		if (r < 0 || c < 0)
			throw error_initialization1(r, c);
	}


	Matrix(int n_row, vector <double> res) : vector(res), row(n_row)
	{
		if (res.size() % row != 0)
			throw "Wrong matrix data";
	}

	Matrix(const Matrix& temp) : row(temp.row), vector(temp) {}

	int row1() const
	{
		return row;
	}

	int column() const
	{
		return size() / row;
	}

    bool check_square()
	{
		return row == column();
	}

	bool check_diagonal()
	{
		bool control = true;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				if (i != j)
					if (data()[i * column() + j] != 0)
						control = false;
		return (control && check_square());
	}

	bool check_identity()
	{
		bool control = true;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				if (i == j)
					if (data()[i * column() + j] != 1)
						control = false;
		return (control && check_diagonal());
	}

	bool check_upper_triangular()
	{
		bool control = true;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				if (i > j)
					if (data()[i * column() + j] != 0)
						control = false;
		return control;
	}

	bool check_lower_triangular()
	{
		bool control = true;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				if (i < j)
					if (data()[i * column() + j] != 0)
						control = false;
		return control;
	}

	bool check_triangular()
	{
		return (check_lower_triangular() || check_upper_triangular());
	}

	vector <double>& operator [] (int index)
	{
		if (index < 0 || index >= row)
			throw error_non_existence(index);
		else
		{
			vector <double> res (begin() + index * column(), begin() + (index + 1) * column() - 1);
			return res;
		}
	}


	vector <double> operator [] (int index) const
	{
		if (index < 0 || index >= row)
			throw error_non_existence(index);
		else
		{
			vector <double> res(begin() + index * column(), begin() + (index + 1) * column() - 1);
			return res;
		}
	}

	Matrix operator+ (const Matrix& temp) const
	{
		int column_max = fmax(column(), temp.column()), row_max = fmax(row, temp.row);
		Matrix res(row_max, column_max);

		for (int i = 0; i < row_max; i++)
			for (int j = 0; j < column_max; j++)
			{
				if (i < fmin(row, temp.row) && j < fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = data()[i * column() + j] + temp.data()[i * temp.column() + j];

				if (i >= fmin(row, temp.row) && j >= fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = 0;

				if ((i < fmin(row, temp.row) && j >= fmin(column(), temp.column())) || (i >= fmin(row, temp.row) && j < fmin(column(), temp.column())))
				{
					if (data()[i * column() + j])
						res.data()[i * res.column() + j] = data()[i * column() + j];
					if (temp.data()[i * temp.column() + j])
						res.data()[i * res.column() + j] = temp.data()[i * temp.column() + j];
				}
			}

		return res;
	}

	Matrix& operator+= (const Matrix& temp)
	{
		int column_max = fmax(column(), temp.column()), row_max = fmax(row, temp.row);
		Matrix res(row_max, column_max);

		for (int i = 0; i < row_max; i++)
			for (int j = 0; j < column_max; j++)
			{
				if (i < fmin(row, temp.row) && j < fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = data()[i * column() + j] + temp.data()[i * temp.column() + j];

				if (i >= fmin(row, temp.row) && j >= fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = 0;

				if ((i < fmin(row, temp.row) && j >= fmin(column(), temp.column())) || (i >= fmin(row, temp.row) && j < fmin(column(), temp.column())))
				{
					if (data()[i * column() + j])
						res.data()[i * res.column() + j] = data()[i * column() + j];
					if (temp.data()[i * temp.column() + j])
						res.data()[i * res.column() + j] = temp.data()[i * temp.column() + j];
				}
			}

		*this = res;
		return *this;
	}

	Matrix operator- (const Matrix& temp) const
	{
		int column_max = fmax(column(), temp.column()), row_max = fmax(row, temp.row);
		Matrix res(row_max, column_max);

		for (int i = 0; i < row_max; i++)
			for (int j = 0; j < column_max; j++)
			{
				if (i < fmin(row, temp.row) && j < fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = data()[i * column() + j] - temp.data()[i * temp.column() + j];

				if (i >= fmin(row, temp.row) && j >= fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = 0;

				if ((i < fmin(row, temp.row) && j >= fmin(column(), temp.column())) || (i >= fmin(row, temp.row) && j < fmin(column(), temp.column())))
				{
					if (data()[i * column() + j])
						res.data()[i * res.column() + j] = data()[i * column() + j];
					if (temp.data()[i * temp.column() + j])
						res.data()[i * res.column() + j] = -temp.data()[i * temp.column() + j];
				}
			}
		return res;
	}

	Matrix& operator-= (const Matrix& temp)
	{
		int column_max = fmax(column(), temp.column()), row_max = fmax(row, temp.row);
		Matrix res(row_max, column_max);

		for (int i = 0; i < row_max; i++)
			for (int j = 0; j < column_max; j++)
			{
				if (i < fmin(row, temp.row) && j < fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = data()[i * column() + j] - temp.data()[i * temp.column() + j];

				if (i >= fmin(row, temp.row) && j >= fmin(column(), temp.column()))
					res.data()[i * res.column() + j] = 0;

				if ((i < fmin(row, temp.row) && j >= fmin(column(), temp.column())) || (i >= fmin(row, temp.row) && j < fmin(column(), temp.column())))
				{
					if (data()[i * column() + j])
						res.data()[i * res.column() + j] = data()[i * column() + j];
					if (temp.data()[i * temp.column() + j])
						res.data()[i * res.column() + j] = -temp.data()[i * temp.column() + j];
				}
			}

		*this = res;
		return *this;
	}

	Matrix operator* (double a) const
	{
		Matrix res(*this);

		for (int i = 0; i < res.row; i++)
			for (int j = 0; j < res.column(); j++)
				res.data()[i * res.column() + j] *= a;

		return res;
	}

	Matrix& operator* (double a)
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				data()[i * column() + j] *= a;

		return *this;
	}

	Matrix operator/ (double a) const
	{
		Matrix res(*this);

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				res.data()[i * res.column() + j] /= a;

		return res;
	}

	Matrix& operator/= (double a)
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column(); j++)
				data()[i * column() + j] /= a;

		return *this;
	}

	Matrix operator* (const Matrix& temp) const
	{
		if (temp.row != column())
			throw error_multiplication(temp.row, column());
		else
		{
			Matrix res(row, temp.column());
			int A, B;

			for (int i = 0; i < row; i++)\
				for (int j = 0; j < temp.column(); j++)
				{
					res.data()[i * res.column() + j] = 0;
					for (int k = 0; k < temp.row; k++)
					{
						A = data()[i * res.column() + k];
						B = temp.data()[k * res.column() + j];
						res.data()[i * res.column() + j] += A * B;
					}
				}

			return res;
		}
	}

	Matrix& operator*= (const Matrix& temp)
	{
		if (temp.row != column())
			throw error_multiplication(temp.row, column());
		else
		{
			Matrix res(row, temp.column());
			int A, B;

			for (int i = 0; i < row; i++)\
				for (int j = 0; j < temp.column(); j++)
				{
					res.data()[i * res.column() + j] = 0;
					for (int k = 0; k < temp.row; k++)
					{
						A = data()[i * res.column() + k];
						B = temp.data()[k * res.column() + j];
						res.data()[i * res.column() + j] += A * B;
					}
				}

			*this = res;
			return *this;
		}
	}

	double determinant()
	{
		if (!check_square())
			throw "Non-square matrix";
		else
		{
			switch (row)
			{
			case 1:
				return data()[0];
			case 2:
				return data()[0] * data()[3] - data()[1] * data()[2];
			default:
				int l, sum11 = 1, sum12 = 0, sum21 = 1, sum22 = 0;

				for (int i = 0; i < row; i++)
				{
					sum11 = 1; l = 2 * row - 1 - i; sum21 = 1;
					for (int j = 0; j < row; j++)
					{
						sum21 *= data()[j * column() + l % row];
						l--;
						sum11 *= data()[j * column() + (j + i) % (row)];
					}
					sum22 += sum21;
					sum12 += sum11;
				}

				return sum12 - sum22;
			}
		}
	}

	bool check_degeneracy()
	{
		if (check_square())
			return determinant() == 0;
		else
			return false;
	}

	Matrix trans()
	{
		Matrix res(column(), row);

		for (int i = 0; i < column(); i++)
			for (int j = 0; j < row; j++)
				res.data()[i * res.column() + j] = data()[j * column() + i];

		return res;
	}

	double tr()
	{
		if (!check_square())
			throw "Non-square matrix";
		else
		{
			double tr = 0;
			for (int i = 0; i < row; i++)
				tr += data()[i * column() + i];

			return tr;
		}
	}

	Matrix inverse()
	{
		if (!check_square())
			throw "Non-square matrix";
		else if(check_degeneracy())
			throw "Non-degeneracy matrix";
		else
		{
			Matrix res(row, column()), mas(row-1, column() - 1);

			for (int i = 0; i < row; i++)
				for (int j = 0; j < column(); j++)
				{
					int m = 0, n = 0;
					for (int k = 0; k < row; k++)
					{
						if (k != i)
						{
							for (int l = 0; l < column(); l++)
							{
								if (l != j)
								{
									mas.data()[m * mas.column() + n] = data()[k * column() + l];
									n++;
								}
							}

							m++;
						}
					}
					res.data()[i * res.column() + j] = pow(-1, i + j) * mas.determinant() / determinant();
				}
			cout << res;
			return res.trans();
		}
	}

	void insert_row(int index, vector<double> row1)
	{
		if (row1.size() == column())
		{
			if (index < 0)
				throw error_non_existence(index);
			else if (index < row)
			{
				insert(begin() + index * column(), row1.begin(), row1.end());
				row++;
			}
			else
			{
				insert(end(), row1.begin(), row1.end());
				row++;
			}
		}
		else
			throw error_insert(column(), row1.size());
	}

	void insert_column(int index, vector<double> column1)
	{
		if (column1.size() == row)
		{
			if (index < 0)
				throw error_non_existence(index);
			else if (index < row)
				for(int i = 0; i < row; i++)
					insert(begin() + index + i + i * column(), column1[i]);
			else
				for (int i = 0; i < row; i++)
					insert(begin() + i + (i + 1) * column(), column1[i]);
		}
		else
			throw error_insert(row, column1.size());
	}

	void erase_row(int index)
	{
		if (index < 0)
			throw error_non_existence(index);
		else if (index < row)
		{
			erase(begin() + index * column(), begin() + (index + 1) * column());
			row--;
		}
		else
		{
			erase(end() - column(), end());
			row--;
		}
	}

	void erase_column(int index)
	{
		if (index < 0)
			throw error_non_existence(index);
		else if (index < row)
		{
			int c = column();
			for (int i = row - 1; i >= 0; i--)
				erase(begin() + index + c * i);
		}
		else
		{
			int c = column();
			for (int i = row - 1; i >= 0; i--)
				erase(begin() + c * (i + 1) - 1);
		}
	}

	void push_back_row(vector<double> row1)
	{
		if (row1.size() == column())
		{
			insert(end(), row1.begin(), row1.end());
			row++;
		}
		else
			throw error_insert(column(), row1.size());
	}

	void push_back_column(vector<double> column1)
	{
		if (column1.size() == row)
		{
			for (int i = 0; i < row; i++)
				insert(begin() + i + (i + 1) * column(), column1[i]);
		}
		else
			throw error_insert(row, column1.size());
	}

	void pop_back_row()
	{
		erase(end() - column(), end());
		row--;
	}

	void pop_back_column()
	{
		int c = column();
		for (int i = row - 1; i >= 0; i--)
			erase(begin() + c * (i + 1) - 1);
	}

	void print_row(ostream& os, int index)
	{
		if (index < 0 || index >= row)
			throw error_non_existence(index);
		else
		{
			for(int i = 0; i < column(); i++)
				os << data()[index * column() + i] << ' ';
		}
	}

	void print_column(ostream& os, int index)
	{
		if (index < 0 || index >= row)
			throw error_non_existence(index);
		else
		{
			for (int i = 0; i < row; i++)
				os << data()[i * column() + index] << endl;
		}
	}

	vector<double> data1()
	{
		vector<double> a;
		a.insert(a.begin(), data(), data() + size() - 1);
		return a;
	}

	void swap1(Matrix& res)
	{
		swap(res);
	}

	void clear1()
	{
		clear();
		row = 0;
	}
	
	~Matrix()
	{
		clear1();
	}

	friend ostream& operator << (ostream& os, const Matrix& temp);
	friend istream& operator >> (istream& file_in, Matrix& res);
};

ostream& operator << (ostream& os, const Matrix& temp)
{
	for (int i = 0; i < temp.row; i++)
	{
		for (int j = 0; j < temp.column(); j++)
			os << temp.data()[i * temp.column() + j] << ' ';

		os << endl;
	}
	return os;
}


istream& operator >> (istream& is, Matrix& res)
{
	string line;
	double temp;
	stringstream line_in;
	int n_row = 0, n_column1, n_column2 = 0;
	vector <double> massive;
	
	while (!is.eof())
	{
		getline(is, line);
		n_column1 = 0;
		line_in << line;

		while (line_in >> temp)
			n_column1++;

		line_in.clear();

		if (n_column1 == 0)
			break;
		if (n_column2 != 0 && n_column1 != n_column2)
			throw "Wrong format of file";
		if (n_column1 != 0)
			n_row++;

		n_column2 = n_column1;
	}

	is.seekg(0, ios_base::beg);

	while (!is.eof())
	{
		is >> temp;;
		massive.push_back(temp);
	}

	Matrix res1(n_row, massive);
	res = res1;

	return is;
}

int main()
{
	try
	{
		setlocale(LC_ALL, "");

		ifstream file_in1("1.txt");
		ifstream file_in2("2.txt");

		vector<double> a;

		if (!file_in1.is_open())
			throw error_file_not_open("1.txt");
		if (!file_in2.is_open())
			throw error_file_not_open("2.txt");

		Matrix A, B;
		file_in1 >> A;
		file_in2 >> B;
		A.swap1(B);
		cout << B;
		return 0;
	}
	catch (string line)
	{
		cerr << line << endl;
	}
	catch (error_initialization1 x)
	{
		cerr << "Initialization error ( " << x.r << "; " << x.c << " )" << endl;
	}
	catch (error_initialization2 x)
	{
		cerr << "Initialization error " << x.Category << endl;
	}
	catch (error_multiplication x)
	{
		cerr << "Multiplication error " << x.r << " != " << x.c << endl;
	}
	catch (error_file_not_open x)
	{
		cerr << "File open error " << x.file_name << endl;
	}
	catch (error_non_existence x)
	{
		cerr << "Non-existence " << x.i << endl;
	}
}