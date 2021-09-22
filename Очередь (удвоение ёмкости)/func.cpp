#include "queue.h"

static int max_size = 0;//Размер очереди
static double* que_array = nullptr;//Элементы очереди
static int first = 0;//Первый элемент
static int current = 0;//Текущий элемент



//Выделение памяти
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



//Очистка памяти
void destruct()
{
	free(que_array);
	current = 0;
	first = 0;
}



//Добавление элемента
int push(double a)
{
	if (!que_array || max_size == 0)
	{
		return 1;
	}

	if (current == max_size)//Удвоение ёмкости
	{
		max_size *= 2;
		que_array = (double*)realloc(que_array, max_size * sizeof(double));
	}
	que_array[current] = a;
	++current;
	return 0;
}



//Показать элемент очереди
void top()
{
	if (first < current)
		cout << "   Первый элемент: " << que_array[first] << endl << flush;
	else
		cout << "   Очередь пуста." << endl << flush;
}



//Удаление элемента очереди
void pop()
{
	if (first < current)
	{
		first += 1;
	}
	else
		return;
}



//Вывод очереди на экран
void display()
{
	if (current - first == 0)
	{
		cout << "    Очередь пуста." << endl << flush;
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