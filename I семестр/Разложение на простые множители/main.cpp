#include "factor.h"

int main()
{
	setlocale(LC_ALL, "");
	int number;

	printf("¬ведите число: ");
	scanf("%d", &number);

	print(number, splitting(number));

	return 0;
}