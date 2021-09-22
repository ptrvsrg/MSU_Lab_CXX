#include "trans.h"

int main()
{
	setlocale(LC_ALL, "rus");
	char file_name[100], file_final[100];
	printf("ֲגוהטעו טלÿ פאיכא: ");
	scanf("%s", file_name);
	printf("ֲגוהטעו טלÿ פאיכא: ");
	scanf("%s", file_final);
	trans(file_name, file_final);
	return 0;
}