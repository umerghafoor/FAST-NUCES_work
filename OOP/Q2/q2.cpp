#include "Array.h" 
#include <iostream>

using namespace std;

int main()
{
	int size;
	int index, value;
	cout << "Enter the size of the first array : ";
	cin >> size;
	Array myArray(size);
	cout << "Enter the size of the Second array : ";
	cin >> size;
	Array tempArray(size);
	int choice = 1;
	system("cls");
	while (choice != 0)
	{
		cout << "1  Set Value of the Array" << endl;
		cout << "2  Display Value of the Array" << endl;
		cout << "3  Add two arrays" << endl;
		cout << "4  Subtract two arrays" << endl;
		cout << "5  Increment all elements of the array" << endl;
		cout << "6  Decrement all elements of the array" << endl;
		cout << "7  Remove value at an index" << endl;
		cout << "8  Check if two arrays are equal" << endl;
		cout << "9  Check if array is empty" << endl;
		cout << "10 Start Over" << endl;
		cout << "0  Exit" << endl;
		cout << "Enter choice : ";cin >> choice;
		cout << "==================================================" << endl;
		switch (choice)
		{
		case 1:
			cout << "\tSet Array" << endl;
			cout << "\n   Enter First Array"<<endl;cin >> myArray;
			cout << "\n   Enter Second Array" << endl;cin >> tempArray;
			break;
		case 2:
			cout << "\tDisplay Array" << endl;
			cout << "Display First Array  : " << myArray << endl;
			cout << "Display Second Array : " << tempArray << endl;
			break;
		case 3:
			cout << "\tAdd two arrays" << endl;
			cout << "Result of addition : " << myArray+tempArray << endl;
			break;
		case 4:
			cout << "\tSubtract two arrays" << endl;
			cout << "Result of subtraction : " << myArray - tempArray << endl;
			break;
		case 5:
			cout << "\tIncrement all elements of the array" << endl;
			++myArray;
			cout << "Array after increment : " << myArray << endl;
			break;
		case 6:
			cout << "\tDecrement all elements of the array" << endl;
			myArray--;
			cout << "Array after increment : " << myArray << endl;
			break;
		case 7:
			cout << "\tRemove Value from index" << endl;
			cout << "Enter index : ";
			cin >> index;
			cout << "Enter value : ";
			cin >> value;
			cout << "Return Value : " << myArray(index, value) << endl;
			cout << "Array after setting value : " << myArray << endl;
			break;
		case 8:
			cout << "\tCheck if two arrays are equal" << endl;
			if (myArray == tempArray) 
			{
				cout << "Arrays are equal" << endl;
			}
			else 
			{
				cout << "Arrays are not equal" << endl;
			}
			break;
		case 9:
			cout << "\tCheck if first array is empty" << endl;
			if (!myArray) 
			{
				cout << "Array is empty" << endl;
			}
			else 
			{
				cout << "Array is not empty" << endl;
			}
			break;
		case 10:
			system("cls");
			main();
			break;
		}
		system("pause");
		system("cls");
	}
}
