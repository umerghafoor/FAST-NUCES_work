#include <iostream>
using namespace std;
/*Write a recursive function that takes three square matrix
and checks whether the values are equal or not. It returns true
if they are equal else false.(10)*/
bool equal(int** matrixOne, int** matrixTwo, int** matrixThree, int row, int column)
{
	if (row == 0 || column == 0)
	{
		return 1;
	}
	if ((matrixOne[row - 1][column - 1] != matrixTwo[row - 1][column - 1]) || (matrixOne[row - 1][column - 1] != matrixThree[row - 1][column - 1]))
	{
		return 0;
	}
	else
	{
		if (column == 1) 
		{
			return equal(matrixOne, matrixTwo, matrixThree, row - 1, column);
		}
		else 
		{
			return equal(matrixOne, matrixTwo, matrixThree, row, column - 1);
		}
	}
}

int main()
{
	int size;
	cout << "Enter the sizes   : ";cin >> size;
	int** Array1 = new int* [size];
	int** Array2 = new int* [size];
	int** Array3 = new int* [size];
	for (int i = 0; i < size; i++)
	{
		Array1[i] = new int[size];
		Array2[i] = new int[size];
		Array3[i] = new int[size];
	}
	
	cout << "//////////////////   INPUT MATRIX 1  //////////////////// " << endl;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			cout << "Enter the Matrix 1 [" << i << "][" << j << "] : ";cin >> *(*(Array1 + i) + j);
		}
	}
	cout << "//////////////////   INPUT MATIX 2   //////////////////// " << endl;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			cout << "Enter the Matrix 2 [" << i << "][" << j << "] : ";cin >> *(*(Array2 + i) + j);
		}
	}
	cout << "//////////////////   INPUT MATRIX 3   //////////////////// " << endl;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
		{
			cout << "Enter the Matrix 3 [" << i << "][" << j << "] : ";cin >> *(*(Array3 + i) + j);
		}
	}

	if (equal(Array1, Array2, Array3, size, size))
		cout << "The Matrix are equal";
	else
		cout << "The Matrix are not equal";
	// deallocate memory
	for (int i = 0; i < size; i++) {
		delete[] Array1[i];
		delete[] Array2[i];
		delete[] Array3[i];
	}
	delete[] Array1;
	delete[] Array2;
	delete[] Array3;
}