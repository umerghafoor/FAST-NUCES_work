#include "Integer.h"
#include <iostream>
using namespace std;

Integer::Integer()
{
	number = 0;
}
Integer::Integer(int num)
{
	number = num;
}

Integer::Integer(string str)
{
	number = stoi(str);
}

void Integer::set(int i)
{
	number = i;
}
int Integer::get()const
{
	return number;
}
int Integer::bitCount()
{
	int count = 0;
	int num = number;
	if (num < 0)
	{
		num = -num - 1;
		count++;
	}

	while (num > 0)
	{
		if (num % 2 == 1)
		{
			count++;
		}
		num = num / 2;
	}
	return count;
}
int Integer::compareTo(Integer other)
{
	if (number < other.get())
	{
		return -1;
	}
	else if (number > other.get())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
double Integer::doubleValue()
{
	double d = number * 1.0;
	return d;
}
float Integer::floatValue()
{
	float f = number * 1.0;
	return f;
}
Integer Integer::plus(const Integer& other)
{
	int result = number + other.number;
	return Integer(result);
}
Integer Integer::minus(const Integer& other)
{
	int result = number - other.number;
	return Integer(result);
}
Integer Integer::multiple(const Integer& other) {
	int result = number * other.number;
	return Integer(result);
}
Integer Integer::divide(const Integer& other) {
	if (other.number == 0) {
		cout << "Infinity" << endl;
		return Integer(0);
	}
	else {
		int result = number / other.number;
		return Integer(result);
	}
}
int Integer::numberOfLeadingZeros(int i) {
	if (i == 0)
	{
		return sizeof(int) * 8;
	}
	int count = 0;
	while ((i & 0x80000000) == 0)
	{
		count++;
		i <<= 1;
	}
	return count;
}
int Integer::numberOfTrailingZeros(int i) {
	if (i == 0)
	{
		return sizeof(int) * 8;
	}
	int count = 0;
	while ((i & 1) == 0)
	{
		count++;
		i >>= 1;
	}
	return count;
}
string Integer::toBinaryString(int i)
{
	string binaryString = "";
	int quotient = i, remainder;
	for (int j = 0; j < 32; j++)
	{
		remainder = quotient % 2;
		quotient /= 2;
		binaryString = to_string(remainder) + binaryString;
	}
	return binaryString;
}
string Integer::toHexString(int i) {
	string hexString = "";
	int quotient = i, remainder;
	for (int j = 0; j < 8; j++) {
		remainder = quotient % 16;
		quotient /= 16;
		if (remainder <= 9)
		{
			hexString = to_string(remainder) + hexString;
		}
		else
		{
			hexString = char(remainder - 10 + 'a') + hexString;
		}
	}
	return hexString;
}
string Integer::toOctString(int i)
{
	string octString = "";
	int digit = 0;
	bool isLeadingZero = true;
	for (int j = 0; j < 11; j++)
	{
		digit = (i / pow(8, 10 - j));
		if (digit > 0)
		{
			isLeadingZero = false;
		}
		if (!isLeadingZero)
		{
			octString += to_string(digit);
		}
		i %= static_cast<int>(pow(8, 10 - j));
	}
	if (octString == "")
	{
		octString = "0";
	}
	return octString;
}