#include "Vehicle.h"
#include <array> 
#include <iostream>

using namespace std;
const int noOfVehicle = 10;
int main()
{
	Vehicle* v = new Vehicle[noOfVehicle];
	int index, year, size;
	double value;
	char registrationNumber[10];
	char make[20];
	Vehicle vTemp;
	int choice = 1;
	Vehicle* temp2;
	Vehicle* temp;
	Vehicle* temp3;
	while (choice != 0) 
	{
		cout << "1 Creatig Vehicle" << endl;
		cout << "2 Age of Vehicle" << endl;
		cout << "3 Displaying All" << endl;
		cout << "4 Displaying At Index" << endl;
		cout << "5 Matching Vehicle" << endl;
		cout << "6 Return by Make" << endl;
		cout << "7 Return by Value" << endl;
		cout << "8 Return by Year" << endl;
		cout << "9 Vehicle Sold" << endl;
		cout << "0 Exit" << endl;
		cout << "Enter choice : ";cin >> choice;
		switch (choice) {
		case 1:
			cout << "\tCreatig Vehicle" << endl;
			cout << "Enter Index [0," << noOfVehicle - 1 << "] : ";
			cin >> index;
			v->addVehicle(v, index);
			break;
		case 2:
			cout << "\tAge of Vehicle" << endl;
			cout << "Enter Index [0," << noOfVehicle - 1 << "]  : ";
			cin >> index;
			cout << "Enter Current Year : ";
			cin >> year;
			cout << "Age : " << v[index].ageOfVehicle(year) << endl;
			break;
		case 3:
			cout << "\tDisplaying All" << endl;
			cout << "RegNo." << '\t' << "Make" << '\t' << "Year" << '\t' << "currentValue" << endl;
			for (int i = 0;i < noOfVehicle;i++)
			{
				if (v[i].getYearOfManufacture() > 0)
				{
					v[i].getVehicleDetails();
				}
			}
			break;
		case 4:
			cout << "\tDisplaying At Index" << endl;
			cout << "Enter Index [0," << noOfVehicle - 1 << "]  : ";
			cin >> index;
			cout << "RegNo." << '\t' << "Make" << '\t' << "Year" << '\t' << "currentValue" << endl;
			v->getVehicleDetailsAtIndex(v, index);
			break;
		case 5:
			cout << "\tMatching Vehicle" << endl;
			cout << "Enter registration number : ";
			cin >> registrationNumber;
			cout << "Enter make                : ";
			cin >> make;
			cout << "Enter year of manufacture : ";
			cin >> year;
			cout << "Enter current value       : ";
			cin >> value;
			vTemp.setRegistrationNumber(registrationNumber);
			vTemp.setMake(make);
			vTemp.setYearOfManufacture(year);
			vTemp.setCurrentValue(value);
			cout << "Enter Index of Compare [0," << noOfVehicle - 1 << "]  : ";
			cin >> index;
			if (v[index].isMatching(vTemp))
			{
				cout << "Vehicle is Matching" << endl;
			}
			else
			{
				cout << "Vehicle is not Matching" << endl;
			}
			break;
		case 6:
			cout << "\tReturn by Make" << endl;
			cout << "Enter make : ";
			cin >> make;
			size = noOfVehicle;
			temp = v[0].returnByMake(v, make, size);
			if (size == 0)
			{
				cout << "No Data Found" << endl;
			}
			for (int i = 0; i < size; i++)
			{
				cout << "Registration Number : " << temp[i].getRegistrationNumber() << endl;
				cout << "Make                : " << temp[i].getMake() << endl;
				cout << "Year of Manufacture : " << temp[i].getYearOfManufacture() << endl;
				cout << "Current Value       : " << temp[i].getCurrentValue() << endl;
				cout << endl;
			}
			break;
		case 7:
			cout << "\tReturn by Value" << endl;
			cout << "Enter Value : ";
			cin >> value;
			size = noOfVehicle;
			temp2 = v[0].returnByValue(v, value, size);
			if (size == 0)
			{
				cout << "No Data Found" << endl;
			}
			for (int i = 0; i < size; i++)
			{
				cout << "Registration Number : " << temp2[i].getRegistrationNumber() << endl;
				cout << "Make                : " << temp2[i].getMake() << endl;
				cout << "Year of Manufacture : " << temp2[i].getYearOfManufacture() << endl;
				cout << "Current Value: " << temp2[i].getCurrentValue() << endl;
				cout << endl;

			}
			break;
		case 8:
			cout << "\tReturn by year" << endl;
			cout << "Enter year : ";
			cin >> year;
			size = noOfVehicle;
			temp3 = v[0].returnByYear(v, year, size);
			if (size == 0)
			{
				cout << "No Data Found" << endl;
			}
			for (int i = 0; i < size; i++)
			{
				cout << "Registration Number : " << temp3[i].getRegistrationNumber() << endl;
				cout << "Make                : " << temp3[i].getMake() << endl;
				cout << "Year of Manufacture : " << temp3[i].getYearOfManufacture() << endl;
				cout << "Current Value       : " << temp3[i].getCurrentValue() << endl;
				cout << endl;
			}
			break;
		case 9:
			cout << "\tDeleting Vehicle" << endl;
			cout << "Enter Index [0," << noOfVehicle - 1 << "] : ";
			cin >> index;
			v->vehicleSold(v, index);
		}
		system("pause");
		system("cls");
	}
}
