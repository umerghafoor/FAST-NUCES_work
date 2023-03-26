#include <iostream>
using namespace std;

void dis(int odr, double mat2[2][2], double mat3[3][3])
{
	if (odr == 2)
	{
		cout << mat2[1][1] << "\t";
	}
}

int main()
{
	int odr;
	double mat2[2][2], mat3[3][3];
	cout << "enter the order" << endl;
	cin >> odr;
	if (odr == 2)
	{
		for (int i = 0;i < odr;i++)
		{
			for (int j = 0;j < odr;j++)
			{
				cout << "enter the element " << j + 1 << ":";
				cin >> mat2[i][j];
			}
			cout << endl;
		}
	}
	else if (odr == 3)
	{
		for (int i = 0;i < odr;i++)
		{
			for (int j = 0;j < odr;j++)
			{
				cout << "enter the element " << j + 1 << ":";
				cin >> mat2[i][j];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "invalid matrix" << endl;
	}
	dis(odr, mat2, mat3);
}






//#include<iostream>
//
//using namespace std;
//
//int main() 
//{
//	int n;
//	cout << "Enter the size : ";
//	cin >> n;
//	int* arr = new int(n);
//
//	for (int i = 0;i < n;i++)
//	{
//		cout << "Enter element " << i << " : ";cin >> *(arr+i);
//	}
//
////arranging even to right
//
//	int* temp = new int(n);
//	int j = 0;
//	for (int i = 0;i < n;i++)
//	{
//		if (*(arr + i) % 2 == 0)
//		{
//			*(temp + j) = *(arr + i);
//			j++;
//		}
//	}
//	for (int i = 0;i < n;i++)
//	{
//		if (*(arr + i) % 2 != 0)
//		{
//			*(temp + j) = *(arr + i);
//			j++;
//		}
//	}
//	for (int i = 0;i < n;i++)
//	{
//		*(arr + i) = *(temp + i);
//	}
//
////counting even numbers
//
//	int evenCount = 0;
//	for (int i = 0;i < n;i++)
//	{
//		if (*(arr + i) % 2 == 0)
//		{
//			evenCount++;
//		}
//	}
////Display
//	for (int i = 0;i < n;i++)
//	{
//		cout << arr[i] << ",\t";
//	}
//	cout << endl;
////Aranging order
//	int temp2;
//	for (int i = 0;i < evenCount-1;i++)
//	{
//		if (*(arr + i) > *(arr + i + 1))
//		{
//			cout << "\nchek\n" << *(arr + i) << endl;
//			temp2 = *(arr + i);
//			*(arr + i) = *(arr + i + 1);
//			*(arr + i + 1) = temp2;
//			
//		}
//	}
//
////Display
//	for (int i = 0;i < n;i++)
//	{
//		cout << arr[i] << ",\t";
//	}
//}