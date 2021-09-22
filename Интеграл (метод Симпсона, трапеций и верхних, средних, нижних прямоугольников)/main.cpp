#include "Integral.h"

int main()
{
	setlocale(LC_ALL, "");
	double a, b, T;
	int n;

	cout <<"Введите пределы интегрирования [a, b]: " << flush;
	cin >> a >> b;
	cout << "Начальное количество разбиений n: " << flush;
	cin >> n;
	cout << "Точность T: " << flush;
	cin >> T;

		cout << "\n  Метод трапеций: \n" << flush;
		met_tr(a, b, n, T);
		cout << "\n  Метод верхних прямоугольников: \n" << flush;
		met_v_pr(a, b, n, T);
		cout << "\n  Метод средних прямоугольников: \n" << flush;
		met_sr_pr(a, b, n, T);
		cout << "\n  Метод нижних прямоугольников: \n" << flush;
		met_n_pr(a, b, n, T);
		cout << "\n  Метод Симпсона: \n" << flush;
		met_sim(a, b, n, T);
	return 0;
}