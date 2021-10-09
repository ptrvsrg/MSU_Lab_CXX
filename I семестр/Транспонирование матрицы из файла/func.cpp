#include"trans.h"

int trans(char* file_name, char* file_final)
{
	int column = 0;
	int sym = 0;
	char LINE[100];
	FILE* fp, * fp2;
	fp = fopen(file_name, "r");

	if (!fp)
	{
		return 1;
	}

	fgets(LINE, 100, fp);
	for (int j = 0; j < strlen(LINE); j++)
	{
		if (LINE[j] >= '0' && LINE[j] <= '9')
		{
			if (!(LINE[j + 1] >= '0' && LINE[j + 1] <= '9'))
				++column;
		}
	}

	fseek(fp, 0, SEEK_SET);

	while (!feof(fp))
	{
		fgets(LINE, 100, fp);
		for (int j = 0; j < strlen(LINE); j++)
		{
			if (LINE[j] >= '0' && LINE[j] <= '9')
			{
				if (!(LINE[j + 1] >= '0' && LINE[j + 1] <= '9'))
					++sym;
			}
		}
		memset(LINE, 0, 100);
	}

	int n = sym / column;
	int m = column;
	fseek(fp, 0, SEEK_SET);

	int** MTR = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		MTR[i] = (int*)malloc(m * sizeof(int));
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fscanf(fp, "%d", &MTR[i][j]);
		}
	}
	fclose(fp);
	fp2 = fopen(file_final, "w");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fprintf(fp2, "%d ", MTR[j][i]);
		}
		fprintf(fp2, "\n");
	}
	free(MTR);
	fclose(fp2);
	return 0;
}