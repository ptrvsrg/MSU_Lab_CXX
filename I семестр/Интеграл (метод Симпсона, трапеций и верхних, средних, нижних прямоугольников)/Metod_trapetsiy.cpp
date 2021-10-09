#include "Integral.h"

void met_tr(double a, double b, int n, double T)
{
	setlocale(LC_ALL, "rus");
	int k = 0;
	double S0=0, S=0, dx;
	if (n > 0)
	{
		if (a <= b)
		{
			do
			{
				dx = (b - a) / n;
				S0 = S;
				S = 0;
				for (int i = 1; i < n; i++)
				{
					S += (f(a + dx * i));
				}
				S += (f(a) + f(b)) / 2;
				S *= dx;
				n *= 2;
				k++;
			} while (T < fabs(S - S0));
			cout << endl << "    ����������������� ��������: " << S << endl << flush;
			cout << "    �������� ���������� ���������: " << n / 4 << endl << flush;
			cout << "    ���������� ��������: " << k - 2 << endl << flush;
		}
		else
		{
			cout << "    �������������� ��������� ������������ ��������� ��� ������������ �������� ��������������" << endl;
		}
	}
	else
	{
		cout << "    �������� n > 0" << endl;
	}
}
