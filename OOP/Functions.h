#include<iostream>

using namespace std;
employee::employee()
{
	empNumber = -1;
	empName = "Null";
	empDa = 0;
	empIt = 0;
	empBasic = 0;
	empNetSal = 0;
}
employee::employee(int empNumber, string empName, int empBasic, int empDa, int empIt, int empNetSal)
{
	this->empNumber = empNumber;
	this->empName = empName;
	this->empBasic = empBasic;
	this->empDa = empDa;
	this->empIt = empIt;
	this->empNetSal = empNetSal;
}

void employee::getEmpDetail()
{

	cout << "============= Enter details ==============" << endl;
	cout << "Enter Employ Number : ";cin >> empNumber;
	cout << "Enter Employ Name   : ";cin >> empName;
	cout << "Enter Employ Basic  : ";cin >> empBasic;
	cout << "Enter Employ DA     : ";cin >> empDa;
	cout << "Enter Employ IT     : ";cin >> empIt;
	cout << "==========================================" << endl;
}
void employee::FindNetSalary()
{

}
void employee::ShowDetails() 
{
	cout << "============= Show   details ==============" << endl;
	cout << "Employ Name       : " << empName;
	cout << "Employ Number     : " << empNumber;
	cout << "Employ Salery     : " << empBasic;
	cout << "Employ DA         : " << empDa;
	cout << "Employ TAX        : " << empIt;
	cout << "Employ Net Salary : " << empBasic + empDa - empIt;
	cout << "==========================================" << endl;
}