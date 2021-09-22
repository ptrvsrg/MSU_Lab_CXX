#include "divider.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	char file_name1[100], file_name2[100];

	/*printf("¬ведите название 1 текстового файла: ");
	scanf("%s", file_name1);
	printf("¬ведите название 2 текстового файла: ");
	scanf("%s", file_name2);
	
	FILE* file1 = fopen(file_name1, "r"), *file2 = fopen(file_name2, "w");*/
	FILE* file1 = fopen(argv[1], "r"), * file2 = fopen(argv[2], "w");

	if (!file1)
	{
		printf("ќшибка при открытии %s", file_name1);
		exit(1);
	}

	if (!file2)
	{
		printf("ќшибка при открытии %s", file_name2);
		exit(1);
	}

	print(file1, file2);

	return 0;
}