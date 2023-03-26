#include <iostream>
#include<string>
using namespace std;
int main()
{
	int x = 0;
	cout << "Enter the size : "; cin >> x;
	char *arr = new char[x];
	cout << "Enter the Word : ";
	for (int i = 0; i < x; i++)
	{
		cin >> *(arr + i);
	}

	cout << "Word is : ";
	for (int i = 0; i < x; i++)
	{
		cout << *(arr + i);
	}
	delete[] arr;
}