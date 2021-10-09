#include "Integral.h"

void met_sr_pr(double a, double b, int n, double T)
{
	setlocale(LC_ALL, "rus");
	int k = 0;
	double S0 = 0, S = 0, dx;
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
					S += f(a + dx/2 + dx * i);
				}
				S *= dx;
				n *= 2;
				k++;
			} while (T < fabs(S - S0));
			cout << endl << "    Экспериментальное значение: " << S << endl << flush;
			cout << "    Конечное количество разбиений: " << n / 4 << endl << flush;
			cout << "    Количество итераций: " << k - 2 << endl << flush;
		}
		else
		{
			cout << "    Выберите n >0" << endl;
		}
	}
	else
	{
		cout << "    Воспользуйтесь свойством определённого интеграла при перестановке пределов интегрирования" << endl;
	}

}
