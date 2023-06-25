#include<iostream>
using namespace std;
class Roles
{
private:
	Admin* admin;
	Customer* customer;
	Vendor* vendor;
public:

};
class Admin
{
private:
	ID adminID;
};
class Customer
{
private:
	ID customerID;
};
class Vendor
{
	ID vendorID;
};
class Items
{
	string itemsName;
	int itemsPrice;
};
class Cart
{
	Items item[];
	int total;
};
class Payment
{
	
};
class Report
{
	
};
class Inventory
{
	
};
class ID
{
	string adminID;
	string adminPassword;
};
int main()
{
	
}