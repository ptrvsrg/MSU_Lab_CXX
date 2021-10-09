#ifndef FACTOR
#define FACTOR
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

struct FACTORS
{
	int fact;
	int quantity = 0;
};

FACTORS* splitting(int number);
void print(int number, FACTORS* mas);

#endif FACTOR