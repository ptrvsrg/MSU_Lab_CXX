// ������ ������
// �������������� �������
// ��� ��������� ������������ � ����: a1x1 + a2x2 + ... + aNxN + b = 0
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct error_initialization_Vector
{
	int m_i;
	error_initialization_Vector(int i)
	{
		m_i = i;
	}
};

struct error_initialization_Matrix
{
	int m_r, m_c;
	error_initialization_Matrix(int r, int c)
	{
		m_r = r;
		m_c = c;
	}
};

struct error_nonexistence
{
	double m_i;
	error_nonexistence(double i)
	{
		m_i = i;
	}
};

struct error_division_by_zero
{
	double m_i;
	error_division_by_zero(double i)
	{
		m_i = i;
	}
};

struct error_no_solution1
{
	error_no_solution1() {}
};

struct error_no_solution2
{
	int m_r, m_c;
	error_no_solution2(int r, int c)
	{
		m_r = r;
		m_c = c;
	}
};


//-------------------------------------------------------------------------------------------------//
//////////////////////////////--- ����� Vector - ����� ������-����� ---//////////////////////////////
//-------------------------------------------------------------------------------------------------//

class Vector
{
protected:
	double* var;
	unsigned int column;
public:

	//////////////////////////////--- ����������� ---//////////////////////////////

	Vector(int N = 0) : var(nullptr), column(N)
	{
		if (N < 0)
			throw error_initialization_Vector(N);
		else
		{
			var = new double[N];
		}
	}

	//////////////////////////////--- ����������� ����������� ---//////////////////////////////

	Vector(const Vector& res) : var(nullptr), column(res.column)
	{
		var = new double[column];

		for (int i = 0; i < column; i++)
			var[i] = res.var[i];
	}

	//////////////////////////////--- ��������[] ---//////////////////////////////

	double operator [] (int index) const
	{
		if (index < 0 || index >= column)
			throw error_nonexistence(index);
		else
			return var[index];
	}

	double& operator [] (int index)
	{
		if (index < 0 || index >= column)
			throw error_nonexistence(index);
		else
			return var[index];
	}

	//////////////////////////////--- �������� = ---//////////////////////////////

	Vector& operator= (Vector& temp)
	{
		delete[] var;
		column = temp.column;
		var = new double[column];

		for (int i = 0; i < column; i++)
			var[i] = temp.var[i];

		return *this;
	}
	
	//////////////////////////////--- �������� -= ---//////////////////////////////

	Vector& operator-= (Vector& temp)
	{
		for (int i = 0; i < column; i++)
			var[i] -= temp.var[i];
		return *this;
	}

	//////////////////////////////--- �������� /= ---//////////////////////////////

	Vector& operator/= (double a)
	{
		for (int i = 0; i < column; i++)
		{
			if (fabs(a) < 1.0E-10)
				throw error_division_by_zero(a);
			else
				var[i] /= a;
		}
		return *this;
	}

	//////////////////////////////--- ������������� ������� ---//////////////////////////////

	friend ostream& operator << (ostream& os, Vector& res);
	friend istream& operator >> (istream& is, Vector& res);
};


//-------------------------------------------------------------------------------------------//
//////////////////////////////--- ����� Matrix - ����� ������ ---//////////////////////////////
//-------------------------------------------------------------------------------------------//


class Matrix
{
protected:
	Vector* equ;
	unsigned int row;
	unsigned int column;

	//////////////////////////////--- ������� ��� ���������� ������� ������ � ������������ �� ������ � ������� ��������� ---//////////////////////////////

	unsigned int maximum(unsigned int index)
	{
		double max = fabs(equ[index][index]);
		unsigned int index_max = index;

		for (int i = index; i < row; i++)
			if (fabs(equ[i][index]) > fabs(max))
				index_max = i;

		return index_max;
	}

	//////////////////////////////--- ������� ��� ������������ ����� ---//////////////////////////////

	void permutation(unsigned int index_max, unsigned int index)
	{
		Vector a;
		a = equ[index_max];
		equ[index_max] = equ[index];
		equ[index] = a;
	}

	//////////////////////////////--- ������� ��� ������� ���� ����� �� ����� ---//////////////////////////////

