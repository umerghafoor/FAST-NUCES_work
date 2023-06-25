#include<iostream>

using namespace std;

int main()
{
	int n;
	cout << "Enter the size : ";
	cin >> n;
	int* arr = new int[n];

	for (int i = 0;i < n;i++)
	{
		cout << "Enter element " << i << " : ";cin >> *(arr + i);
	}

	//arranging even to right

	int* temp = new int[n];
	int j = 0;
	for (int i = 0;i < n;i++)
	{
		if (*(arr + i) % 2 == 0)
		{
			*(temp + j) = *(arr + i);
			j++;
		}
	}
	for (int i = 0;i < n;i++)
	{
		if (*(arr + i) % 2 != 0)
		{
			*(temp + j) = *(arr + i);
			j++;
		}
	}
	for (int i = 0;i < n;i++)
	{
		*(arr + i) = *(temp + i);
	}

	//counting even numbers

	int evenCount = 0;
	for (int i = 0;i < n;i++)
	{
		if (*(arr + i) % 2 == 0)
		{
			evenCount++;
		}
	}
	//Display
	for (int i = 0;i < n;i++)
	{
		cout << arr[i] << ",\t";
	}
	cout << endl;
	//Aranging order
	int temp2;

	for (int i = 0; i < evenCount - 1; i++) {
		for (int j = 0; j < evenCount - i - 1; j++) {
			if (*(arr + j) > *(arr + j + 1)) {
				temp2 = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp2;
			}
		}
	}

	//Display
	cout << "\nFinal Array is : ";
	for (int i = 0;i < n;i++)
	{
		cout << arr[i] << ",\t";
	}
}