#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

void write(FILE* file)
{
	srand(time(NULL));
	int num, sym, a, b;
	printf("Введите количество чисел в файле: ");
	scanf("%d", &num);
	printf("Введите пределы инициализации чисел: ");
	scanf("%d", &a);
	scanf("%d", &b);

	if (b < a)
	{
		printf("Ошибка при инициализации пределов");
		exit(2);
	}

	for (int i = 0; i < num; i++)
	{
		sym = rand() % (b-a+1) + a;
		fprintf(file, "%d; ", sym);
	}
}

int read(FILE* file, bool onlycount, int* a)
{
	int sym = 0, cnt = 0;
	char c;
	fseek(file, 0, SEEK_SET);
	while (!feof(file))
	{
		int i = fscanf(file, "%d", &sym);
		if (i)
		{
			if (!onlycount)
			{
				a[cnt] = sym;
			}
			cnt++;
		}
		else
		{
			fscanf(file, "%c", &c);
			sym = 0;

		}
	}
	return cnt;
}

int main()
{
	setlocale(LC_ALL, "");
	int index_1 = 0, index_2 = 1, difference, last;
	char file_name[20];

	printf("Введите название файла: ");
	scanf("%s", file_name);

	FILE* file = fopen(file_name, "w+");

	if (!file)
	{
		printf("Ошибка при открытии файла %s", file_name);
		exit(1);
	}

	write(file);
	int cnt = read(file, true, NULL) - 1;
	int* a = (int*)malloc(cnt * sizeof(int));
	read(file, false, a);

	last = fabs(a[index_1] - a[index_2]);
	for (int j = 0; j < cnt; j++)
	{
		for (int k = 0; k < cnt; k++)
		{
			if (j != k)
			{
				difference = fabs(a[k] - a[j]);
				if (difference < last)
				{
					index_1 = fmin(k, j);
					index_2 = fmax(k, j);
					last = difference;
				}
			}
		}
	}

	printf("Наименьший модуль разности: | A[%d] - A[%d] | = %d", index_1, index_2, last);
	fclose(file);
	return 0;
}