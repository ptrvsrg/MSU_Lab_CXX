#include <iostream>
#include <vector>

using namespace std;

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

template <class CLASS, int defsize = 0> class MyDeque
{
private:

	vector <CLASS> queue;
	int begin, end;

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

	iterator begin_()
	{
		return &queue[begin + 1];
	}

	iterator end_()
	{
		return &queue[end];
	}

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

	MyDeque(const MyDeque& temp): queue(temp.queue), begin(temp.begin), end(temp.end) {}

	void reverse()
	{
		for (iterator f = begin_(), l = end_(); f != l && f != --l; ++f)
		{
			iter_swap(f, l);
		}
	}

	void insert_begin(CLASS value)
	{
		if (queue.empty())
		{
			queue.resize(2);
			end = 1;
		}

		queue[begin] = value;
		begin--;

		if (begin < 0)
			doubling_memory(true);
	}

	void insert_end(CLASS value)
	{
		if (queue.empty())
		{
			queue.resize(2);
			end = 1;
		}

		queue[end] = value;
		end++;

		if (end > queue.size() - 1)
			doubling_memory(false);
	}

	void erase_begin()
	{
		if (queue.empty())
			throw 1;

		begin++;
	}

	void erase_end()
	{
		if (queue.empty())
			throw 1;
		end--;
	}

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

	void print()
	{
		for (int i = begin + 1; i < end; i++)
			cout << queue[i];
	}

	~MyDeque()
	{
		queue.clear();
		begin = end = 0;
	}
};

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
		cerr << "Initialization error " << x.i << " !" << endl;
	}
	catch (error_non_existence x)
	{
		cerr << "Non-existence error " << x.i << " !" << endl;
	}
	catch (int x)
	{
		cerr << "Remove element from empty deque" << endl;
	}
}