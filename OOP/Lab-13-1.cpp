#include<iostream>
#include <string>
using namespace std;
/*
Class Person holds
 Two attributes i.e. name and year_of_birth
 A two-argument constructor to initialize its data members with user-defined
values
*/
class Person
{
protected:
	string name;
	int YOB;
public:
	Person(string name, int yearOfBirth)
	{
		this->name = name;
		this->YOB = yearOfBirth;
	}
};


/*
• Class Student has
 Two attributes i.e. studentID and enrolledSemester
 A four-argument constructor to initialize its data members (including inherited
data members) o A function named display() to show the values of all attributes
(including inherited attributes)
*/
class Student : public Person
{
	int SID;
	int enrolledSemester;
public:
	Student(string name, int yearOfBirth, int studentID, int enrolledSemester) : Person(name, yearOfBirth)
	{
		this->SID = studentID;
		this->enrolledSemester = enrolledSemester;
	}
	void display() const 
	{
		cout << "Name               : " << Person::name << endl;
		cout << "Year of Birth      : " << Person::YOB << endl;
		cout << "Student ID         : " << SID << endl;
		cout << "Enrolled Semester  : " << enrolledSemester << endl;
	}
};
/*
• Class Employee contains
 Five attributes i.e. employeeID, joiningYear, jobTitle (designation of an employee),
courseID, and courseTitle
*/
class Employee : public Person
{
protected:
	int employeeID;
	int joiningYear;
	string jobTitle;
	int courseID;
	string courseTitle;
public:
	Employee(string name, int yearOfBirth, int employeeID, int joiningYear, string jobTitle, int courseID, string courseTitle) : Person(name, yearOfBirth) 
	{
		this->employeeID = employeeID;
		this->joiningYear = joiningYear;
		this->jobTitle = jobTitle;
		this->courseID = courseID;
		this->courseTitle = courseTitle;
	}
	void setJobTitle(string jobTitle)
	{
		this->jobTitle = jobTitle;
	}
	string getJobTitle()
	{
		return jobTitle;
	}
};
/*
• Class Administration has
 A parameterized constructor to receive five arguments to initialize inherited
attributes from class (Concerning courseID and courseTitle, only null value is
allowed to set for an admin officer)
 Two functions i.e. setJobTitle(employee) and getJobTitle(employee) to set and get
job title of an employee
*/
class Administration :public Employee
{
public:
	Administration(int employeeID, int joiningYear, string jobTitle)
		: Employee("NULL", 0, employeeID, joiningYear, jobTitle, 0, "NULL")
	{

	}
	void setJobTitle(Employee& employee, string jobTitle) {
		employee.setJobTitle(jobTitle);
	}
	string getJobTitle(Employee employee) {
		return employee.getJobTitle();
	}
    void display() 
    {
        cout << "Employee ID    : " << employeeID << endl;
        cout << "Name           : " << name << endl;
        cout << "Joining Year   : " << joiningYear << endl;
        cout << "Job Title      : " << jobTitle << endl;
    }
};
/*
• Class Academic has
 A parameterized constructor to receive five arguments to initialize inherited
attributes from class (Concerning employeeID, joiningYear, and jobTitle, only null
value is allowed to set)
 Two functions i.e. setCourseID() and setCourseTitle()
*/
class Academic : public Employee 
{
public:
	Academic(string name, int yearOfBirth, int courseID, string courseTitle)
		: Employee(name, yearOfBirth, 0, 0, "", courseID, courseTitle)
	{
	}

	void setCourseID(int courseID) {
		this->courseID = courseID;
	}

	void setCourseTitle(string courseTitle) {
		this->courseTitle = courseTitle;
	}
    void display() 
    {
        cout << "Name             : " << name << endl;
        cout << "Year of Birth    : " << YOB << endl;
        cout << "Course ID        : " << courseID << endl;
        cout << "Course Title     : " << courseTitle << endl;
    }

};

int main() {


    string name;
    int birthYear;
    int id;
    int year;
    string jobTitle;
    string courseTitle;
    int courseID;

    int choice = 1;

    while (choice != 0)
    {
        cout << "1. Set Student information" << endl;
        cout << "2. Set academic course ID and title" << endl;
        cout << "3. Set administration job title" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == 1) 
        {
            cout << "Enter student name : ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter birth year   : ";
            cin >> birthYear;
            cout << "Enter student ID   : ";
            cin >> id;
            cout << "Enter student year : ";
            cin >> year;
            Student student1(name, birthYear, id, year);
            cout << "================== Display ===================" << endl;
            student1.display();
        }
        if (choice == 2)
        {
            cout << "Enter academic employee name : ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter birth year             : ";
            cin >> birthYear;
            cout << "Enter employee ID            : ";
            cin >> id;
            cout << "Enter course ID              : ";
            cin >> courseID;
            cin.ignore();
            cout << "Enter course title           : ";
            getline(cin, courseTitle);
            Academic academic1(name, birthYear, id, courseTitle);
            academic1.setCourseID(courseID);
            academic1.setCourseTitle(courseTitle);
            cout << "================== Display ===================" << endl;
            academic1.display();
        }
        if (choice == 3)
        {
            cout << "Enter administration employee name : ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter join year                    : ";
            cin >> year;
            cout << "Enter employee ID                  : ";
            cin >> id;
            cout << "Enter job title                    : ";
            cin.ignore();
            getline(cin, jobTitle);
            Academic academic2(name, year, id, courseTitle);
            Administration admin1(id, year, jobTitle);
            admin1.setJobTitle(academic2, jobTitle);
            cout << "================== Display ===================" << endl;
            admin1.display();
        }
        system("pause");
        system("cls");
    }
    return 0;
}