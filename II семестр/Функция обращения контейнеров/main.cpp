#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

using namespace std;

class STR
{
private:
	vector <char> line;
public:
	STR(const string & nline)
	{
		line.resize(nline.size());

		for (int i = 0; i < nline.size(); i++)
			line[i] = nline[i];
	}

	void print()
	{
		for (int i = 0; i < line.size(); i++)
			cout << line[i];
	}
};

template <class CLASS>
void reverse(CLASS* first, CLASS* last)
{
	while ((first != last) && (first != --last)) 
		iter_swap(first++, last);
}

int main()
{
	STR str1("L"), str2("I"), str3("V"), str4("E");
	list <STR> mas1 = { str1, str2, str3, str4 };
	vector <STR> mas2 = { str4, str3, str2, str1 };
	deque <STR> mas3 = { str1, str2, str3, str4 };

	reverse(mas1.begin(), mas1.end());
	reverse(mas2.begin(), mas2.end());
	reverse(mas3.begin(), mas3.end());

	for (auto i = mas1.begin(); i != mas1.end(); i++)
		(*i).print();

	cout << endl;

	for (auto i = mas2.begin(); i != mas2.end(); i++)
		(*i).print();

	cout << endl;

	for (auto i = mas3.begin(); i != mas3.end(); i++)
		(*i).print();
}