#include "counter.h"

int count(FILE* file)
{
	setlocale(LC_ALL, "");
	int counter = 0, integer_part, remainder, j, * numeral = nullptr;
	bool switches;
	numeral = (int*)malloc(sizeof(int));

	for (int i = A; i <= B; i++)
	{
		switches = true;
		integer_part = 1;
		remainder = 10;
		j = 0;

		do
		{
			numeral = (int*)realloc(numeral, (j + 1) * sizeof(int));
			numeral[j] = i % remainder / integer_part;
			++j;
			remainder *= 10;
			integer_part *= 10;
		} while (i / integer_part != 0);

		for (int k = 0; k < j; k++)
		{
			for (int l = 0; l < j; l++)
			{
				if (numeral[k] == numeral[l] && k != l)
				{
					switches = false;
				}
			}
		}

		if (switches == true)
		{
			fprintf(file, "%d\n", i);
			++counter;
		}
	}

	free(numeral);
	return counter;
}