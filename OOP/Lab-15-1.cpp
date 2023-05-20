/*
Two classes, Student and Teacher, both derived from a common abstract class Person.
2. Person should have two pure virtual functions
 display()
 readData().
3. The Student class should have the following data members:
 name (string) 
 rollNo (integer) 
 marks (an array of integers) 
 numSubjects (integer)

4. The Teacher class should have the following data members: 
 name (string) 
 empId (integer) 
 department (string) 
 numSubjects (integer)

5. The program should allow the user to enter the details of students and teachers using the 
readData() function, and display the details using the display()
function.*/

#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	virtual void readData() = 0;
	virtual void displayData() = 0;
    virtual bool searchByName(string searchName) = 0;
    virtual int getID() = 0;
    virtual bool isStudent() = 0;
};
class Student : public Person {
	string name;
	int rollNo;
	int marks;
	int numSubjects;

public:
	Student() {
		name = "";
		rollNo = -1;
		marks = -1;
		numSubjects = -1;
	}
	void readData() {
		cout << "Enter student name: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter roll number: ";
		cin >> rollNo;

		cout << "Enter marks: ";
		cin >> marks;

		cout << "Enter number of subjects: ";
		cin >> numSubjects;
	}
	void displayData() override {
		cout << "Name         : " << name << endl;
		cout << "Roll No.     : " << rollNo << endl;
		cout << "Marks        : " << marks << endl;
		cout << "No. Subjects : " << numSubjects << endl;
	}
    bool searchByName(string searchName) 
    {
        return name == searchName;
    }
    int getID()
    {
        return rollNo;
    }
    bool isStudent()
    {
        return 1;
    }
};
class Teacher : public Person {
	string name;
	int empId;
	string department;
	int numSubjects;

public:
	void readData() {
		cout << "Enter teacher name: ";
		cin.ignore();
		getline(cin, name);

		cout << "Enter employee ID: ";
		cin >> empId;

		cout << "Enter department: ";
		cin.ignore();
		getline(cin, department);

		cout << "Enter number of subjects: ";
		cin >> numSubjects;
	}
	void displayData() override {
		cout << "Name         : " << name << endl;
		cout << "Employee Id  : " << empId << endl;
		cout << "Department   : " << department << endl;
		cout << "No. Subjects : " << numSubjects << endl;
	}
    bool searchByName(string searchName) 
    {
        return name == searchName;
    }
    int getID()
    {
        return empId;
    }
    bool isStudent()
    {
        return 0;
    }
};

int main() {
    const int MAX_PERSONS = 100;
    Person* persons[MAX_PERSONS];
    int numPersons = 0;

    int choice = 1;
    while (choice!=0) 
    {
        cout << "1. Add a new student" << endl;
        cout << "2. Add a new teacher" << endl;
        cout << "3. Display details of all students" << endl;
        cout << "4. Display details of all teachers" << endl;
        cout << "5. Search for a person by name" << endl;
        cout << "6. Search for a person by roll number/employee ID" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice) {
        case 1: 
        {
            persons[numPersons] = new Student();
            persons[numPersons]->readData();
            numPersons++;
            cout << "Student added successfully!" << endl;
            break;
        }
        case 2: 
        {

            persons[numPersons] = new Teacher();
            persons[numPersons]->readData();
            numPersons++;
            cout << "Teacher added successfully!" << endl;

            break;
        }
        case 3: 
        {
            for (int i = 0; i < numPersons; i++)
            {
                if(persons[i]->isStudent())
                persons[i]->displayData();
                cout << endl;
            }
            break;
        }
        case 4: {
            for (int i = 0; i < numPersons; i++)
            {
                if (!persons[i]->isStudent())
                persons[i]->displayData();
                cout << endl;
            }
            break;
        }
        case 5: 
        {
            string searchName;
            cout << "Enter the name to search : ";
            cin.ignore();
            getline(cin, searchName);

            bool found = false;
            for (int i = 0; i < numPersons; i++) {
                if (persons[i]->searchByName(searchName)) {
                    persons[i]->displayData();
                    found = true;
                    cout << endl;
                }
            }
            if (!found) 
            {
                cout << "Person not found." << endl;
            }
            break;
        }
        case 6: {
            int searchId;
            cout << "Enter the roll number/employee ID to search : ";
            cin >> searchId;

            bool found = false;
            for (int i = 0; i < numPersons; i++) {
                if ((persons[i])->getID() == searchId) 
                {
                    persons[i]->displayData();
                    found = true;
                    cout << endl;
                    break;
                }
            }
            if (!found) {
                cout << "Person not found." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        system("pause");
        system("cls");

    }

    for (int i = 0; i < numPersons; i++) 
    {
        delete persons[i];
    }

    return 0;
}