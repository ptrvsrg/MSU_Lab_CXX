#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void uravnenie(int A, int B, int C, FILE* file)
{
	int D = pow(B, 2) - 4 * A * C;
	double x1, x2;
	if (D > 0)
	{
		x1 = (double)(-B - pow(D, 0.5)) / (2 * A);
		x2 = (double)(-B + pow(D, 0.5)) / (2 * A);
		fprintf(file, "A = %d;   B = %d;   C = %d;   x1 = %.2lf;   x2 = %.2lf;\n", A, B, C, x1, x2);
	}
	if (D == 0)
	{
		x1 = (double)(-B  / (2 * A));
		fprintf(file, "A = %d;   B = %d;   C = %d;   x1 = %.2lf;\n", A, B, C, x1);
	}
	if (D<0)
	{
		x1 = (double)(-B / (2 * A));
		x2 = (double)(pow(D * (-1), 0.5) / (2 * A));
		fprintf(file, "A = %d;   B = %d;   C = %d;   x1 = %.2lf + %.2lf i;   x2 = %.2lf - %.2lf i;\n", A, B, C, x1, x2, x1, x2);
	}
}

int main()
{
	char line[100];
	FILE* file = fopen("1.txt", "r"), * final = fopen("2.txt", "w");
	int A, B, C;
	
	while (!feof(file))
	{
		fgets(line, 100, file);
		A = atoi(strtok(line, " ,.:;\n"));
		B = atoi(strtok(NULL, " ,.:;\n"));
		C = atoi(strtok(NULL, " ,.:;\n"));
		uravnenie(A, B, C, final);
	}
}