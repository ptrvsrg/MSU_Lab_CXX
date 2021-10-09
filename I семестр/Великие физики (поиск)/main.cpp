//Петров Сергей, 107 группа
//Семинар 7, задача 5
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char line[100];
	char line_2[100];
	char* elem;
	char country[20];
	FILE* file_1, * file_2;
	file_1 = fopen("famous_physicist.txt", "r");
	file_2 = fopen("famous_physicist_1.xlsx", "w");

	printf("Введите слово: ");
	scanf("%s", country);

	if (!file_1)
	{
		return 1;
	}

	while (!feof(file_1))
	{
		fgets(line, 100, file_1);
		strcpy(line_2, line);
		elem = strtok(line, " .,;:\n");
		while (elem != NULL)
		{
			if (strstr(elem, country) != NULL)
			{
				fprintf(file_2, "%s", line_2);
			}
			elem = strtok(NULL, " .,;:\n");
		}
	}
	fclose(file_1);
	fclose(file_2);
	return 0;
}