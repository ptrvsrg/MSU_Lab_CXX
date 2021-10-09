#include "factor.h"

static int i = 0;

FACTORS* splitting(int number)
{
	int proba, divider = 2, remainder;
	FACTORS* mas;
	mas = (FACTORS*)malloc(sizeof(FACTORS));

	if (number == 0 || number == 1)
	{
		printf("%d = %d", number, number);
		exit(0);
	}

	proba = fabs(number);

	while (proba > 1)
	{
		remainder = proba % divider;

		if (remainder == 0)
		{
			if (mas[i - 1].fact == divider)
			{
				++mas[i - 1].quantity;
			}
			else
			{
				mas[i].fact = divider;
				mas[i].quantity = 1;
				++i;
				mas = (FACTORS*)realloc(mas, (i + 1) * sizeof(FACTORS));
			}
			proba = proba / divider;
		}
		else
		{
			++divider;
		}
	}
	return mas;
}

void print(int number, FACTORS* mas)
{
	if (number > 0)
		printf("\n%d = ", number);
	else
		printf("\n%d = - ", number);
	for (int j = 0; j < i; j++)
	{
		printf("%d", mas[j].fact);

		if (mas[j].quantity != 1)
			printf("^%d", mas[j].quantity);

		if (j != i - 1)
			printf(" * ");
		else
			printf(";\n");
	}

	free(mas);
}