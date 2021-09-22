#include "divider.h"

param read(FILE* file)
{
	param A;
	char LINE[100];
	int row = 0, column = 0, * column_num;
	column_num = (int*)malloc(sizeof(int));

	while (!feof(file))
	{
		column = 0;
		++row;
		fgets(LINE, 100, file);

		for (int j = 0; j < strlen(LINE); j++)
		{
			if (LINE[j] >= '0' && LINE[j] <= '9')
			{
				if (!(LINE[j + 1] >= '0' && LINE[j + 1] <= '9'))
					++column;
			}
		}
		memset(LINE, 0, 100);
		column_num = (int*)realloc(column_num, row * sizeof(int));
		column_num[row - 1] = column;
	}

	fseek(file, 0, SEEK_SET);

	int** MTR = (int**)malloc(row * sizeof(int*));

	for (int i = 0; i < row; i++)
	{
		MTR[i] = (int*)malloc(column_num[i] * sizeof(int*));

		for (int j = 0; j < column_num[i]; j++)
		{
			fscanf(file, "%d", &MTR[i][j]);
		}
	}
	A.column_num = column_num;
	A.MTR = MTR;
	A.row = row;
	fseek(file, 0, SEEK_SET);
	return A;
}

int* max_divider(param A)
{
	bool control, security;
	int divider, last, remainder, * save;
	save = (int*)malloc(sizeof(int));

	for (int i = 0; i < A.row; i++)
	{
		security = true;
		divider = 1;
		last = 1;

		while (security == true)
		{
			control = true;

			for (int j = 0; j < A.column_num[i]; j++)
			{
				remainder = A.MTR[i][j] % divider;
				if (remainder != 0)
					control = false;
				if (remainder == A.MTR[i][j])
					security = false;
			}

			if (control == true && security == true)
			{
				last = divider;
			}

			++divider;
		}

		save = (int*)realloc(save, (i + 1) * sizeof(int));
		save[i] = last;
	}

	return save;
}

void print(FILE* file, FILE* final)
{
	param A = read(file);
	int* save = max_divider(A);

	for (int i = 0; i < A.row; i++)
	{
		for (int j = 0; j < A.column_num[i]; j++)
		{
			fprintf(final, "%d ", A.MTR[i][j]);
		}
		fprintf(final, "| %d\n", save[i]);
	}
}