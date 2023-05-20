#include<iostream>
using namespace std;

class Employee 
{
protected:
    string firstName;
    string lastName;
    string CNICNumber;

public:
    Employee() 
    {
        firstName = "";
        lastName = "";
        CNICNumber = "";
    }
    Employee(string fName, string lName, string cnic)
    {
        firstName = fName;
        lastName = lName;
        CNICNumber = cnic;
    }
    string getFirstName(){ return firstName; }
    void setFirstName(string fName) { firstName = fName; }
    string getLastName() { return lastName; }
    void setLastName(string lName) { lastName = lName; }
    string getCNICNumber() { return CNICNumber; }
    void setCNICNumber(string cnic) { CNICNumber = cnic; }

    virtual double earnings() { return 0.00; }
};

class SalariedEmployee : public Employee 
{
private:
    double weeklySalary;
public:
    SalariedEmployee() : Employee() 
{
        weeklySalary = 0.0;
    }

    SalariedEmployee(string fName, string lName, string cnic, double salary) : Employee(fName, lName, cnic) 
    {
        weeklySalary = salary;
    }

    void setWeeklySalary(double salary) 
    {
        weeklySalary = salary;
    }

    double getWeeklySalary() 
    {
        return weeklySalary;
    }

    virtual double earnings() 
    {
        return weeklySalary;
    }
};

class CommissionEmployee : public Employee {
private:
    double grossSales;
    double commissionRate;

public:
    CommissionEmployee() : Employee() 
    {
        grossSales = 0.0;
        commissionRate = 0.0;
    }

    CommissionEmployee(string firstName, string lastName, string cnicNumber, double grossSales, double commissionRate) 
        : Employee(firstName, lastName, cnicNumber) 
    {
        setGrossSales(grossSales);
        setCommissionRate(commissionRate);
    }

    double getGrossSales()
    {
        return grossSales;
    }

    double getCommissionRate()
    {
        return commissionRate;
    }

    void setGrossSales(double grossSales) 
    {
        if (grossSales >= 0) {
            this->grossSales = grossSales;
        }
    }

    void setCommissionRate(double commissionRate) 
    {
        if (commissionRate >= 0) 
        {
            this->commissionRate = commissionRate;
        }
    }

    double earnings()
    {
        return grossSales * commissionRate;
    }
};

int main()
{
    const int numEmployees = 1;

    Employee* employees[numEmployees];

    for (int i = 0; i < numEmployees; i++)
    {
        cout << "\nEmployee " << i + 1 << endl;
        cout << "Enter first name: ";
        string fName;
        cin >> fName;

        cout << "Enter last name: ";
        string lName;
        cin >> lName;

        cout << "Enter CNIC number: ";
        string cnic;
        cin >> cnic;

        cout << "Choose employee type " << endl;
        cout << "1. Salaried Employee" << endl;
        cout << "2. Commission Employee" << endl;
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter weekly salary: ";
            double salary;
            cin >> salary;
            employees[i] = new SalariedEmployee(fName, lName, cnic, salary);
        }
        else if (choice == 2)
        {
            cout << "Enter gross sales       : ";
            double sales;
            cin >> sales;
            cout << "Enter commission rate   : ";
            double rate;
            cin >> rate;
            employees[i] = new CommissionEmployee(fName, lName, cnic, sales, rate);
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            i--;
        }
    }

    cout << "Earnings" << endl;
    for (int i = 0; i < numEmployees; i++)
    {
        cout << employees[i]->getFirstName() << " " << employees[i]->getLastName() << " : $" << employees[i]->earnings() << endl;
    }

    return 0;
}