#include <iostream>
using namespace std;
struct name
{
	char fName[20];
	char lName[20];

	void Input()
	{
		cout << "Enter student first Name : ";cin >> fName;
		cout << "Enter student last Name  : ";cin >> lName;
	}
};
struct student
{
	int regNo;
	name studentName;
	int marks[5];
	float gpa;

	void Input()
	{
		cout << "Enter student Reg No.  : ";cin >> regNo;
		studentName.Input();
		for (int i = 0;i < 5;i++)
		{
			cout << "Enter Marks of subject " << i + 1 << " : ";cin >> marks[i];
		}
	}
	float CalculateGPA()
	{
		float average = 0;
		for (int i = 0;i < 5;i++)
		{
			average += marks[i];
		}
		average = average / 5;
		if (average < 50)
		{
			gpa = 0;
		}
		else if (average >= 50 && average < 60)
		{
			gpa= 1.80;
		}
		else if (average >= 60 && average < 70)
		{
			gpa= 2.87;
		}
		else if (average >= 70 && average < 80)
		{
			gpa= 3.10;
		}
		else if (average >= 80 && average < 90)
		{
			gpa= 3.62;
		}
		else if (average >= 90 && average <= 100)
		{
			gpa= 4;
		}
		return gpa;
	}
	void PrintGThree()
	{
		CalculateGPA();
		if (gpa > 3)
		{
			cout << studentName.fName << '\t' << regNo << '\t' << gpa << endl;
		}
	}
	void Print()
	{
		cout << studentName.fName << '\t' << regNo << '\t' << gpa << endl;
	}
};
int main()
{
	int NoStudents;
	cout << "Enter the number of students : ";cin >> NoStudents;
	student* s = new student[NoStudents];

	for (int i = 0;i < NoStudents;i++)
	{
		cout << "--------------- Enter " << i + 1 << " ---------------" << endl;
		s[i].Input();
	}

	student temp = s[0];
	for (int i = 0;i < NoStudents;i++)
	{
		s[i].CalculateGPA();
	}
	for (int i = 0; i < NoStudents; i++)
	{
		for (int j = i + 1; j < NoStudents; j++) 
		{
			if (s[i].gpa < s[j].gpa)
			{	temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}

	cout << "=================== GPA > 3  ===================" << endl;
	cout << "Name" << '\t' << "regNo" << '\t' << "gpa" << endl;
	for (int i = 0;i < NoStudents;i++)
	{
		s[i].PrintGThree();
	}
	cout << "=================== Print All  ===================" << endl;
	cout << "Name" << '\t' << "regNo" << '\t' << "gpa" << endl;
	for (int i = 0;i < NoStudents;i++)
	{
		s[i].PrintGThree();
	}
}