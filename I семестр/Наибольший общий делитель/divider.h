#ifndef DIVIDER
#define DIVIDER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct param
{
	int row = 0;
	int* column_num = nullptr;
	int** MTR = nullptr;
};

param read(FILE* file);
int* max_divider(param A);
void print(FILE* file, FILE* final);

#endif DIVIDER