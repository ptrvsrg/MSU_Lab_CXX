#include <iostream>
#include <math.h>
#include <ctime>

#define W 10

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	int A[W];
	srand(time(NULL));

	cout << endl << "Исходный массив: " << flush;
	for (int i = 0; i < W; i++)
	{
		A[i] = rand() / 327;
		cout << A[i] << ", " << flush;
	}

	cout << endl << "Конечный массив: " << flush;
	int j = 0;
LABEL:
	A[j] = 0;
	cout << A[j] << ", " << flush;
	++j;
	if (j < W)
		goto LABEL;
	else
		return 0;
}