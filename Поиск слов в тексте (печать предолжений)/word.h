#define _CRT_SECURE_NO_WARNINGS
#ifndef WORDS
#define WORDS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>

struct INDEX
{
	char word[20];
	char lines[1000];
};

FILE* input(FILE* file);//������ ���� � �������� ����
void output(FILE* file, FILE* final);//������ � ����� ���� �� ��������� �����

#endif WORDS