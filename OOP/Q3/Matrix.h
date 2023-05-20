#include<iostream>
using namespace std;
class Matrix {
private:
	int rows;
	int colm;
	float** matrix;
public:
	Matrix();
	Matrix(int rows, int colm);
	Matrix(const Matrix&);
	void operator()(int i, int j, float val);
	Matrix& operator=(const Matrix&);
	bool operator==(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix& operator++(int);
	void operator+=(const Matrix&);
	void operator-=(const Matrix&);
	~Matrix();
	friend istream& operator>>(istream& input,Matrix&);
	friend ostream& operator<<(ostream& output, const Matrix);
};