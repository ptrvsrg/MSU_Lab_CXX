#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctime>

#define W 10

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int i, j, m, n;
	double A[W], a;
	m = 0;
	n = 0;

	srand(time(NULL));
	for (i = 0; i < W; i++)
	{
		A[i] = rand()%11;
	}

	cout << "Initial array:  " << flush;

	for (i = 0; i < W; i++)
	{
		cout << A[i] << "; " << flush;
	}

	for (j = 0; j < W; j++)
	{
		for (i = j + 1; i < W; i++)
		{
			n++;
			if (A[j] < A[i])
			{
				a = A[j];
				A[j] = A[i];
				A[i] = a;
				m++;
			}
		}
	}
	cout << endl << endl << "Final array:  " << flush;

	for (i = 0; i < W; i++)
	{
		cout << A[i] << "; " << flush;
	}
	cout << endl << endl << "Count of permutatinons: " << m << endl << flush;
	cout << "Count of comparisons: " << n << endl << flush;
	return 0;
}
