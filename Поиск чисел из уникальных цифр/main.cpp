#include "counter.h"

int main()
{
	setlocale(LC_ALL, "");
	char file_name[100];
	int counter;

	printf("������� �������� �����: ");
	scanf("%s", file_name);

	FILE* file = fopen(file_name, "w");

	counter = count(file);

	printf("\n���������� �����, ������������ �� ���������� ���� �� ���������� �� %d �� %d: %d\n", A, B, counter);
	return 0;
}