#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct error_initialization1
{
	int i;
	error_initialization1(int m_i)
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

template <class CLASS, int defsize = 0> class MySet
{
private:

	vector <CLASS> massive;

public:

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

	MySet(int N = defsize)
	{
		if (N >= 0)
			massive.resize(N+1);
		else if (N < 0)
			throw error_initialization1(N);
	}

	MySet(vector <CLASS> temp)
	{
		try
		{
			sort(temp.begin(), temp.end());

			for (int i = 0; i < temp.size() - 1; i++)
				if (temp[i] == temp[i + 1])
					throw 1;

			massive = temp;
			massive.resize(massive.size() + 1);
		}
		catch (int x)
		{
			cerr << "Невозможно инициализировать объект вектором { " << temp[0];
			for (int i = 1; i < temp.size(); i++)
				cerr << ", " << temp[i];
			cerr << " } !";
			exit(0);
		}
	}

	MySet(const MySet& temp): massive(temp.massive) {}

	CLASS operator [] (int index)
	{
		if (index < 0 || index >= size1())
			throw error_non_existence(index);
		else
			return massive[index];
	}

	int size1()
	{
		return massive.size() - 1;
	}

	iterator begin1()
	{
		return &massive[0];
	}

	iterator end1()
	{
		return &massive[size1()];
	}

	MySet insert1(CLASS temp)
	{
		try
		{			
			if (find(massive.begin(), massive.end() - 1, temp) != massive.end() - 1)
				throw 1;
			else
			{
				auto iter = massive.begin();
				while (iter != massive.end() - 1 && *iter < temp)
					iter++;

				massive.insert(iter, temp);
				return *this;
			}

		}
		catch (int x)
		{
			cerr << "Нельзя добавить в контейнер ключей элемент " << temp << " !";
			exit(0);
		}
	}

	iterator find1(CLASS val)
	{
		iterator first(begin1()), last(end1());

		while (first != last)
		{
			if (*first == val)
				return first;
			++first;
		}
		return last;
	}

	void print()
	{
		for (int i = 0; i < size1(); i++)
			cout << massive[i] << "; ";
	}

	~MySet()
	{
		massive.clear();
	}
};

int main()
{
	try
	{
		setlocale(LC_ALL, "");
		vector <double> a = { 1, 2, 3, 4, 5, 6,7, 8, 9, 10};
		MySet <double> A(a);
		A.insert1(100);
	}
	catch (error_initialization1 x)
	{
		cerr << "Невозможно инициализировать объект значением " << x.i << '!';
	}
	catch (error_non_existence x)
	{
		cerr << "Нет элемента с индексом " << x.i << '!';
	}
}