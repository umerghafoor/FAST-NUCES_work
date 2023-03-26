#include <iostream>

using namespace std;

const int number = 2;

struct Car
{
	string Model;
	unsigned int Year;
	unsigned int price;
	void Dispaly(int i)
	{
		cout << "+++++++++++++++ CAR NUMBER " << i << " +++++++++++++ + " << endl;
		cout << "Model    \t: " << Model << endl;
		cout << "Year     \t: " << Year << endl;
		cout << "Price    \t: " << price << endl;
	}
	void Input(int i)
	{
		cout << "+++++++++++++++ Enter data for car " << i << " +++++++++++++++" << endl;
		cout << "Enter Car Model \t: ";cin >> Model;
		cout << "Enter Car Year  \t: ";cin >> Year;
		cout << "Enter Car Price \t: ";cin >> price;
	}
};

void main()
{
	Car car[number];
	for (int i = 0;i < number;i++)
	{
		car[i].Input(i);
	}
	for (int i = 0;i < number;i++) 
	{
		car[i].Dispaly(i);
	}
}

// Phone Directry Code
//#include <iostream>
//
//using namespace std;
//
//struct Address
//{
//	string City;
//	string Company;
//	void Dispaly()
//	{
//		cout << "City    \t: "<< City << endl;
//		cout << "Company \t: "<< Company << endl;
//	}
//	void Input()
//	{
//		cout << "Enter Company Name \t: ";cin >> Company;
//		cin.ignore();
//		cout << "Enter City Name \t: ";cin >> City;
//	}
//};
//struct PhoneDirectry
//{
//	string name;
//	string phoneNumber;
//	Address address;
//	void Dispaly()
//	{
//		cout << "Name    \t: " << name << endl;
//		cout << "Company \t: " << phoneNumber << endl;
//		address.Dispaly();
//	}
//	void Input()
//	{
//		cout << "Enter Your Name \t: ";cin >> name;
//		cin.ignore();
//		cout << "Enter Phone Number \t: ";cin >> phoneNumber;
//		cin.ignore();
//		address.Input();
//	}
//};
//
//void main()
//{
//		PhoneDirectry p2[2];
//	Address a2;
//	//a2.Input();
//	p2[1].Input();
//	//cout << "//////////////         For Address        ////////////" << endl;
//	//a2.Dispaly();
//	cout << "+++++++++++++++    For Phone Directectry   +++++++++++++++" << endl << endl;
//	p2[1].Dispaly();
//}