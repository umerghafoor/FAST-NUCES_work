#include <iostream>

using namespace std;
int main()
{
	int* arr = new int[10];
	int num = 0;
	
	for (int i = 0; i < 10; i++)
	{
		cout << "Enter the Element " << i + 1 << " : ";
		cin >> *(arr + i);
	}
	cout << "Enter the number : ";
	cin >> num;
	cout << "Multiples of " << num << " are : ";
	for (int i = 0; i < 10; i++)
	{
		if (*(arr + i) % num == 0)
		{
			cout << *(arr + i) << "\t";
		}
	}
}