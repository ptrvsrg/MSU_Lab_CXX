//Петров Сергей
//3 семинар, 16 задача
#include <iostream>
#include <cmath>

using namespace std;

struct error_initialization
{
	int n;
	error_initialization(int ni)
	{
		n = ni;
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

//////////////////////////////////////////////////////

class Numbers
{
protected:
	double* mas;
	unsigned int dim;
public:
	Numbers(int N = 0) : mas(nullptr), dim(0) //Конструктор
	{
		if (N < 0)
			throw error_initialization(N);
		if (N > 0)
		{
			mas = new double[N];
			dim = N;
		}
	}

	Numbers(const Numbers& temp): mas(nullptr), dim(0)//Конструктор копирования
	{
		if (temp.dim > 0)
		{
			mas = new double[temp.dim];
			dim = temp.dim;

			for (int i = 0; i < dim; i++)
			{
				mas[i] = temp.mas[i]; 
			}
		}
	}

	~Numbers() //Деструктор
	{
		delete[] mas;
		dim = 0;
	}
};

//////////////////////////////////////////////////////

class Trinomial: public Numbers
{
public:
	Trinomial (): Numbers(3) {} //Конструктор

	Trinomial(const Trinomial& temp) : Numbers(temp) {} // Конструктор копирования

	double der(double x = 1) const
	{
		double sum = 0;

		for (int i = 1; i < dim; i++)
		{
			sum += i * mas[i] * pow(x, i - 1);
		}

		return sum;
	}

	double& operator[] (unsigned int index)
	{
		if (index >= dim || index < 0)
			throw error_nonexistence(index);
		else
			return mas[index];
	}

	double operator[] (unsigned int index) const
	{
		if (index >= dim || index < 0)
			throw error_nonexistence(index);
		else
			return mas[index];
	}

	Trinomial& operator+=(const Trinomial& r)
	{
		for (int i = 0; i < dim; i++)
		{
			if (i < r.dim)
				mas[i] += r.mas[i];
		}
		return *this;
	}

	Trinomial& operator-=(const Trinomial& r)
	{
		for (int i = 0; i < dim; i++)
		{
			if (i < r.dim)
				mas[i] -= r.mas[i];
		}
		return *this;
	}

	Trinomial& operator*=(double r)
	{
		for (int i = 0; i < dim; i++)
		{
			mas[i] *= r;
		}
		return *this;
	}

	double operator*= (const Trinomial& A) const //Скалярное умножение
	{
		return der(-1) * A.der(-1) + der(0) * A.der(0) + der(1) * A.der(1);
	}

	friend ostream& operator<< (ostream& os, const Trinomial& K);
	friend istream& operator>> (istream& is, Trinomial& r);
};

//////////////////////////////////////////////////////

ostream& operator<< (ostream& os, const Trinomial& K) //Вывод коэффициентов
{
	for (int i = 0; i < K.dim; i++)
	{
		os << 'a' << i << " = " << K[i] << ";  ";
	}

	return os;
}

istream& operator>> (istream& is, Trinomial& K) //Ввод коэффициентов
{
	double nx;
	cout << "Введите коэффициенты трёхчлена: ";
	for (int i = 0; i < K.dim; i++)
	{
		is >> nx;
		K[i] = nx;
	}
	return is;
}

//////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "");
	try
	{
		Trinomial A, B;
		cin >> A;
		cout << A << endl;
		cin >> B;
		cout << B << endl;
		B += A;
		cout << B << endl;
		B -= A;
		cout << B << endl;
		B *= A;
		cout << B << endl;
		cout << A * B << endl;
	}
	catch(error_initialization x)
	{ 
		cerr << "Нельзя инициализировать объект типа Numbers значением " << x.n << endl;
	}
	catch (error_nonexistence x)
	{
		cerr << "Не существует элемента массива с индексом " << x.m_i << endl;
	}

	return 0;
}