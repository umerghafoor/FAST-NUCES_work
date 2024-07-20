#include<iostream>
#include<string>
using namespace std;

struct Date
{
	int dd;
	int mm;
	int yyyy;
	Date()
	{
		dd = 0;
		mm = 0;
		yyyy = 0;
	}
	Date(int dd,int mm,int yyyy)
	{
		this->dd = dd;
		this->mm = mm;
		this->yyyy = yyyy;
	}
	int daysInMonth()
	{
		int daysInMonth;
		if (mm == 2)
		{
			if ((yyyy % 4 == 0 && yyyy % 100 != 0) || yyyy % 400 == 0)
			{
				daysInMonth = 29;
			}
			else
			{
				daysInMonth = 28;
			}
		}
		else if (mm == 4 || mm == 6 || mm == 9 || mm == 11)
		{
			daysInMonth = 30;
		}
		else
		{
			daysInMonth = 31;
		}
		return daysInMonth;
	}
};

class Person
{
	string name;
	string address;
public:
	Person() 
	{
		name = "NULL";
		address = "NULL";
	}
	Person(string name,string address)
	{
		this->name = name;
		this->address = address;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setAddress(string address)
	{
		this->address = address;
	}
};
class Employee :public Person
{
	int employeeNumber;
	Date hireDate;
public:
	Employee()
	{
		employeeNumber = 0;
	}
	Employee(string name,string address,int employeeNum,Date hireDate)
		: Person(name, address)
	{
		this->employeeNumber = employeeNum;
		this->hireDate = hireDate;
	}
	void setEmployeeNum(int n)
	{
		employeeNumber = n;
	}
	void setHD(Date date)
	{
		hireDate.dd = date.dd;
		hireDate.mm = date.mm;
		hireDate.yyyy = date.yyyy;
	}
};
class ProductionWorker :public Employee
{
protected:
	int shift;
	double hourPay;
public:
	ProductionWorker()
	{
		shift = 0;
		hourPay = 0;
	}
	ProductionWorker(string name,string address, int employeeNum,Date hireDate, int shift, double hourlyPayRate)
		: Employee(name, address, employeeNum, hireDate), shift(shift)
	{
		this->hourPay = hourlyPayRate;
	}
	void setShift(int shift)
	{
		this->shift = shift;
	}
	void setHPR(double hourPay)
	{
		this->hourPay = hourPay;
	}
};
class TeamLeader :public ProductionWorker
{
	float monthlyBonus;
	int requiredHour;
	int numberOfHours;
public:
	TeamLeader()
	{
		monthlyBonus = 0;
		requiredHour = 0;
		numberOfHours = 0;
	}
	TeamLeader(string name, string address, int employeeNum, Date hireDate, int shift, double hourlyPayRate, double monthlyBonusAmount, int requiredTrainingHours, int attendedTrainingHours)
		: ProductionWorker(name, address, employeeNum, hireDate, shift, hourlyPayRate)
	{
		this->monthlyBonus = monthlyBonusAmount;
		this->requiredHour = requiredTrainingHours;
		this->numberOfHours = attendedTrainingHours;
	}
	double calculateSalary(Date date)
	{
		int daysInMonth = date.daysInMonth();
		int hoursWorked = daysInMonth * 8;
		double salary = hoursWorked * hourPay;
		if (numberOfHours >= requiredHour) 
		{
			salary += monthlyBonus;
		}
		return salary;
	}
};
int main()
{
	string name, address;
	int employeeNumber, shift;
	double hourlyPayRate;
	int hireMonth, hireDay, hireYear;
	double monthlyBonus;
	int requiredTrainingHours, attendedTrainingHours;

	cout << "\nEnter team leader information:" << endl;
	cout << "Name                       : ";
	cin.ignore();
	getline(cin, name);
	cout << "Address                    : ";
	getline(cin, address);
	cout << "Employee number            : ";
	cin >> employeeNumber;
	cout << "Hire date (mm dd yyyy)     : ";
	cin >> hireMonth >> hireDay >> hireYear;
	cout << "Shift (1 = day, 2 = night) : ";
	cin >> shift;
	cout << "Hourly pay rate            : ";
	cin >> hourlyPayRate;
	cout << "Monthly bonus              : ";
	cin >> monthlyBonus;
	cout << "Required training hours    : ";
	cin >> requiredTrainingHours;
	cout << "Attended training hours    : ";
	cin >> attendedTrainingHours;

	Date date(hireMonth, hireDay, hireYear);
	TeamLeader tl(name, address, employeeNumber, date, shift, hourlyPayRate, monthlyBonus, requiredTrainingHours, attendedTrainingHours);

	Date currentDate = { 10, 5, 2023 };
	double salary = tl.calculateSalary(currentDate);
	cout << "Team Leader's salary for the current month: $" << salary << endl;

	return 0;

	return 0;
}
