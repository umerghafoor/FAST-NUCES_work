#include <iostream>
#include <string>
#include <Bits.h>
using namespace std;
int cnt = 0;

class Integer {
	int num;
	// think about the private data members...
public:
	//include all the necessary checks before performing the operations in
	
	Integer();// a default constructor
	Integer(int);// a parametrized constructor
	Integer(string); // a parametrized
	void set(int);//set value
	int get()const;//get value at (i,j)
	int bitCount(); 
	//Returns the number of one-bits in the 2's complement binary
	int compareTo(Integer*,int); //Compares two Integer objects
	double doubleValue(); //Returns the value of this Integer as a
	float floatValue(); //Returns the value of this Integer as a
	Integer plus(const Integer&); //adds two Integers and return the result
	Integer minus(const Integer&); // subtracts two Integers and return the
		Integer multiple(const Integer&); //multiplies two Integers and return the
		Integer divide(const Integer&); //divides two Integers and return theresult
	static int numberOfLeadingZeros(int); /*Returns the number of zerobits
	preceding the highest-order ("leftmost") one-bit in the two's complement
	binary representation of the specified int value.*/
	static int numberOfTrailingZeros(int j); /*Returns the number of zero bits
	following the lowest-order ("rightmost") one-bit in the two's complement binary
	representation of the specified int value.*/

	static string toBinaryString(int); //Returns string representation of i
	static string toHexString(int); //Returns string representation of i in
	static string toOctString(int); //Returns string representation ofi in
	
};

Integer::Integer() 
{
	num = 0;
}
Integer::Integer(int n) 
{
	this ->num = n;
}
Integer::Integer(string m) 
{
	//this->num = stoi(m); //Used to convert string to int
}

void Integer::set(int n) 
{
	this->num = n;
}

int Integer::get() const 
{
	return this->num;
}

int Integer::bitCount() 
{
	int p = this->get();
	while (p>0) {
		if (p % 2 == 1) {
			cnt++;
			
		}
		p = p / 2;
	}
	
	return cnt;
}

int Integer::compareTo(Integer *e,int b) 
{
	int i = 0;
	if (this->num > e[b].num) {
		i = 2;

	}
	if (this->num == e[b].num) {
		i = 1;
	
	}
	if (this->num < e[b].num) {
		i = 0;
	}
	return i;
}

double Integer::doubleValue() 
{
	return (double)this->num;
}

float Integer::floatValue() 
{
	return (float)this->num;
}

Integer Integer::plus(const Integer& temp) 
{
	int add = 0;
	add = num + temp.num;
	return Integer(add);
}

Integer Integer::minus(const Integer& temp) 
{
	int sub = 0;
	sub = this->num - temp.num;
	return Integer(sub);
}

Integer Integer::multiple(const Integer& temp) 
{
	int mul = 0;
	mul = this->num * temp.num;
	return Integer(mul);
}
Integer Integer::divide(const Integer& temp) 
{
	float div = 0;
	div = this->num / temp.num*1.0;
	return Integer(div);
}


int Integer::numberOfLeadingZeros(int j) 
{
	int z = 0;
	while (j>0) {
		z++;
		j = j / 2;
	}
	return 8 - z;

}
int Integer::numberOfTrailingZeros(int j)
{
	int z = 0;
	while (j > 0) {
		if (j % 2 != 1) {
			z++;
		}
		else
			break;
	}
	return z;
}

string Integer::toBinaryString(int j)
{
	string s="";
	int a;
	while (j > 0) {
		a = j % 2;
		s = s+(to_string(a));
		j = j / 2;
	}
	return s;
}

string Integer::toHexString(int j) {
	string s= "";
	int a;
	while (j > 0) {
		a = j % 16;
		if (a >= 0 && a <= 9) {
			s = s + (to_string(a));
			
		}
		if (a == 10)
			s = s + "A";
		if (a == 11)
			s = s + "B";
		if (a == 12)
			s = s + "C";
		if (a == 13)
			s = s + "D";
		if (a == 14)
			s = s + "E";
		if (a == 15)
			s = s + "F";
		j = j / 16;
	}
	return s;

}