	void division(unsigned int index)
	{
		for (int i = index; i < row; i++)
		{
			if (fabs(equ[i][index]) > 1.0E-10)
				equ[i] /= equ[i][index];
		}

	}

	//////////////////////////////--- ������� ��� ��������� ����������� ������ �� ���� ������ ---//////////////////////////////

	void subtraction(unsigned int index)
	{
		for (int i = index + 1; i < row; i++)
		{
			if (equ[i][index] != 0)
				equ[i] -= equ[index];
		}
	}

	//////////////////////////////--- ������� ��� �������� ������� ����� ---//////////////////////////////

	void delete_row()
	{
		bool control;
		int j;

		for (int i = 0; i < row; i++)
		{
			control = true;

			for (j = 0; j < column; j++)
			{
				if (equ[i][j] != 0)
					control = false;
			}

			if (control)
			{
				Vector* q;
				q = new Vector[row - 1];

				Vector A(column);
				for (int i = 0; i < row - 1; i++)
					q[i] = A;

				int l = 0;

				for (int k = 0; k < row; k++)
				{
					if (k != i)
					{
						q[l] = equ[k];
						l++;
					}
				}

				delete[] equ;
				row--;
				i--;
				equ = q;
			}
		}
	}

	//////////////////////////////--- ������� ��� ���������� ������� �������� ---//////////////////////////////

	bool find_column()
	{
		bool control = false;

		for (int i = 0; i < row; i++)
		{
			control = true;

			for (int j = 0; j < column; j++)
			{
				if (equ[i][j] != 0)
					control = false;
			}
		}

		return control;
	}

	//////////////////////////////--- ������� ��� ��������� ����������� ������� ---//////////////////////////////

	Matrix& triangle()
	{
		for (int i = 0; i < fmin(column, row) - 1; i++)
		{
			permutation(maximum(i), i);
			division(i);
			subtraction(i);
			cout << endl << *this << endl;
		}
		delete_row();
		division(fmin(column, row) - 1);
		cout << endl << *this << endl;
		return *this;
	}

public:

	//////////////////////////////--- ����������� ---//////////////////////////////

	Matrix(int nr = 0, int nc = 0) : equ(nullptr), row(nr), column(nc)
	{
		if (nr < 0 || nc < 0)
			throw error_initialization_Matrix(nr, nc);

		else
		{
			equ = new Vector[nr];

			Vector A(nc);
			for (int i = 0; i < nr; i++)
				equ[i] = A;
		}
	}

	//////////////////////////////--- ����������� ����������� ---//////////////////////////////

	Matrix(const Matrix& res) : equ(nullptr), row(res.row), column(res.column)
	{
		equ = new Vector[row];

		Vector A(column);
		for (int i = 0; i < row; i++)
			equ[i] = A;
	}

	//////////////////////////////--- �������� [] ---//////////////////////////////

	Vector operator [] (int index) const
	{
		if (index < 0 || index >= row)
			throw error_nonexistence(index);
		else
			return equ[index];
	}

	Vector& operator [] (int index)
	{
		if (index < 0 || index >= row)
			throw error_nonexistence(index);
		else
			return equ[index];
	}

	//////////////////////////////--- �������� = ---//////////////////////////////

	Matrix& operator = (const Matrix& res)
	{
		row = res.row;
		column = res.column;

		delete[] equ;
		equ = new Vector[row];

		Vector A(column);
		for (int i = 0; i < row; i++)
			equ[i] = A;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				equ[i][j] = res.equ[i][j];

		return *this;
	}

	//////////////////////////////--- ��������� ������� ������� ---//////////////////////////////

	Vector& solution()
	{
		triangle();

		if (find_column())
			throw error_no_solution1();
		else if (column - row != 1)
			throw error_no_solution2(row, column);
		else
		{
			static Vector solution(row);

			for (int i = column - 2; i >= 0; i--)
			{
				solution[i] = equ[i][column - 1];

				for (int j = i + 1; j < column - 1; j++)
					solution[i] -= equ[i][j] * solution[j];
			}

			return solution;
		}
	}

	//////////////////////////////--- ���������� ---//////////////////////////////

