#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class Integer {
	int number;
public:
	//include all the necessary checks before performing the operations in the functions
	Integer();// a default constructor
	Integer(int);// a parametrized constructor
	Integer(string str);
	// a parametrized constructor
	void set(int);
	//set value
	int get()const;
	//get value at (i,j)
	int bitCount();
	//Returns the number of one-bits in the 2's complement binary
	int compareTo(Integer); //Compares two Integer objects numerically.
	double doubleValue(); //Returns the value of this Integer as a double.
	float floatValue(); //Returns the value of this Integer as a float.
	Integer plus(const Integer&); //adds two Integers and return the result
	Integer minus(const Integer&); // subtracts two Integers and return the result
	Integer multiple(const Integer&); //multiplies two Integers and return the result
	Integer divide(const Integer&); //divides two Integers and return theresult
	static int numberOfLeadingZeros(int i); /*Returns the number of zero bits
	preceding the highest-order ("leftmost") one-bit in the two's complement
	binary representation of the specified int value.*/
	static int numberOfTrailingZeros(int i); /*Returns the number of zero bits
	following the lowest-order ("rightmost") one-bit in the two's complement binary
	representation of the specified int value.*/
	static string toBinaryString(int i); //Returns string representation of i
	static string toHexString(int i); //Returns string representation of i in base16
	static string toOctString(int i); //Returns string representation of i in base 8

};