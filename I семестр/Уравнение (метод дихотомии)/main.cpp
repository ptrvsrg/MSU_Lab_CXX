#include <iostream>
#include <math.h>

using namespace std;

double f(double x)
{
	return log(x) + int(1);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, c, d, e;
	int i = 1;
	cout << " log(x) + 1 = 0"  << endl << flush;
	cout << " Введите отрезок [a, b]: "  << flush;
	cin >> a >> b;
	cout << " Введите точность: " << flush;
	cin >> d;
	cout << " Введите невязку: " << flush;
	cin >> e;
	if (f(a)*f(b) > 0)
	{
		cout << " Выберите другой интервал [a, b]" << endl << flush;
		return 1;
	}
	c = (a + b) / 2;
	while (fabs(a - b) > d && fabs(f(a)-f(b)) > e)
	{
		if (f(a)*f(c) < 0)
		{
			b = c;
			i = i + 1;
		}
		else
		{
			a = c;
			i = i + 1;
		}
		c = (a + b) / 2;
	}
	d = fabs(a - b);
	e = fabs(f(b)-f(a));
	cout << " Ответ: " << c << endl << flush;
	cout << " Ширина интервала на последней итерации: " << d << endl << flush;
	cout << " Невязка: " << e << endl << flush;
	cout << " Количество итераций: " << i << endl << flush;
	return 0;
}
