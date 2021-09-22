#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#define MIN 1
#define MAX 30

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	printf("Случайное число: %d", rand() % (MAX - MIN + 1) + MIN);
}