	~Matrix()
	{
		delete[] equ;
		row = 0;
	}

	//////////////////////////////--- ������������� ������� ---//////////////////////////////

	friend ostream& operator << (ostream& os, Matrix& res);
	friend istream& operator >> (istream& is, Matrix& res);
};


//////////////////////////////--- �������� << ---//////////////////////////////

ostream& operator << (ostream& os, Vector& res)
{
	for (int i = 0; i < res.column; i++)
		os << setw(5) << res.var[i] << ' ';

	return os;
}

ostream& operator << (ostream& os, Matrix& res)
{
	for (int i = 0; i < res.row; i++)
		os << setw(5) << res.equ[i] << '\n';

	return os;
}

// //////////////////////////////--- �������� >> ---//////////////////////////////

istream& operator >> (istream& is, Vector& res)
{
	double a;

	if (res.column == 0)
	{
		int i = 0, variables;
		cout << "������� ���������� �����������: ";
		cin >> variables;

		if (variables <= 0)
			throw error_initialization_Vector(variables);

		Vector res(variables + 1);

		for (int i = 0; i < res.column; i++)
		{
			if (i == res.column - 1)
			{
				cout << "������� ��������� ����: ";
				is >> a;
				res.var[i] = -a;
			}

			else
			{
				cout << "������� ����������� ��� �" << i + 1 << ": ";
				is >> a;
				res.var[i] = a;
			}
		}
	}

	else
	{
		for (int i = 0; i < res.column; i++)
		{
			if (i == res.column - 1)
			{
				cout << "������� ��������� ����: ";
				is >> a;
				res.var[i] = -a;
			}

			else
			{
				cout << "������� ����������� ��� �" << i + 1 << ": ";
				is >> a;
				res.var[i] = a;
			}
		}
	}

	return is;
}

istream& operator >> (istream& is, Matrix& res)
{
	if (res.row == 0)
	{
		int equations, variables;
		cout << "������� ���������� ���������: ";
		cin >> equations;
		cout << "������� ���������� �����������: ";
		cin >> variables;


		if (variables <= 0 || equations <= 0)
			throw error_initialization_Matrix(equations, variables);

		Matrix temp(equations, variables + 1);

		for (int i = 0; i < temp.row; i++)
		{
			cout << "\t������� " << i + 1 << " ���������:\n";
			is >> temp.equ[i];
		}

		res = temp;
	}

	else
	{
		for (int i = 0; i < res.row; i++)
		{
			cout << "\t������� " << i + 1 << " ���������:\n";
			is >> res.equ[i];
		}
	}

	return is;
}


//----------------------------------------------------------------------------//
//////////////////////////////--- ������� main ---//////////////////////////////
//----------------------------------------------------------------------------//

int main()
{
	try
	{
		setlocale(LC_ALL, "");
		Matrix A;
		cin >> A;
		cout << "\t�����: " << A.solution() << endl;;
	}
	catch (error_division_by_zero x)
	{
		cerr << "������� �� " << x.m_i << "�������������� ��� ������� �� ����!" << endl;
	}
	catch (error_initialization_Vector x)
	{
		cerr << "������ ���������������� ������ ���� Vector ������ ���������: " << x.m_i << endl;
	}
	catch (error_initialization_Matrix x)
	{
		cerr << "������ ���������������� ������ ���� Matrix ������� ����������: ( " << x.m_r << "; " << x.m_c << ")" << endl;
	}
	catch (error_nonexistence x)
	{
		cerr << "�������� � �������� " << x.m_i << "�� ����������!" << endl;
	}
	catch (error_no_solution1 x)
	{
		cerr << "� ������� ������������ ���� ���������� ������� �������, ������ ������� �������� ��������� ����� ���������� ����� �������!" << endl;
	}
	catch (error_no_solution2 x)
	{
		if (x.m_c - x.m_r < 1)
			cerr << "������� �������� �������� �� ����� �������, ������ ��� ������� ����������� ����� ������, ��� �����������!" << endl;
		else
			cerr << "������� �������� ��������� ����� ���������� ����� �������, ������ ��� ������� ����������� ����� ������, ��� �����������!" << endl;
	}
	return 0;
}