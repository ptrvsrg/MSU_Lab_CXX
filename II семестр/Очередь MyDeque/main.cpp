//Петров Сергей
//Семинар 6, задача 11
#include <iostream>
#include <vector>

using namespace std;

//--------------------------------------------------------------------------------//
//////////////////////////////--- Структуры ошибок ---//////////////////////////////
//--------------------------------------------------------------------------------//

struct error_initialization
{
	int i;
	error_initialization(int m_i)
	{
		i = m_i;
	}
};

struct error_non_existence
{
	int i;
	error_non_existence(int m_i)
	{
		i = m_i;
	}
};

//-------------------------------------------------------------------------------------//
//////////////////////////////--- Шаблон класса mydeque ---//////////////////////////////
//-------------------------------------------------------------------------------------//

template <class CLASS, int defsize = 0> class MyDeque
{
private:

	//////////////////////////////--- Параметры ---//////////////////////////////

	vector <CLASS> queue;
	int begin, end;

	//////////////////////////////--- Структура итератора ---//////////////////////////////

	struct iterator
	{
		CLASS* iter;

		iterator(CLASS* n_iter = nullptr) : iter(n_iter) {}

		CLASS& operator*()
		{
			return *iter;
		}

		CLASS* operator++()
		{
			return ++iter;
		}

		CLASS* operator--()
		{
			return --iter;
		}

		bool operator==(const iterator& res) const
		{
			return iter == res.iter;
		}

		bool operator!=(const iterator& res) const
		{
			return !(iter == res.iter);
		}
	};

	//////////////////////////////--- Итератор на первый элемент ---//////////////////////////////

	iterator begin_()
	{
		return &queue[begin + 1];
	}

	//////////////////////////////--- Итератор на последний элемент ---//////////////////////////////

	iterator end_()
	{
		return &queue[end];
	}

	//////////////////////////////--- Удвоение длины вектора ---//////////////////////////////

	void doubling_memory(bool control)
	{
		vector <CLASS> res(queue.size());

		if (control)
		{
			begin += queue.size();
			end += queue.size();
			res.insert(res.begin() + begin + 1, queue.begin(), queue.end());
		}
		else
			res.insert(res.begin(), queue.begin(), queue.end());
		
		queue = res;
	}

public:

	//////////////////////////////--- Конструктор ---//////////////////////////////

	MyDeque(int N = defsize) : begin(N), end(N)
	{
		if (N > 0)
		{
			queue.resize(2*N);
			begin = N - 1;
		}
		else if (N < 0)
			throw error_initialization(N);
	}

	//////////////////////////////--- Конструктор копирования ---//////////////////////////////

	MyDeque(const MyDeque& temp): queue(temp.queue), begin(temp.begin), end(temp.end) {}

	//////////////////////////////--- Перевернуть очередь ---//////////////////////////////

	void reverse()
	{
		for (iterator f = begin_(), l = end_(); f != l && f != --l; ++f)
		{
			iter_swap(f, l);
		}
	}

	//////////////////////////////--- Вставка в начало очереди ---//////////////////////////////

	void insert_begin(CLASS value)
	{
		if (queue.empty()) //При размере вектора равному 0
		{
			queue.resize(2);
			end = 1;
		}

		queue[begin] = value;
		begin--;

		if (begin < 0)
			doubling_memory(true);
	}

	//////////////////////////////--- Вставка в конец очереди ---//////////////////////////////

	void insert_end(CLASS value)
	{
		if (queue.empty()) //При размере вектора равному 0
		{
			queue.resize(2);
			end = 1;
		}

		queue[end] = value;
		end++;

		if (end > queue.size() - 1)
			doubling_memory(false);
	}

	//////////////////////////////--- Удаление из начала очереди ---//////////////////////////////

	void erase_begin()
	{
		if (queue.empty()) //При размере вектора равному 0
			throw 1;

		begin++;
	}

	//////////////////////////////--- Удаление из конца очереди ---//////////////////////////////

	void erase_end()
	{
		if (queue.empty()) //При размере вектора равному 0
			throw 1;
		end--;
	}

	//////////////////////////////--- Оператор [] ---//////////////////////////////

	CLASS operator [] (int index) const
	{
		if (index < 0 || index > end - begin - 1)
			throw error_non_existence(begin + index + 1);
		else
			return queue[begin + index + 1];
	}

	CLASS& operator [] (int index)
	{
		if (index < 0 || index > end - begin - 1)
			throw error_non_existence(begin + index + 1);
		else
			return queue[begin + index + 1];
	}

	//////////////////////////////--- Печать очереди ---//////////////////////////////

	void print()
	{
		for (int i = begin + 1; i < end; i++)
			cout << queue[i];
	}

	//////////////////////////////--- Деструктор ---//////////////////////////////

	~MyDeque()
	{
		queue.clear();
		begin = end = 0;
	}
};

//----------------------------------------------------------------------------//
//////////////////////////////--- Функция main ---//////////////////////////////
//----------------------------------------------------------------------------//

int main()
{
	try
	{
		setlocale(LC_ALL, "");

		MyDeque <char> MY(0), YOUR(0);
		
		MY.insert_begin('I');
		MY.insert_end('V');
		MY.insert_begin('L');
		MY.insert_end('E');
		MY.print();

		YOUR.insert_begin('i');
		YOUR.insert_end('s');
		YOUR.insert_begin(' ');
		YOUR.insert_end(' ');
		YOUR.print();

		MY.reverse();
		MY.print();
		cout << endl;

	}
	catch (error_initialization x)
	{
		cerr << "Error 1: Нельзя инициализировать объект значением " << x.i << " !" << endl;
	}
	catch (error_non_existence x)
	{
		cerr << "Error 2: Не существует элемента с индексом " << x.i << " !" << endl;
	}
	catch (int x)
	{
		cerr << "Error 3: Попытка удаление элемента из пустого контейнера!" << endl;
	}
}