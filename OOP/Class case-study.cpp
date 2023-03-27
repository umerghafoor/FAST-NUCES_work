#include <iostream>
#include "Functions.h"

using namespace std;
class employee
{
	int empNumber;
	string empName;
	int empBasic;
	int empDa;
	int empIt;
	int empNetSal;
public:
	employee();
	employee(int, string, int, int, int, int);
	void getEmpDetail();
	void FindNetSalary();
	void ShowDetails();
};
int main()
{
	employee ee;
	ee.getEmpDetail();
	ee.ShowDetails();
}