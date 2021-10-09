#include "word.h"

//Запись слов в бинарный файл
FILE* input(FILE* file)
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char file_final[] = "final.bin", LINE[1000], PROBA[1000], line[1000], * sym;
	INDEX index;
	int i = 0, j = 0;
	memset(LINE, 0, 1000);
	memset(PROBA, 0, 1000);
	memset(line, 0, 1000);

	FILE* final = fopen(file_final, "w+b");

	if (!final)
	{
		printf("Ошибка при открытии %s", file_final);
		exit(1);
	}

	while (!feof(file))
	{
		fgets(LINE, 1000, file);

		while (LINE[i])
		{
			PROBA[j] = LINE[i];

			if (((LINE[i] == '.' || LINE[i] == '!' || LINE[i] == '?') && (LINE[i + 1] == ' ' || LINE[i + 1] == '\n' || LINE[i + 1] == '\0' || LINE[i + 1] == '\t')) || LINE[i] == '\n' || LINE[i] == '\0')
			{
				strcpy(line, PROBA);
				sym = strtok(PROBA, " .:;,-");
				while (sym != NULL)
				{
					strcpy(index.lines, line);
					strcpy(index.word, _strlwr(sym));
					fwrite(&index, sizeof(INDEX), 1, final);
					sym = strtok(NULL, " :;,.-\n\r");
				}
				memset(PROBA, 0, 1000);
				memset(line, 0, 1000);
				j = -1;
				++i;
			}
			++i;
			++j;
		}
		i = 0;
		memset(LINE, 0, 1000);
	}
	fseek(file, 0, SEEK_SET);
	fseek(final, 0, SEEK_SET);
	return final;
}

//Чтение и поиск слов из бинарного файла
void output(FILE* file, FILE* final)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	INDEX index;
	int j = 0, k, m, n = 1;
	char letters[20], word[20], last[1000];
	memset(last, 0, 1000);

	printf("Введите нужное слово: ");
	scanf("%s", letters);
	printf("\n");

	while (fread(&index, sizeof(INDEX), 1, final))
	{
		k = 0;
		memset(word, 0, 20);
		strcpy(word, index.word);
		int leght = strlen(letters);

		for (int i = 0; word[i] != '\0'; i++)
		{
			m = i;
			for (int l = 0; l < leght; l++)
			{
				if (word[m] == letters[l])
				{
					if (l == leght - 1)
					{
						++k;
					}
					m++;
				}
				else
				{
					break;
				}
			}
		}

		if (k != 0 && strcmp(last, index.lines) != 0)
		{
			j += printf("%d) %s\n", n, index.lines);
			memset(last, 0, 1000);
			strcpy(last, index.lines);
			++n;
		}
	}

	if (j == 0)
	{
		printf("Такого слова нет в данном тексте\n");
	}

	fclose(final);
}