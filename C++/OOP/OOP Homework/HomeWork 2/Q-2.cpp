/*Write a class to store the roll no., name, age (between 11 to 14) and address of students (more
than 10). Store the information of the students.
a. Write a function to print the names of all the students having age 14.
b. Write another function to print the names of all the students having even roll no.
c. Write another function to display the details of the student whose roll no is given (i.e.
roll no. entered by the user).*/
#include <iostream>
#include <string>

using namespace std;
const int studentNo = 10;
class student
{
	string name;
	int rollNo;
	int age;
	string address;
public:
	student()
	{
		name = "NULL";
		rollNo = 0;
		age = 0;
		address = "NULL";
	}
	student(string nameT, int rollNoT, int ageT, string addressT)
	{
		name = nameT;
		rollNo = rollNoT;
		age = ageT;
		address = addressT;
	}
	void Input()
	{
		cout << "\tName        : ";cin.ignore();getline(cin, name);
		cout << "\tRoll Number : ";cin >> rollNo;
		cout << "\tAge         : ";cin >> age;
		cout << "\tAddress     : ";cin.ignore(); getline(cin, address);
	}
	void PrintAgeFourteen()
	{
		if (age == 14)
		{
			cout << "Name : " << name << endl;
		}
	}
	void PrintEvenRoll()
	{
		if ((rollNo % 2) == 0)
		{
			cout << "Name : " << name << endl;
		}
	}
	void PrintStudent(int roll)
	{
		if (rollNo == roll)
		{

			cout << "-------------------------------------------" << endl;
			cout << "\tName        : " << name << endl;
			cout << "\tRoll Number : " << rollNo << endl;
			cout << "\tAge         : " << age << endl;
			cout << "\tAddress     : " << address << endl;
			cout << "-------------------------------------------" << endl;
		}
	}
};
int main()
{
	student s1[studentNo];
	int rollNo;
	bool enterData;
	s1[0] = { "Umer Ghafoor",2328,20,"Shakargarh, Narowal" };
	s1[1] = { "Abdullah",2349,19,"Sialkot" };
	s1[2] = { "Noor",2317,19,"KPK" };
	s1[3] = { "Umer Sani",2365,20,"wah cant" };
	s1[4] = { "Taha",2302,20,"bahria" };
	s1[5] = { "Asad Abdullah",2332,20,"Multan" };
	s1[6] = { "Huzafia",2346,21,"Jehlam" };
	s1[7] = { "Ali",2319,14,"Lahore" };
	s1[8] = { "Ahmad",2388,14,"karachi" };
	s1[9] = { "Waqas",2327,20,"Hedrabad" };

	cout << "1. Enter Data Manullay" << endl;
	cout << "0. Go with stored data" << endl;
	cin >> enterData;
	if (enterData) 
	{
		for (int i = 0; i < studentNo; i++)
		{
			cout << "Enter data of student no. " << i + 1 << endl;
			s1[i].Input();
		}
	}
	cout << "-------------------------------------------" << endl;
	for (int i = 0; i < studentNo; i++)
	{
		s1[i].PrintAgeFourteen();
	}
	cout << "-------------------------------------------" << endl;
	for (int i = 0; i < studentNo; i++)
	{
		s1[i].PrintEvenRoll();
	}
	cout << "-------------------------------------------" << endl;
	cout << "Enter Roll No. for Search : ";cin >> rollNo;
	for (int i = 0;i < studentNo;i++) 
	{
		s1[i].PrintStudent(rollNo);
	}
}