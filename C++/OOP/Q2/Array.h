#include<iostream>
using namespace std;
class Array {
private:
	int* array;
	int size;
public:
	Array();
	Array(int Size);
	Array(int *arr,int size);
	Array(const Array&);
	int operator[](int i) const;
	Array operator=(const Array);
	Array operator+(const Array);
	Array operator-(const Array);
	void operator++();
	Array& operator--(int x);
	bool operator==(const Array);
	bool operator!();
	void operator+=(const Array&);
	void operator-=(const Array&);
	int operator()(int idx,int val);
	friend istream& operator>>(istream& input,Array&);
	friend ostream& operator<<(ostream& output, const Array);
	~Array();
};