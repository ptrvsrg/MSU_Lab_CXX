#include <iostream>

using namespace std;

struct error {
	int m_i;
	error(int i) {
		m_i = i;
	}
};

class Vector
{
private:
	double x, y;
public:
	Vector(double nx = 0, double ny = 0) :
		x(nx), y(ny)
	{}

	Vector(const Vector& r):
		x(r.x), y(r.y)
	{}

	~Vector()
	{}

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

	Vector& operator-=(const Vector& r)
	{
		x = x - r.x;
		y = y - r.y;
		return *this;
	}

	Vector operator-(const Vector& r) const
	{
		Vector res(*this);
		res -= r;
		return res;
	}

	Vector operator*(double r) const
	{
		Vector res(*this);
		res.x *= r;
		res.y *= r;
		return res;
	}

	Vector operator/(double r) const
	{
		Vector res(*this);
			if (r < 1.0E-10)
			{
				throw error(1);
			}
			res.x /= r;
			res.y /= r;
			return res;
	}

	double X() const
	{
		return x;
	}

	double Y() const
	{
		return y;
	}
};

Vector operator+(Vector& r1, Vector& r2)
{
	Vector res = r1;
	res += r2;
	return res;
}

ostream& operator<<(ostream& os, Vector& r)
{
	os << "[" << r.X() << "; ";
	os << r.Y() << "]" << flush;
	return os;
}

istream& operator>> (istream& is, Vector& r)
{
	double nx, ny;
	is >> nx;
	is >> ny;
	r = Vector(nx, ny);
	return is;
}

int main()
{
	setlocale(LC_ALL, "");
	Vector r1(1, 2), r2, r3;
	double k;
	char op;
	cout << "������� ������ r1\n" << flush;
	cin >> r1;
	cout << "������� �������������� ���� op\n" << flush;
	cin >> op;

	if (op == '+' || op == '-')
	{
		cout << "������� ������ r2\n" << flush;
		cin >> r2;
	}
	
	if (op == '*' || op == '/')
	{
		cout << "������� ����� k\n" << flush;
		cin >> k;
	}
	try
	{
		switch (op)
		{
		case'+':
			r3 = r1 + r2;
			cout << "   �����: " << r1 << ' ' << op << ' ' << r2 << " = " << r3 << endl << flush;
			break;
		case'-':
			r3 = r1 - r2;
			cout << "   �����: " << r1 << ' ' << op << ' ' << r2 << " = " << r3 << endl << flush;
			break;
		case'*':
			r3 = r1 * k;
			cout << "   �����: " << r1 << ' ' << op << ' ' << k << " = " << r3 << endl << flush;
			break;
		case'/':
			r3 = r1 / k;
			cout << "   �����: " << r1 << ' ' << op << ' ' << k << " = " << r3 << endl << flush;
			break;
		default:
			cout << "������ �1 - ������������ �������������� ����!\n" << flush;
			return 1;
		}
	}
	catch (int x)
	{
		cout << "\n������ �" << x << " - ������� �� ����!!!\n\n";
	}

	return 0;
}
