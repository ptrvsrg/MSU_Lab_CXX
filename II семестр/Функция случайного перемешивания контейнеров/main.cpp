#include <list>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

template <class CLASS>
void rand(list <CLASS> & massive)
{
	srand(time(NULL));

	for (auto iter1 = massive.begin(); iter1 != massive.end(); iter1++)
	{
		auto iter2 = massive.begin();
		for (int j = 0; j < rand() % massive.size(); j++)
			iter2++;
		swap(*iter1, *iter2);
	}
}

template <class CLASS>
void rand(vector <CLASS> & massive)
{
	srand(time(NULL));

	for (int i = 0; i < massive.size(); i++)
	{
		int j = rand() % massive.size();
		swap(massive[i], massive[j]);
	}
}

int main()
{
	list <int> massive = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	rand(massive);
	
	for (auto i = massive.begin(); i != massive.end(); i++)
		cout << *i;
}