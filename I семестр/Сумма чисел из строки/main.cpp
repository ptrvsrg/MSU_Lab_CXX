#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int read_int_numbers(FILE* fp, bool onlycount, int* a) 
{
	int sym = 0, cnt = 0;
	char c; 
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		int i = fscanf(fp, "%d", &sym);
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
			fscanf(fp, "%c", &c);
			sym = 0;

		}
	}
	return cnt;
}

int main() 
{
	setlocale(LC_ALL, "rus");
	char file_name[100];
	char file_final[100];
	int sum = 0;

	printf("Enter 1 file name: ");
	scanf("%s", file_name);
	printf("Enter 2 file name: ");
	scanf("%s", file_final);

	FILE* fp = fopen(file_name, "r");
	FILE* final = fopen(file_final, "w");
	if (!fp) 
	{
		printf("file open error %s", file_name);
		exit(1);
	}
	if (!final) 
	{
		printf("file open error %s", file_final);
		exit(2);
	}
	int cnt = read_int_numbers(fp, true, NULL);
	int* a = (int*)malloc(cnt * sizeof(int));
	read_int_numbers(fp, false, a);
	for (int i = 0; i < cnt; i++)
	{
		fprintf(final, "%d + ", a[i]);
		sum += a[i];
	}
	fprintf(final, "= %d", sum);
	return 0;
}
