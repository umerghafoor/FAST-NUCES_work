#include <iostream>
using namespace std;

int row, colmn;

//Is the sum of any two arrays equal to the 3rd array ? 
void CheckEqualSumArrays(int** A1, int** A2, int** A3)
{
	bool check = 0;
	int sumA1 = 0, sumA2 = 0, sumA3 = 0;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			sumA1 = sumA1 + *(*(A1 + i) + j);
		}
	}
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			sumA2 = sumA2 + *(*(A2 + i) + j);
		}
	}
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			sumA3 = sumA3 + *(*(A3 + i) + j);
		}
	}
	cout << endl << endl;
	if (sumA1 + sumA2 == sumA3)
	{
		check = 1;
	}
	else if (sumA1 + sumA3 == sumA2)
	{
		check = 1;
	}
	else if (sumA2 + sumA3 == sumA1)
	{
		check = 1;
	}
	if (check)
	{
		cout << "The sum of two arrays equal to the 3rd array" << endl;
	}
	else
	{
		cout << "The sum of two arrays is not equal to the 3rd array" << endl;
	}
}

//Is the difference of any two arrays equal to the 3rd array ? 
void CheckDifferentArrays(int** A1, int** A2, int** A3)
{
	bool check = 0;
	int sumA1 = 0, sumA2 = 0, sumA3 = 0;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			sumA1 = sumA1 + *(*(A1 + i) + j);
		}
	}
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			sumA2 = sumA2 + *(*(A2 + i) + j);
		}
	}
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			sumA3 = sumA3 + *(*(A3 + i) + j);
		}
	}
	cout << endl << endl;
	if (sumA1 - sumA2 == sumA3 || sumA1 - sumA2 == -sumA3)
	{
		check = 1;
	}
	else if (sumA1 - sumA3 == sumA2|| sumA1 - sumA3 == -sumA2)
	{
		check = 1;
	}
	else if (sumA2 - sumA3 == sumA1|| sumA2 - sumA3 == -sumA1)
	{
		check = 1;
	}
	if (check)
	{
		cout << "The difference of two arrays equal to the 3rd array" << endl;
	}
	else
	{
		cout << "The difference of two arrays is not equal to the 3rd array" << endl;
	}
}
//Are there any equal arrays among these ?
void CheckEqualArrays(int** A1, int** A2, int** A3)
{
	bool check1 = 1, check2 = 1, check3 = 1;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			if (*(*(A1 + i) + j) != *(*(A2 + i) + j))
			{
				check1 = 0;
			}
		}
	}
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			if (*(*(A1 + i) + j) != *(*(A3 + i) + j))
			{
				check2 = 0;
			}
		}
	}
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			if (*(*(A2 + i) + j) != *(*(A3 + i) + j))
			{
				check3 = 0;
			}
		}
	}

	if (check1||check2||check3)
	{
		cout << "There are equal arrays among these" << endl;
	}
	else
	{
		cout << "There is no equal arrays among these" << endl;
	}
}
//Find the same rows in each array.
void FindSameRows(int** A1, int** A2, int** A3)
{
	bool check1 = 1;
	bool check2 = 1;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			if (*(*(A1 + i) + j) != *(*(A2 + i) + j) && *(*(A1 + i) + j) != *(*(A3 + i) + j))
			{
				check1 = 0;
			}
		}
		if (check1)
		{
			cout << "There are the same rows" << endl;
			for (int j = 0;j < colmn;j++)
			{
				cout << *(*(A1 + i) + j) << '\t';
			}
			cout<< endl;
			check2 = 0;
		}
	}
	if (check2)
	{
		cout << "There is no same rows " << endl;
	}
}
//Rotate all three arrays up to 90 degrees in clockwise  direction.
void RotateArrays(int** A1, int** A2, int** A3)
{
	if (row != colmn)
	{
		cout << "Matrix is not aquare Matrix ! " << endl;
	//	return;
	}
	cout << "///////////////////////  Array 1  /////////////////////////" << endl;
	for (int i = 0;i < colmn;i++)
	{
		for (int j = row-1;j >= 0;j--)
		{
			cout << *(*(A1 + j) + i) << '\t';
		}
		cout << endl;
	}
	cout << "///////////////////////  Array 2  /////////////////////////" << endl;
	for (int i = 0;i < colmn;i++)
	{
		for (int j = row - 1;j >= 0;j--)
		{
			cout << *(*(A2 + j) + i) << '\t';
		}
		cout << endl;
	}
	cout << "///////////////////////  Array 3  /////////////////////////" << endl;
	for (int i = 0;i < colmn;i++)
	{
		for (int j = row - 1;j >= 0;j--)
		{
			cout << *(*(A3 + j) + i) << '\t';
		}
		cout << endl;
	}
}

int main()
{
	cout << "Enter the Rows   : ";cin >> row;
	cout << "Enter the column : ";cin >> colmn;
	int** Array1 = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Array1[i] = new int[colmn];
	}
	int** Array2 = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Array2[i] = new int[colmn];
	}
	int** Array3 = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Array3[i] = new int[colmn];
	}
	cout << "//////////////////   INPUT ARRAY 1  //////////////////// " << endl;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			cout << "Enter the Array1 [" << i << "][" << j << "] : ";cin >> *(*(Array1 + i) + j);
		}
	}
	cout << "//////////////////   INPUT ARRAY 2   //////////////////// " << endl;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			cout << "Enter the Array2 [" << i << "][" << j << "] : ";cin >> *(*(Array2 + i) + j);
		}
	}
	cout << "//////////////////   INPUT ARRAY 3   //////////////////// " << endl;
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < colmn;j++)
		{
			cout << "Enter the Array3 [" << i << "][" << j << "] : ";cin >> *(*(Array3 + i) + j);
		}
	}
	int choice = 9;
	system("cls");
	while (choice)
	{
		cout << "1. Is the sum of any two arrays equal to the 3rd array?" << endl;
		cout << "2. Is the difference of any two arrays equal to the 3rd array" << endl;
		cout << "3. Are there any equal arrays among these ?" << endl;
		cout << "4. Find the same rows in each array." << endl;
		cout << "5. Rotate all three arrays up to 90 degrees in clockwise direction." << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice : ";cin >> choice;
		switch (choice) 
		{
		case 1:	CheckEqualSumArrays(Array1, Array2, Array3);break;
		case 2:	CheckDifferentArrays(Array1, Array2, Array3);break;
		case 3:	CheckEqualArrays(Array1, Array2, Array3);break;
		case 4:	FindSameRows(Array1, Array2, Array3);break;
		case 5:	RotateArrays(Array1, Array2, Array3);break;
		}
		system("pause");
		system("cls");
	}
	for (int i = 0; i < row; i++)
	{
		delete[] Array1[i];
	}
	delete[] Array1;

	for (int i = 0; i < row; i++)
	{
		delete[] Array2[i];
	}
	delete[] Array2;

	for (int i = 0; i < row; i++)
	{
		delete[] Array3[i];
	}
	delete[] Array3;

}