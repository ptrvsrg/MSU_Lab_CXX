//������ ������, 107 ������
//������� 8, ������ 12
#include "word.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char file_begin[100];
	
	printf("������� �������� ���������� �����: ");
	scanf("%s", file_begin);

	FILE* file = fopen(file_begin, "r+");

	if (!file)
	{
		printf("������ ��� �������� %s", file_begin);
		exit(1);
	}

	output(file, input(file));
	return 0;
}