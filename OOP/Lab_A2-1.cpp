#include <iostream>
#include <string>
using namespace std;

class Professor;

class Person 
{
    string name;
    int age;
    string address;
public:
    Person(){}
    Person(string name, int age, string address)
    {
        this->name = name;
        this->age = age;
        this->address = address;

    }
    string getName() { return name; }
    int getAge() { return age; }
    string getAddress() { return address; }
    Person& operator+=(string lastName)
    {
        string newName = name + " " + lastName;
        this->name = newName;
        return *this;
    }
};


class Student : public Person 
{
    int studentId;
    string coursesTaken;
public:
    Student(){}
    Student(string name, int age, string address, int studentId, string coursesTaken)
        : Person(name, age, address)
    {
        this->studentId = studentId;
        this->coursesTaken = coursesTaken;
    }
    int getStudentId() { return studentId; }
    string getCoursesTaken() { return coursesTaken; }
};

class Professor : public Person 
{
    string subjectTaught;
    int yearsOfExperience;
    Student student;
public:
    Professor(){}
    Professor(string name, int age, string address, string subjectTaught, int yearsOfExperience,Student student)
        : Person(name, age, address)
    {
        this->subjectTaught = subjectTaught;
        this->yearsOfExperience = yearsOfExperience;
        this->student = student;
    }
    string getSubjectTaught() { return subjectTaught; }
    int getYearsOfExperience() { return yearsOfExperience; }
    string getStudentName()
    {
        return student.getName();
    }

};

int main()
{
    string temp;
    Student* s{};
    Professor* p{};
    bool professer = 0, student = 0;
    int choice = 1;
    while (choice != 0)
    {
        cout << "1. Add a student Data" << endl;
        cout << "2. Add a professor Data" << endl;
        cout << "3. Add a last name (Operator overloading)" << endl;
        cout << "5. Print all people" << endl;
        cout << "0. Quit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, address, coursesTaken;
            int age, studentId;

            cout << "Enter name          : ";
            cin >> name;
            cout << "Enter age           : ";
            cin >> age;
            cout << "Enter address       : ";
            cin >> address;
            cout << "Enter student ID    : ";
            cin >> studentId;
            cout << "Enter courses taken : ";
            cin >> coursesTaken;

            s = new Student(name, age, address, studentId, coursesTaken);
            student = 1;
        }
        else if (choice == 2)
        {
            if (student)
            {
                string name, address, subjectTaught;
                int age, yearsOfExperience;

                cout << "Enter name                 : ";
                cin >> name;
                cout << "Enter age                  : ";
                cin >> age;
                cout << "Enter address              : ";
                cin >> address;
                cout << "Enter subject taught       : ";
                cin >> subjectTaught;
                cout << "Enter years of experience  : ";
                cin >> yearsOfExperience;

                p = new Professor(name, age, address, subjectTaught, yearsOfExperience, *s);
                professer = 1;
            }
            else
            {
                cout << "First create the student which willbe relation with teach" << endl;
            }
        }
        else if (choice==3)
        {
            if (professer && student)
            {
                cout << "Enter last name of Student : ";
                cin >> temp;
                *s += temp;

                cout << "Enter last name of Teacher : ";
                cin >> temp;
                *p += temp;
            }
            else
            {
                cout << "First create the object" << endl;
            }
        }
        else if (choice == 5)
        {
            if (professer)
            {
                cout << "\t For Professor\n";
                cout << "Name                  : " << p->getName() << endl;
                cout << "Age                   : " << p->getAge() << endl;
                cout << "Address               : " << p->getAddress() << endl;
                cout << "Subject taught        : " << p->getSubjectTaught() << endl;
                cout << "Years of experience   : " << p->getYearsOfExperience() << endl;
                cout << "Teaches (Association) : " << p->getStudentName() << endl;
            }
            if (student)
            {
                cout << "\t For Student\n";
                cout << "Name                  : " << s->getName() << endl;
                cout << "Age                   : " << s->getAge() << endl;
                cout << "Address               : " << s->getAddress() << endl;
                cout << "Student ID            : " << s->getStudentId() << endl;
                cout << "Courses taken         : " << s->getCoursesTaken() << endl;
            }
            if (!professer && !student)
            {
                cout << "First create the object" << endl;
            }
        }

        system("pause");
        system("cls");
    }


    return 0;
}