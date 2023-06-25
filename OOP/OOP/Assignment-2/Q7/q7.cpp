#include "Integer.h"
#include <iostream>
using namespace std;

int main()
{
	Integer intg, intg2, intgR;
	int i;

	int choice = 1;
	while (choice != 0)
	{
		cout << "1  Set value" << endl;
		cout << "2  Get value" << endl;
		cout << "3  Number of (1) Bits" << endl;
		cout << "4  Comparing Two Numbers" << endl;
		cout << "5  Return Double" << endl;
		cout << "6  Return Float" << endl;
		cout << "7  Add Numbers" << endl;
		cout << "8  Subtract Numbers" << endl;
		cout << "9  Multiply Numbers" << endl;
		cout << "10 Divide Numbers" << endl;
		cout << "11 Number of leading and trailing zeros" << endl;
		cout << "12 Convert to Bin,Hex and Oct" << endl;
		cout << "0  Exit" << endl;
		cout << "Enter choice : ";cin >> choice;
		cout << "==================================================" << endl;
		switch (choice)
		{
		case 1:
			cout << "\tSet value" << endl;
			cout << "Enter Value : ";cin >> i;
			intg.set(i);
			break;
		case 2:
			cout << "\tGet value" << endl;
			cout << "Value is : " << intg.get() << endl;
			break;
		case 3:
			cout << "\tNumber of (1) Bits" << endl;
			cout << "N0. of bits : " << intg.bitCount() << endl;
			break;
		case 4:
			cout << "\tComparing Two Numbers" << endl;
			cout << "Enter 2nd Value : ";cin >> i;
			intg2.set(i);
			if (intg.compareTo(intg2) == -1)
			{
				cout << "First One is Smaller" << endl;
			}
			else if (intg.compareTo(intg2) == 1)
			{
				cout << "First One is Greater" << endl;
			}
			else if (intg.compareTo(intg2) == -1)
			{
				cout << "Both are Equal" << endl;
			}
			break;
		case 5:
			cout << "\tReturn Double" << endl;
			cout << "Double Value : " << intg.doubleValue() << endl;
			break;
		case 6:
			cout << "\tReturn Float" << endl;
			cout << "Float Value : " << intg.floatValue() << endl;
			break;
		case 7:
			cout << "\tAdd Numbers" << endl;
			cout << "Enter 2nd Value : ";cin >> i;
			intg2.set(i);
			intgR = intg.plus(intg2);
			cout << "Sum : " << intgR.get() << endl;
			break;
		case 8:
			cout << "\tSubtract Numbers" << endl;
			cout << "Enter 2nd Value : ";cin >> i;
			intg2.set(i);
			intgR = intg.minus(intg2);
			cout << "Answer : " << intgR.get() << endl;
			break;
		case 9:
			cout << "\tMultiply Numbers" << endl;
			cout << "Enter 2nd Value : ";cin >> i;
			intg2.set(i);
			intgR = intg.multiple(intg2);
			cout << "Answer : " << intgR.get() << endl;
			break;
		case 10:
			cout << "\tDivide Numbers" << endl;
			cout << "Enter 2nd Value : ";cin >> i;
			intg2.set(i);
			intgR = intg.divide(intg2);
			cout << "Answer : " << intgR.get() << endl;
			break;
		case 11:
			cout << "\t Number of leading and trailing zeros" << endl;
			cout << "Leading Zeros  : " << intg.numberOfLeadingZeros(intg.get()) << endl;
			cout << "Trailing Zeros : " << intg.numberOfTrailingZeros(intg.get()) << endl;
			break;
		case 12:
			cout << "\tConvert to Bin,Hex and Oct" << endl;
			cout << "Binary : " << intg.toBinaryString(intg.get()) << endl;
			cout << "Hexa   : " << intg.toHexString(intg.get()) << endl;
			cout << "Octal  : " << intg.toOctString(intg.get()) << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}