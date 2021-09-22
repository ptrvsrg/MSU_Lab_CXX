#include "queue.h"

static int max_size = 0;//������ �������
static double* que_array = nullptr;//�������� �������
static int first = 0;//������ �������
static int current = 0;//������� �������



//��������� ������
int allocate(int S)
{
	if (S == 0)
	{
		return 1;
	}

	max_size = S;
	que_array = (double*)malloc(max_size * sizeof(double));

	if (!que_array)
	{
		return 1;
	}
	return 0;
}



//������� ������
void destruct()
{
	free(que_array);
	current = 0;
	first = 0;
}



//���������� ��������
int push(double a)
{
	if (!que_array || max_size == 0)
	{
		return 1;
	}

	if (current == max_size)//�������� �������
	{
		max_size *= 2;
		que_array = (double*)realloc(que_array, max_size * sizeof(double));
	}
	que_array[current] = a;
	++current;
	return 0;
}



//�������� ������� �������
void top()
{
	if (first < current)
		cout << "   ������ �������: " << que_array[first] << endl << flush;
	else
		cout << "   ������� �����." << endl << flush;
}



//�������� �������� �������
void pop()
{
	if (first < current)
	{
		first += 1;
	}
	else
		return;
}



//����� ������� �� �����
void display()
{
	if (current - first == 0)
	{
		cout << "    ������� �����." << endl << flush;
		return;
	}
	else
	{
		for (int i = first; i < current; i++)
		{
			cout << "    " << que_array[i] << endl << flush;
		}
	}
}