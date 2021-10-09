#include "divider.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	char file_name1[100], file_name2[100];
	FILE* file1 = fopen(argv[1], "r"), * file2 = fopen(argv[2], "w");

	if (!file1)
	{
		printf("file open error %s", file_name1);
		exit(1);
	}

	if (!file2)
	{
		printf("file open error %s", file_name2);
		exit(1);
	}

	print(file1, file2);

	return 0;
}