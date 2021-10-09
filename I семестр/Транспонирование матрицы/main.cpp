#include <iostream>
#include <math.h>
#include <ctime>
#define W 4
#define S 3

using namespace std;

int main ()
{
	int A[W][S];
	int k = 0, l = 0;
	srand(time(NULL));
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < S; j++)
		{
			A[i][j] = rand()%10;
			cout << A[i][j] << "  " << flush;
		}
		cout << endl;
	}
	cout << endl;
	while (A[k][0])
	{
		while (A[k][l])
		{
			cout << A[k][l] << " " << flush;
			++l;
		}
		++k;
		cout << endl;
	}
	return 0;
}
