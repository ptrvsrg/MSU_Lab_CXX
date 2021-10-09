//Петров Сергей, 107 группа
//2 семинар, 1 задача
#include <iostream>
#include <cmath>

using namespace std;

class Vector
{
private:
	double x, y;
public:
	Vector(double nx = 0, double ny = 0) : x(nx), y(ny) //Конструктор
	{}

	Vector(const Vector& r) : x(r.x), y(r.y) //Конструктор копирования
	{}

	~Vector() //Деструктор
	{
		x = y = 0;
	}

	double X() const //Получение координаты х
	{
		return x;
	}

	double Y() const //Получение координаты у
	{
		return y;
	}

	Vector& operator=(const Vector& r)
	{
		x = r.x;
		y = r.y;
		return *this;
	}

	Vector& operator+=(const Vector& r)
	{
		x = x + r.x;
		y = y + r.y;
		return *this;
	}
};

class VectorArray
{
private:
	Vector* v;
	unsigned int len;
public:
	VectorArray(int N = 0) : len(0) //Конструктор
	{
		if(N < 0)
			throw 1;

		else if (N > 0)
		{
			v = new Vector[N];
			if (v)
				len = N;
			else
				throw 1;
		}
	}

	VectorArray(const VectorArray& temp) : len(temp.len) //Конструктор копирования
	{
		Vector* q = new Vector[temp.len];

		for (int i = 0; i < temp.len; i++)
			q[i] = temp.v[i];

		v = q;
	}
	
	int size() const //Получение размера массива
	{ 
		return len; 
	}

	Vector& operator [] (int index)
	{
		if (index >= len || index < 0)
			throw 2;
		else
			return v[index];
	}

	Vector operator [] (int index) const
	{
		if (index >= len || index < 0)
			throw 2;
		else
			return v[index];
	}

	VectorArray& insert(Vector r, int pos) //Добавление вектора в конец массива
	{
		Vector* q;
		q = new Vector[len + 1];

		for (int i = 0, j = 0; j < len+1; i++, j++)
		{
			if (j != pos)
				q[j] = v[i];
			else
			{
				q[j] = r;
				i--;
			}
		}

		len++;
		delete[] v;
		v = q;
		return *this;
	}

	VectorArray& erase(int pos) //Удаление вектора из массива
	{
		if (pos >= len)
			throw 2;

		else
		{
			Vector* q;
			q = new Vector[len - 1];
			
			for (int i = 0, j = 0; i < len; i++, j++)
			{
				if (i != pos)
					q[j] = v[i];
				else
					j--;
			}

			delete[] v;
			len--;
			v = q;
			return *this;
		}
	}

	VectorArray& merge(const VectorArray w) //Объединение 2 массивов
	{
		Vector* q;
		q = new Vector[len + w.size()];

		for (int i = 0; i < len + w.size(); i++)
		{
			if(i < len)
				q[i] = v[i];
			else
				q[i] = w[i - len];
		}

		len += w.size();
		delete[] v;
		v = q;
		return *this;
	}

	VectorArray& operator+=(const VectorArray& r)
	{
		for (int i = 0; i < len; i++)
		{
			if (i < r.len)
				v[i] += r.v[i];
		}
		return *this;
	}

	~VectorArray() //Деструктор
	{
		delete[] v; 
	}
};

ostream& operator<< (ostream& os, const VectorArray& r) //Вывод массива
{
	for (int i = 0; i < r.size(); i++)
	{
		os << "[ " << r[i].X() << "; " << r[i].Y() << "]\n";
	}

	return os;
}

istream& operator>> (istream& is, VectorArray& r) //Ввод массива
{
	double nx, ny;

	if (r.size() == 0)
	{
		int i = 0, len;
		cout << "Введите размер массива: ";
		cin >> len;
		if (len < 0)
			throw 3;

		while (i < len)
		{
			cout << "Введите координаты вектора: ";
			is >> nx;
			is >> ny;
			r.insert(Vector(nx, ny), r.size());
			i++;
		}
	}

	else
	{
		for (int i = 0; i < r.size(); i++)
		{
			cout << "Введите координаты вектора: ";
			is >> nx;
			is >> ny;
			r[i] = Vector(nx, ny);
		}
	}
	
	return is;
}

int main()
{
	setlocale(LC_ALL, "");
	VectorArray A, B;
	Vector a(9, 9);

	try
	{
		cin >> A;
		A[1] = a;
		cout << A << endl;
		B = A;
		cout << B << endl;
		B += A;
		cout << B << endl;
		cout << B.erase(2) << endl;
		cout << A.merge(B) << endl;
	}
	catch (int x)
	{
		cerr << "Ошибка №" << x << endl;
	}

	return 0;
}