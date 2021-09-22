#include "Integral.h"

void met_v_pr(double a, double b, int n, double T)
{
	setlocale(LC_ALL, "rus");
	int k = 0;
	double S0=0, S=0, dx, D = f(a);
	if (a <= b)
	{
		if (n > 0)
		{
			do
			{
				S0 = S;
				dx = (b - a) / n;
				S = 0;
				for (int i = 0; i < n; i++)
				{
					S += fmax(D, f(a + dx * (i + 1)));
					D = f(a + dx * (i + 1));
				}
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
			cout << "    �������� n >0" << endl;
		}
	}
	else
	{
		cout << "    �������������� ��������� ������������ ��������� ��� ������������ �������� ��������������" << endl;
	}
	
}
