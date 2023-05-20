#include "String.h" 
#include <iostream>

using namespace std;

int main()
{
	String myString;
	String tempString;
	int index;
	char find;
	int choice = 1;
	while (choice != 0)
	{
		cout << "1  Set Value of the String" << endl;
		cout << "2  Display Value of the String" << endl;
		cout << "3  Display the length of the string object" << endl;
		cout << "4  Add string to objects using the + operator" << endl;
		cout << "5  Check Empty String" << endl;
		cout << "6  Find the index of a character in the string" << endl;
		cout << "7  Remove a substring in the string using the - operator" << endl;
		cout << "8  Multiply string using the * operator" << endl;
		cout << "9  Access characters of string using [] operator" << endl;
		cout << "0  Exit" << endl;
		cout << "Enter choice : ";cin >> choice;
		cout << "==================================================" << endl;
		switch (choice)
		{
		case 1:
			cout << "\tSet String" << endl;
			cout << "Enter String : ";cin >> myString;
			break;
		case 2:
			cout << "\tDisplay String" << endl;
			cout << "String is : " << myString << endl;
			break;
		case 3:
			cout << "\tDisplay the length of the string object" << endl;
			cout << "Length of myString : " << myString.length() << endl;
			break;
		case 4:
			cout << "\tAdd string to objects using the + operator" << endl;
			cout << "Enter Second String : ";cin >> tempString;
			myString = myString + tempString;
			break;
		case 5:
			cout << "\tCheck Empty String" << endl;
			if (!tempString) {
				cout << "String is empty" << endl;
			}
			else
			{
				cout << "String is not empty" << endl;
			}
			break;
		case 6:
			cout << "\tFinding the index of a character in the string" << endl;
			cout << "Enter Charactor : ";cin >> find;
			index = myString(find);
			cout << "Index of "<<find<<" : " << index << endl;
			break;
		case 7:
			cout << "\tRemove a substring in the string using the - operator" << endl;
			cout << "Enter String : ";cin >> tempString;
			myString = myString - tempString;
			break;
		case 8:
			cout << "\tMultiply string using the * operator" << endl;
			cout << "Enter Multiply Value : ";cin >> index;
			myString = myString * 3;
			break;
		case 9:
			cout << "\tAccess characters of string using [] operator" << endl;
			for (int i = 0; i < myString.length(); i++)
			{
				cout << myString[i] << " ";
			}
			cout << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}
