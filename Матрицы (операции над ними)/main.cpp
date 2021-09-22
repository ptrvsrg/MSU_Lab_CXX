#include "matrix.h"

int main()
{
	setlocale(LC_ALL, "");

	char file_name_1[100], file_name_2[100], file_final[100];

	printf("Введите имя первого файла: ");
	scanf("%s", file_name_1);

	printf("Введите имя второго файла: ");
	scanf("%s", file_name_2);

	printf("Введите имя файла, в который будет записан результат: ");
	scanf("%s", file_final);

	FILE* file_1 = fopen(file_name_1, "r"), * file_2 = fopen(file_name_2, "r"), * final = fopen(file_final, "w");

	if (!file_1)
	{
		printf("Ошибка при открытии файла %s!", file_name_1);
		return 1;
	}
	if (!file_2)
	{
		printf("Ошибка при открытии файла %s!", file_name_2);
		return 1;
	}	
	if (!final)
	{
		printf("Ошибка при открытии файла %s!", file_final);
		return 1;
	}
	
	print_matrix(final, addition(file_1, file_2));
	return 0;
}