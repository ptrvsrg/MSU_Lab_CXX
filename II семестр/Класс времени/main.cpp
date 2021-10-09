#include <iostream>
#include <cmath>

using namespace std;

struct error_initialization
{
	int i;

	error_initialization (int mi)
	{
		i = mi;
	}
};

struct error_non_existence
{
	int i;

	error_non_existence (int mi)
	{
		i = mi;
	}
};

class NumberArray
{
protected:

	double* massive;
	int lenght;

public:

	NumberArray(int N = 0) : lenght(N)
	{
		if (N < 0)
			throw error_initialization(N);
		else if (N > 0)
		{
			massive = new double[N];
		}
	}

	NumberArray(const NumberArray& temp) : lenght(temp.lenght)
	{
		massive = new double[temp.lenght];

		for (int i = 0; i < temp.lenght; i++)
			massive[i] = temp.massive[i];
	}

	~NumberArray()
	{
		lenght = 0;
		delete[] massive;
	}
};

class Time
{
public:

	double hours, minutes, seconds;

	Time(double nhours, double nminutes, double nseconds) : hours(nhours), minutes(nminutes), seconds(nseconds) {}

	Time(const Time& temp): hours(temp.hours), minutes(temp.minutes), seconds(temp.seconds) {}

	~Time()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
};

class TimeArray : public NumberArray
{
public:

	TimeArray (int N = 0): NumberArray(3*N) {}

	TimeArray(const TimeArray& temp) : NumberArray((const NumberArray&) temp) {}

	Time& operator [] (int index)
	{
		if (index >= lenght / 3 || index < 0)
			throw error_non_existence(index);
		else
		{
			Time res(massive[index*3], massive[index*3 + 1], massive[index*3 + 2]);
			return res;
		}
	}

	Time operator [] (int index) const
	{
		if (index >= lenght / 3 || index < 0)
			throw error_non_existence(index);
		else
		{
			Time res(massive[index * 3], massive[index * 3 + 1], massive[index * 3 + 2]);
			return res;
		}
	}

	TimeArray& operator=(const TimeArray& r)
	{
		delete[] massive;
		massive = new double[r.lenght];

		for (int i = 0; i < r.lenght; i++)
			massive[i] = r.massive[i];

		lenght = r.lenght;

		return *this;
	}

	TimeArray& operator+=(const TimeArray& r)
	{
		TimeArray res(fmax(lenght, r.lenght)/3);

		for (int i = 0; i < fmax(lenght, r.lenght); i++)
		{
			if (i < fmin(lenght, r.lenght))
				res.massive[i] = massive[i] + r.massive[i];
			else if (i < lenght)
				res.massive[i] = massive[i];
			else if (i < r.lenght)
				res.massive[i] = r.massive[i];
		}

		*this = res;
		return *this;
	}

	TimeArray& operator-=(const TimeArray& r)
	{
		TimeArray res(fmax(lenght, r.lenght)/3);

		for (int i = 0; i < fmax(lenght, r.lenght); i++)
		{
			if (i < fmin(lenght, r.lenght))
				res.massive[i] = massive[i] - r.massive[i];
			else if (i < lenght)
				res.massive[i] = massive[i];
			else if (i < r.lenght)
				res.massive[i] = - r.massive[i];
		}

		*this = res;
		return *this;
	}

	TimeArray insert(Time t, int pos)
	{
		if (pos < 0 || pos > lenght / 3)
			throw error_non_existence(pos);
		else
		{
			TimeArray res(lenght/3 + 1);

			for (int i = 0, j = 0; i < lenght + 3; i++, j++)
			{
				if (i == 3*pos)
				{
					res.massive[i] = t.hours;
					res.massive[i+1] = t.minutes;
					res.massive[i+2] = t.seconds;
					j--;
					i += 2;
				}
				else
				{
					res.massive[i] = massive[j];
				}
			}

			*this = res;
			return *this;
		}
	}

	TimeArray erase(int pos)
	{
		if (0 > pos || pos >= lenght / 3)
			throw error_non_existence(pos);
		else
		{
			TimeArray res(lenght / 3 - 1);

			for (int i = 0, j = 0; j < lenght; i++, j++)
			{
				if (j == 3 * pos)
				{
					i--;
					j += 2;
				}
				else 
					res.massive[i] = massive[j];
			}

			*this = res;
			return *this;
		}
	}

	friend ostream& operator << (ostream& os, const TimeArray& res);
	friend istream& operator >> (istream& is, TimeArray& res);
};

ostream& operator << (ostream& os, const TimeArray& res)
{
	for (int i = 0; i < res.lenght/3; i++)
		os << "[ " << res[i].hours << "; " << res[i].minutes << "; " << res[i].seconds << "]\n";

	return os;
}

istream& operator >> (istream& is, TimeArray& res)
{
	double nhours, nminutes, nseconds;

	if (res.lenght == 0)
	{
		int i = 0, len;
		cout << "Enter array size: ";
		cin >> len;
		if (len < 0)
			throw error_initialization(len);

		while (i < len)
		{
			cout << "Enter time (hours, minutes, seconds): ";
			is >> nhours;
			is >> nminutes;
			is >> nseconds;
			res.insert(Time(nhours, nminutes, nseconds), res.lenght/3);
			i++;
		}
	}

	else
	{
		for (int i = 0; i < res.lenght/3; i++)
		{
			cout << "Enter time (hours, minutes, seconds): ";
			is >> res.massive[3*i];
			is >> res.massive[3*i+1];
			is >> res.massive[3*i+2];
		}
	}

	return is;
}

int main()
{
	try
	{
		setlocale(LC_ALL, "");
		TimeArray MY, YOUR;
		cin >> MY;
		cout << MY << endl;
		Time A(4, 20, 0);

		YOUR = MY;

		YOUR.insert(A, 1);
		cout << YOUR << endl;

		YOUR += MY;
		cout << YOUR << endl;

		YOUR.erase(2);
		cout << YOUR << endl;
		return 0;
	}
	catch (error_initialization x)
	{
		cerr << "Initialization error " << x.i << '!' << endl;
	}
	catch (error_non_existence x)
	{
		cerr << "Non-existence error" << endl;
	}
}