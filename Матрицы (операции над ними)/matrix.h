#ifndef MATRIX
#define MATRIX
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>

struct matrix
{
	int row;
	int column;
	int** MTR;
};

int fcolumn(FILE* file);
int frow(FILE* file);
int** memory(int row, int column);
void clear(int row, int** MTR);
int** read(int row, int column, int** MTR, FILE* file);
matrix Matrix(FILE* file);
matrix transposition(FILE* file);
matrix multiplication_number(int coefficient, FILE* file);
matrix addition(FILE* file_1, FILE* file_2);
matrix multiplication_matrix(FILE* file_1, FILE* file_2);
int determinant(FILE* file);
void print_matrix(FILE* final, matrix M);
void print_column(FILE* final, matrix M, int index);

#endif