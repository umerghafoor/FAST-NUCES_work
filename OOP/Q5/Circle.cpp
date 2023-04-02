#include "Circle.h"
#include <iostream>
using namespace std;

Circle::Circle()
{
	x = 0;
	y = 0;
	radius = 0;
}
Circle::Circle(int x, int y)
{
	this->x = x;
	this->y = y;
}
Circle::Circle(int x, int y, int radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}
void Circle::setCenter(int X,int Y)
{
	x = X;
	y = Y;
}
void Circle::setRadius(int Radius)
{
	radius = Radius;
}
int Circle::getArea()
{
	return 3.1415 * radius * radius;
}
Circle Circle::returnLargestCircle(Circle CircleArr[],int SIZE)
{
	Circle largestCircle = CircleArr[0];

	for (int i = 1; i < SIZE; i++)
	{
		if (CircleArr[i].radius > largestCircle.radius)
		{
			largestCircle = CircleArr[i];
		}
	}

	return largestCircle;
}
bool Circle::overlapping(Circle c1, Circle c2)
{
	double dx = c1.x - c2.x;
	double dy = c1.y - c2.y;
	double distance = sqrt(dx * dx + dy * dy);

	if (distance <= c1.radius + c2.radius) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
Circle* Circle::overlappingCircles(Circle CircleArr[],int SIZE)
{
	Circle largetCircle = returnLargestCircle(CircleArr, SIZE);
	Circle* overlappingCircles = new Circle[SIZE];
	int numOverlapping = 0;

	for (int i = 0; i < SIZE; i++) 
	{
		if (overlapping(CircleArr[i], largetCircle))
		{
			overlappingCircles[numOverlapping] = CircleArr[i];
			numOverlapping++;
		}
	}
	Circle* resizedArray = new Circle[numOverlapping+1];
	for (int i = 0; i < numOverlapping+1; i++) 
	{
		resizedArray[i] = overlappingCircles[i];
	}
	delete[] overlappingCircles;

	return resizedArray;
}
void Circle::PrintCoordinate() 
{
	cout << '(' << x << ',' << y << ')' << endl;
}
int Circle::getRadius()
{
	return radius;
}
Circle::~Circle() 
{
//	std::cout << "Circle destruct" << std::endl;
}