#include "counter.h"

int main()
{
	setlocale(LC_ALL, "");
	char file_name[100];
	int counter;

	printf("Введите название файла: ");
	scanf("%s", file_name);

	FILE* file = fopen(file_name, "w");

	counter = count(file);

	printf("\nКоличество чисел, составленных из уникальных цифр на промежутке от %d до %d: %d\n", A, B, counter);
	return 0;
}