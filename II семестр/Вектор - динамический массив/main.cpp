#include <iostream>
#include <cmath>

using namespace std;

class Vector
{
private:
	double x, y;
public:
	Vector(double nx = 0, double ny = 0) : x(nx), y(ny)
	{}

	Vector(const Vector& r) : x(r.x), y(r.y)
	{}

	~Vector()
	{
		x = y = 0;
	}

	double X() const
	{
		return x;
	}

	double Y() const
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
	VectorArray(int N = 0) : len(0)
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

	VectorArray(const VectorArray& temp) : len(temp.len)
	{
		Vector* q = new Vector[temp.len];

		for (int i = 0; i < temp.len; i++)
			q[i] = temp.v[i];

		v = q;
	}
	
	int size() const
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

	VectorArray& insert(Vector r, int pos)
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

	VectorArray& erase(int pos)
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

	VectorArray& merge(const VectorArray w)
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

	~VectorArray()
	{
		delete[] v; 
	}
};

ostream& operator<< (ostream& os, const VectorArray& r)
{
	for (int i = 0; i < r.size(); i++)
	{
		os << "[ " << r[i].X() << "; " << r[i].Y() << "]\n";
	}

	return os;
}

istream& operator>> (istream& is, VectorArray& r)
{
	double nx, ny;

	if (r.size() == 0)
	{
		int i = 0, len;
		cout << "Enter array size: ";
		cin >> len;
		if (len < 0)
			throw 3;

		while (i < len)
		{
			cout << "Enter vector coordinates: ";
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
			cout << "Enter vector coordinates: ";
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
		cerr << "Error #" << x << endl;
	}

	return 0;
}