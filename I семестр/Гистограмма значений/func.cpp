#include "gist.h"

char** gistogramm(int W, int* A)
{
	char** B;
	int max = 0, iter = 0;
	B = (char**)malloc(W * sizeof(char*));

	for (int i = 0; i < W; i++)
	{
		max = fmax(A[i], max);
	}

	for (int i = 0; i < W; i++)
	{
		B[i] = (char*)malloc(max * sizeof(char));
	}

	for (int i = 0; i < W; i++)
	{
		iter = max;
		for (int j = 0; j < A[i]; j++)
		{
			B[i][j] = '*';
		}
		iter = A[i];
		for (iter; iter < max; iter++)
		{
			B[i][iter] = ' ';
		}
	}

	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cout << B[j][max - i - 1] << " " << flush;
		}
		cout << endl << flush;
	}
	cout << endl << flush;
	for (int j = 0; j < W; j++)
	{
		cout << A[j] << " " << flush;
	}
	return B;
}