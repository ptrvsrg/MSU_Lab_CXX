#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define _CRT_SECURE_NO_WARNINGS


int** Matr_Construct(int width, int height);
int Matr_Destruct(int** matr, int width, int height);
int** Matr_File_Scan(FILE* pf, int* width, int* height);
int Matr_Print(int** matr, int width, int height);
int Matr_Print_File(int** matr, int width, int height, FILE* fp);
void move_row(int** matr, int n_i, int height, int width);
void move_column(int** matr, int n_j, int height, int width);
void Find_Average(int** matr, int height, int width, FILE* fp);

int** Matr_Construct(int height, int width)
{ // ввод матрицы
	int i;
	// выделяем память под массив УКАЗАТЕЛЕЙ НА МАССИВЫ int
	int** matr = (int**)malloc(sizeof(int*) * (height));
	printf("Countructing Matrix!\n height = %d \n width = %d\n", height, width);
	if (width <= 0 || height <= 0)
	{
		free(matr);
		return NULL;
	}

	if (NULL == matr)
	{
		return NULL;
	}
	for (i = 0; i < height; ++i)
	{
		// выделяем память под каждый массив double ОТДЕЛЬНО
		matr[i] = (int*)malloc(sizeof(int) * (width));
		if (NULL == matr[i])
		{
			return NULL;
		}
	}
	return matr;
}

int Matr_Destruct(int** matr, int height, int width)
{
	int c;
	width = width;
	if (matr != NULL)
	{
		for (c = 0; c < height; ++c)
		{
			if (matr[c] != NULL)
			{
				free(matr[c]);
			}
		}
		free(matr);
	}
	return 1;
}

int** Matr_File_Scan(FILE* pf, int* height, int* width)
{
	int** matr;
	int i, j;
	*width = 0;
	*height = 0;
	if (pf == NULL)
	{
		return 0;
	}
	fscanf(pf, "%d", height);
	fscanf(pf, "%d", width);
	matr = Matr_Construct(*height, *width);
	for (i = 0; i < *height; ++i)
	{
		for (j = 0; j < *width; ++j)
		{
			fscanf(pf, "%d", &(matr[i][j]));
			// printf("%d ", (matr[i][j]));
		}
		// printf("\n");
	}
	// Matr_Print(matr, *width, *height);
	return matr;
}

int Matr_Print(int** matr, int height, int width)
{
	int i, j;
	printf("\n------\n");
	printf(" n = %d\n m = %d\n", height, width);
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			printf("%d ", matr[i][j]);
		}
		printf("\n");
	}
	return 1;
}

int Matr_Print_File(int** matr, int height, int width, FILE* fp)
{

	int i, j;
	fprintf(fp, "%d %d\n", height, width);
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			fprintf(fp, "%d ", matr[i][j]);
		}
		fprintf(fp, "\n");
	}
	return 1;
}

void Find_Average(int** matr, int height, int width, FILE* fp)
{
	double res = 0;
	int n_i = 0, n_j = 0;
	bool control = true;

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; j++)
			res += matr[i][j];

	res /= (height * width);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
			if (!(matr[i][j] < res) && !(matr[i][j] > res))
			{
				n_i = i;
				n_j = j;
				control = false;
				break;
			}
		if (!control)
			break;
	}

	if (!control)
	{
		move_row(matr, n_i, height, width);
		Matr_Print(matr, height, width);
		Matr_Print_File(matr, height, width, fp);
		move_column(matr, n_j, height, width);
		Matr_Print(matr, height, width);
		Matr_Print_File(matr, height, width, fp);
	}
}

void move_row(int**matr, int n_i, int height, int width)
{
	int res;
	for (int j = 0; j < width; j++)
	{
		res = matr[n_i][j];
		matr[n_i][j] = matr[height - 1][j];
		matr[height - 1][j] = res;
	}
}

void move_column(int** matr, int n_j, int height, int width)
{
	int res;
	for (int i = 0; i < height; i++)
	{
		res = matr[i][n_j];
		matr[i][n_j] = matr[i][width -1];
		matr[i][width - 1] = res;
	}
}

int main(void)
{
	FILE* pf;
	FILE* fp;
	int** matr;
	double res;
	int n, m;
	pf = fopen("1.txt", "r");
	fp = fopen("2.txt", "w");
	matr = Matr_File_Scan(pf, &n, &m);
	Matr_Print(matr, n, m);
	Matr_Print_File(matr, n, m, fp);
	Find_Average(matr, n, m, fp);
	//fclose(pf);
	//fclose(fp);
	Matr_Destruct(matr, n, m);
	return 0;
}