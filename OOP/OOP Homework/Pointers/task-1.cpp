#include<iostream>
#include"MinMaxArray.h"

using namespace std;

int main()
{
	int arr[11];
	for (int i = 0; i < 11; i++)
	{
		cout << "Enter element "<<i<<" : ";
		cin >> arr[i];
	}
	int* pArr = arr;
	cout << "\nMinimum element is: " << min(pArr) << endl;
	cout << "Maximum element is: " << max(pArr) << endl;
}