string Integer::toOctString(int j) {
	string s = "";
	int a;
	while (j > 0) {
		a = j % 8;
		s = s + (to_string(a));
		j = j / 8;
	}
	return s;
}


int main() {
	cout << "Enter Number of Integers You Want To Store" << endl;
	int n;
	cin >> n;
	int in, se;
	int dum, cont=1;
	Integer emp,a;
	Integer* i = new Integer[n];
	for (int j = 0;j < n;j++) {
		cout << "Enter Number " << j + 1 << endl;
		cin >> in;
		i[j].set(in);
	}


	cout << "What Do You Want To Do?" << endl;
	int ch;
	while(cont){
	cout << "1)Count 1 bits of a Number\n2)Compare Two Numbers\n3)Convert Number To Double\n";
	cout << "4)Convert Number To Float\n5)Add Two Numbers\n6)Subtract Two Numbers\n7)Multiply Two Numbers\n";
	cout << "8)Divide Two Numbers\n9)Get Number Of Leading Zeros\n10)Get Number Of Trailing Zeros\n";
	cout << "11)Convert Binary to String\n12)Convert Hex to String\n13)Convert Octal To String\n";
	cin >> ch;
	switch (ch) {
	case 1: {
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		dum = i[in].bitCount();
		cout << "The number of 1 bits in " << i[in].get() << " are " << dum << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 2:
	{
		cout << "Enter Index from 0 to " << n - 1 << " for First Number" << endl;
		cin >> in;
		cout << "Enter Index from 0 to " << n - 1 << " for Second Number" << endl;
		cin >> se;
		dum = i[in].compareTo(i, se);
		if (dum == 2)
			cout << " The Number " << i[in].get() << " is greater than " << i[se].get() << endl;
		if (dum == 1)
			cout << " The Number " << i[in].get() << " is equal to " << i[se].get() << endl;
		if (dum == 0)
			cout << " The Number " << i[in].get() << " is less than " << i[se].get() << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 3:
	{
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		double d = i[in].doubleValue();
		cout << "Double:" << d << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;

	}
	case 4: {
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		float f = i[in].floatValue();
		cout << "Double:" << f << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 5:
	{

		cout << "Enter Index from 0 to " << n - 1 << " for First Number" << endl;
		cin >> in;
		cout << "Enter Index from 0 to " << n - 1 << " for Second Number" << endl;
		cin >> se;
		a = i[se].get();
		i[in].plus(a);

		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;

	}
	case 6:
	{
		cout << "Enter Index from 0 to " << n - 1 << " for First Number" << endl;
		cin >> in;
		cout << "Enter Index from 0 to " << n - 1 << " for Second Number" << endl;
		cin >> se;
		a = i[se].get();
		i[in].minus(a);

		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 7:
	{
		cout << "Enter Index from 0 to " << n - 1 << " for First Number" << endl;
		cin >> in;
		cout << "Enter Index from 0 to " << n - 1 << " for Second Number" << endl;
		cin >> se;
		a = i[se].get();
		i[in].multiple(a);

		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 8:
	{
		cout << "Enter Index from 0 to " << n - 1 << " for First Number" << endl;
		cin >> in;
		cout << "Enter Index from 0 to " << n - 1 << " for Second Number" << endl;
		cin >> se;
		a = i[se].get();
		i[in].divide(a);

		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 9:
	{
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		int x = i[in].get();
		cout << "The Number of Leading 0s are " << i->numberOfLeadingZeros(x) << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 10:
	{
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		int x = i[in].get();
		cout << "The Number of Trailing 0s are " << i->numberOfTrailingZeros(x) << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 11:
	{
		string s;
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		int x = i[in].get();
		cout << x << " -> Binary:" << i[in].toBinaryString(x) << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	case 12:
	{
		//static string s;
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		int x = i[in].get();
		cout << x << " -> Hexa:" << i[in].toHexString(x) << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;

	}
	case 13:
	{
		//static string s;
		cout << "Enter Index from 0 to " << n - 1 << endl;
		cin >> in;
		int x = i[in].get();
		cout << x << " -> Octal:" << i[in].toOctString(x) << endl;
		cout << "Continue?\n1)Yes\n0)No" << endl;
		cin >> cont;
		break;
	}
	}
	}
}

