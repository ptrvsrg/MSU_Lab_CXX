#include "gist.h"

int main()
{
	setlocale(LC_ALL, "rus");
	int W;
	int* A;
	int max = 0, iter = 0, a;;
	srand(time(NULL));
	cout << "Введите размерность массива: ";
	cin >> W;

	A = (int*)malloc(W * sizeof(int));

	for (int i = 0; i < W; i++)
	{
		A[i] = rand() % 11;
	}

	gistogramm(W, A);

	free(A);

	return 0;
}

