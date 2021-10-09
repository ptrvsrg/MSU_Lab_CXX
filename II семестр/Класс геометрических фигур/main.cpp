#include <iostream>
#include <cmath>

#define PI 3.1416

using namespace std;

class Point
{
protected:
	double X, Y;
public:
	Point(double nX = 0, double nY = 0) : X(nX), Y(nY) {}

	Point(const Point& res) : X(res.X), Y(res.Y) {}

	~Point()
	{
		X = 0;
		Y = 0;
	}
};

class Figure
{
protected:
	Point O;
public:
	Figure(Point nO) : O(nO) {}

	Figure(const Figure& res) : O(res.O) {}

	void MoveTo(Point nO)
	{
		O = nO;
	}

	virtual double perimeter() = 0;

	virtual double square() = 0;
};

class Quadrate : public Figure
{
public:
	double side;

	Quadrate(Point nO, double nside) : Figure(nO), side(nside) {}

	Quadrate(const Quadrate& res) : Figure(res.O), side(res.side) {}

	double perimeter()
	{
		return 4 * side;
	}

	double square()
	{
		return pow(side, 2);
	}
};

class Circle : public Figure
{
public:
	double radius;

	Circle(Point nO, double nradius) : Figure(nO), radius(nradius) {}

	Circle(const Circle& res) : Figure(res.O), radius(res.radius) {}

	double perimeter()
	{
		return 2 * PI * radius;
	}

	double square()
	{
		return PI * pow(radius, 2);
	}
};

void main()
{
	Quadrate a1(Point(0, 0), 2);
	Circle a2(Point(0, 0), 2);
	Figure* A[] = { &a1, &a2 };

	for (int i = 0; i < 2; i++)
		cout << A[i]->square() << endl;
}