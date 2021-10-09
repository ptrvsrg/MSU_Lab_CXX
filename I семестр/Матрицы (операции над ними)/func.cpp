#include "matrix.h"


int fcolumn(FILE* file)
{
	int column = 0;
	char LINE[100];

	fgets(LINE, 100, file);
	for (int j = 0; j < strlen(LINE); j++)
	{
		if (LINE[j] >= '0' && LINE[j] <= '9')
		{
			if (!(LINE[j + 1] >= '0' && LINE[j + 1] <= '9'))
				++column;
		}
	}
	fseek(file, 0, SEEK_SET);
	return column;
}


int frow(FILE* file)
{
	int row = 0, sym = 0, pr1 = 0, pr2 = 0, column = fcolumn(file);
	char LINE[100];
	while (!feof(file))
	{
		pr1 = 0;
		fgets(LINE, 100, file);
		for (int j = 0; j < strlen(LINE); j++)
		{
			if (LINE[j] >= '0' && LINE[j] <= '9')
			{
				if (!(LINE[j + 1] >= '0' && LINE[j + 1] <= '9'))
				{
					++sym;
					++pr1;
				}
			}
		}

		if (pr2 != 0 && pr1 != pr2)
		{
			printf("Wrong file");
			exit(1);
		}

		pr2 = pr1;
		memset(LINE, 0, 100);
	}

	row = sym / column;
	fseek(file, 0, SEEK_SET);
	return row;
}


int** memory(int row, int column)
{
	int** MTR;
	MTR = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
	{
		MTR[i] = (int*)malloc(column * sizeof(int));
	}
	return MTR;
}


void clear(int row, int** MTR)
{
	for (int i = 0; i < row; i++)
	{
		free(MTR[i]);
	}
	free(MTR);
}


int** read(int row, int column, int** MTR, FILE* file)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			fscanf(file, "%d", &MTR[i][j]);
		}
	}
	fseek(file, 0, SEEK_SET);
	return MTR;
}


matrix transposition(FILE* file)
{
	matrix M;
	int row = frow(file), column = fcolumn(file);
	int** MTR = read(row, column, memory(row, column), file), ** FINAL = memory(column, row);

	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			FINAL[i][j] = MTR[j][i];
		}
	}
	clear(row, MTR);
	M.MTR = FINAL;
	M.row = column;
	M.column = row;
	return M;
}


matrix multiplication_number(int coefficient, FILE* file)
{
	matrix M;
	int row = frow(file), column = fcolumn(file);
	int** MTR = read(row, column, memory(row, column), file);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			MTR[i][j] *= coefficient;
		}
	}
	M.MTR = MTR;
	M.row = row;
	M.column = column;
	return M;
}


matrix addition(FILE* file_1, FILE* file_2)
{
	matrix M;
	int row_1 = frow(file_1), row_2 = frow(file_2), column_1 = fcolumn(file_1), column_2 = fcolumn(file_2);
	int column_max = fmax(column_1, column_2), row_max = fmax(row_1, row_2);
	int** MTR_1 = read(row_1, column_1, memory(row_max, column_max), file_1), ** MTR_2 = read(row_2, column_2, memory(row_max, column_max), file_2);

	for (int i = 0; i < row_max; i++)
	{
		for (int j = column_1; j < column_max; j++)
		{
			MTR_1[i][j] = 0;
		}
	}
	for (int i = row_1; i < row_max; i++)
	{
		for (int j = 0; j < column_max; j++)
		{
			MTR_1[i][j] = 0;
		}
	}


	for (int i = 0; i < row_max; i++)
	{
		for (int j = column_2; j < column_max; j++)
		{
			MTR_2[i][j] = 0;
		}
	}
	for (int i = row_2; i < row_max; i++)
	{
		for (int j = 0; j < column_max; j++)
		{
			MTR_2[i][j] = 0;
		}
	}


	for (int i = 0; i < row_max; i++)
	{
		for (int j = 0; j < column_max; j++)
		{
			MTR_1[i][j] += MTR_2[i][j];
		}
	}

	clear(row_max, MTR_2);
	M.MTR = MTR_1;
	M.row = row_max;
	M.column = column_max;
	return M;
}


matrix multiplication_matrix(FILE* file_1, FILE* file_2)
{
	matrix M;
	int SYM, A, B;
	int row_1 = frow(file_1), row_2 = frow(file_2), column_1 = fcolumn(file_1), column_2 = fcolumn(file_2);
	int** MTR_1 = read(row_1, column_1, memory(row_1, column_1), file_1), ** MTR_2 = read(row_2, column_2, memory(row_2, column_2), file_2), ** FINAL = memory(row_1, column_2);

	if (row_2 != column_1)
	{
		printf("Wrong matrix\n");
		exit(1);
	}

	for (int i = 0; i < row_1; i++)
	{
		for (int j = 0; j < column_2; j++)
		{
			FINAL[i][j] = 0;
			for (int k = 0; k < row_2; k++)
			{
				A = MTR_1[i][k];
				B = MTR_2[k][j];
				FINAL[i][j] += A * B;
			}
		}
	}
	clear(row_1, MTR_1);
	clear(row_2, MTR_2);
	M.MTR = FINAL;
	M.row = row_1;
	M.column = column_2;
	return M;
}


int determinant(FILE* file)
{
	int l, d, sum11 = 1, sum12 = 0, sum21 = 1, sum22 = 0, row = frow(file), column = fcolumn(file);
	int** MTR = read(row, column, memory(row, column), file);

	if (row != column)
	{
		printf("Non-square matrix");
		exit(1);
	}

	for (int i = 0; i < row; i++)
	{
		sum11 = 1; l = 2 * row - 1 - i; sum21 = 1;
		for (int j = 0; j < row; j++)
		{
			sum21 *= MTR[j][l % row];
			l--;
			sum11 *= MTR[j][(j + i) % (row)];
		}
		sum22 += sum21;
		sum12 += sum11;
	}
	d = sum12 - sum22;
	return d;
}


void print_matrix(FILE* final, matrix M)
{
	for (int i = 0; i < M.row; i++)
	{
		for (int j = 0; j < M.column; j++)
		{
			fprintf(final, "%d ", M.MTR[i][j]);
		}
		fprintf(final, "\n");
	}
	for (int i = 0; i < M.row; i++)
	{
		free(M.MTR[i]);
	}
	free(M.MTR);
}