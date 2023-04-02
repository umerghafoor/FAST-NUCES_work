#include <iostream>

using namespace std;

struct address
{
	char city[20];
	int postcode;
	char emailId[20];
};
struct salary
{
	int year;
	float grossSalary;
};
struct tax
{
	int year;
	float taxDue;
	float netSalary;
};
struct employee
{
	char name[20];
	int scale;
	salary yearlySalary[3];
	tax yearlyTax[3];
	address addr;
	employee* next;
};

void calculateTax(employee* emp) 
{
    for (int i = 0; i < 3; i++) 
    {
        if (emp->scale >= 1 && emp->scale <= 10) 
        {
            emp->yearlyTax[i].taxDue = emp->yearlySalary[i].grossSalary * 0.05;
        }
        else if (emp->scale >= 11 && emp->scale <= 17) 
        {
            emp->yearlyTax[i].taxDue = emp->yearlySalary[i].grossSalary * 0.075;
        }
        else 
        {
            emp->yearlyTax[i].taxDue = 0;
        }
        emp->yearlyTax[i].year = emp->yearlySalary[i].year;
        emp->yearlyTax[i].netSalary = emp->yearlySalary[i].grossSalary - emp->yearlyTax[i].taxDue;
    }
}

int main()
{
    employee* empPtr = NULL;
    employee* prevEmp = NULL;
    employee* currentEmp = empPtr;
    int x = 1;
    int n = 0;
    int netSal = 0;
    float tax = 0;
    int highTax = 0;
    while (x != 0) {
        cout << "1 Enter data" << endl;
        cout << "2 Display data" << endl;
        cout << "3 Highest Tax" << endl;
        cout << "Enter choice : ";cin >> x;
        switch (x) {
        case 1:
            cout << "Enter No. Employee : ";cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "-------------------- Enter " << i + 1 << " --------------------" << endl;
                employee* emp = new employee;
                emp->next = NULL;

                cout << "Enter name : ";
                cin >> emp->name;

                cout << "Enter scale (1 to 17) : ";
                cin >> emp->scale;

                for (int j = 0; j < 3; j++)
                {
                    cout << "Enter gross salary for year " << j + 1 << " : ";
                    cin >> emp->yearlySalary[j].grossSalary;
                    emp->yearlySalary[j].year = 2023 - j;
                }

                cout << "Enter city : ";
                cin >> emp->addr.city;

                cout << "Enter postcode : ";
                cin >> emp->addr.postcode;

                cout << "Enter email id : ";
                cin >> emp->addr.emailId;

                calculateTax(emp);

                if (prevEmp != NULL)
                {
                    prevEmp->next = emp;
                }
                else
                {
                    empPtr = emp;
                }
                prevEmp = emp;
            }
            break;
        case 2:
            cout << "====================== All Data ======================" << endl;
            currentEmp = empPtr;
            while (currentEmp != NULL)
            {
                cout << "Name                 : " << currentEmp->name << endl;
                cout << "Scale                : " << currentEmp->scale << endl;
                cout << endl;
                netSal = 0;
                for (int i = 0; i < 3; i++)
                {
                    cout << "\tFor Year " << i + 1 << endl;
                    cout << "Gross salary     : " << currentEmp->yearlySalary[i].grossSalary << endl;
                    cout << "Yearly tax       : " << currentEmp->yearlyTax[i].taxDue << endl;
                    cout << "Net salary       : " << currentEmp->yearlyTax[i].netSalary << endl;
                    netSal += currentEmp->yearlyTax[i].netSalary;
                }
                cout << endl;
                cout << "Average Net Salary   : " << netSal / 3 << endl;
                cout << "City                 : " << currentEmp->addr.city << endl;
                cout << "Postcode             : " << currentEmp->addr.postcode << endl;
                cout << "Email ID             : " << currentEmp->addr.emailId << endl;

                cout << "------------------------------------------" << endl;
                currentEmp = currentEmp->next;
            }
            break;
        case 3:
            currentEmp = empPtr;
            cout << "====================== Highest Tax ======================" << endl;
            for (int i=0;currentEmp != NULL;i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (currentEmp->yearlyTax[i].taxDue > tax)
                    {
                        highTax = i;
                    }
                }
                currentEmp = currentEmp->next;
            }
            currentEmp = empPtr;
            cout << highTax;
            for (int i = 0;currentEmp != NULL;i++)
            {
                if (highTax == i) 
                {
                    cout << "Name                 : " << currentEmp->name << endl;
                    cout << "City                 : " << currentEmp->addr.city << endl;
                    cout << "Postcode             : " << currentEmp->addr.postcode << endl;
                    cout << "Email ID             : " << currentEmp->addr.emailId << endl;
                    cout << "------------------------------------------" << endl;
                }
                currentEmp = currentEmp->next;
            }
            break;
        }
        system("pause");
        system("cls");
    }
}