#include <iostream>
#include <cmath>

using namespace std;

class RealNumber
{
private:
	double mantissa;
	int exponent;
public:
	RealNumber(double n_mantissa = 0, int n_exponent = 0) : mantissa(n_mantissa), exponent(n_exponent)
	{
		if (mantissa == 0)
			exponent = 1;
		else if (fabs(mantissa) >= 1)
			while (fabs(mantissa) >= 1)
			{
				mantissa /= 10;
				exponent++;
			}
		else if (0 < fabs(mantissa) < 0.1)
			while (0 < fabs(mantissa) < 0.1)
			{
				mantissa *= 10;
				exponent--;
			}
	}

	RealNumber(const RealNumber& temp) : mantissa(temp.mantissa), exponent(temp.exponent) {}

	RealNumber operator + (const RealNumber temp) const
	{
		RealNumber res(mantissa + temp.mantissa * pow(10, temp.exponent - exponent), exponent);
		return res;
	}

	RealNumber operator - (const RealNumber temp) const
	{
		RealNumber res(mantissa - temp.mantissa * pow(10, temp.exponent - exponent), exponent);
		return res;
	}

	RealNumber operator * (const RealNumber temp) const
	{
		RealNumber res(mantissa * temp.mantissa, exponent + temp.exponent);
		return res;
	}

	RealNumber operator / (const RealNumber temp) const
	{
		RealNumber res(mantissa / temp.mantissa, exponent - temp.exponent);
		return res;
	}

	RealNumber& operator = (const RealNumber temp)
	{
		mantissa = temp.mantissa;
		exponent = temp.exponent;
		return *this;
	}

	RealNumber operator = (double temp)
	{
		RealNumber res(temp);
		*this = res;
		return *this;
	}

	operator double()
	{
		return mantissa * pow(10, exponent);
	}

	~RealNumber()
	{
		mantissa = 0;
		exponent = 1;
	}

	friend ostream& operator << (ostream& os, RealNumber& temp);
	friend istream& operator >> (istream& is, RealNumber& temp);
};

ostream& operator << (ostream& os, RealNumber& temp)
{
	os << (double)temp;
	return os;
}

istream& operator >> (istream& is, RealNumber& temp)
{
	double res;
	is >> res;
	temp = res;
	return is;
}

int main()
{
	RealNumber A(134, -2), B;
	cout << A << endl;
	cin >> B;
	cout << B << endl;
	cout << A + B << endl;
}