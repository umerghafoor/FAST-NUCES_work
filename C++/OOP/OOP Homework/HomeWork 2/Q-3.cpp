/*Write a class to store the name, account number and balance of customers and store their
information.
1 - Write a function to print the names of all the customers having balance less than $200.
2 - Write a function to add $100 in the balance of all the customers having more than $1000 in
their balance and then print the incremented value of their balance.*/
#include <iostream>
#include <string>

using namespace std;
const int No = 10;
class account
{
	string name;
	int accountNo;
	int balance;
	string address;
public:
	account()
	{
		name = "NULL";
		accountNo = 0;
		balance = 0;
	}
	account(string nameT, int accountNoT, int balanceT)
	{
		name = nameT;
		accountNo = accountNoT;
		balance = balanceT;
	}
	void Input()
	{
		cout << "\tName        : ";cin.ignore();getline(cin, name);
		cout << "\tAccount Number : ";cin >> accountNo;
		cout << "\tBalance         : ";cin >> balance;
	}
	void LessthanZero()
	{
		if (balance < 200)
		{
			cout << "\tName   : " << name << endl;
		}
	}
	void AddHundred()
	{
		if (balance > 1000)
		{
			balance += 100;
			cout << "---------------------------------------" << endl;
			cout << "\tName    : " << name << endl;
			cout << "\tBalance : $" << balance << endl;
		}
	}

};
int main()
{
	account a1[No];
	int rollNo;
	bool enterData;
	a1[0] = { "Umer Ghafoor",2328,200};
	a1[1] = { "Abdullah",2349,190};
	a1[2] = { "Noor",2317,1900};
	a1[3] = { "Umer Sani",2365,200};
	a1[4] = { "Taha",2302,200};
	a1[5] = { "Asad Abdullah",2332,200};
	a1[6] = { "Huzafia",2346,210};
	a1[7] = { "Ali",2319,1400};
	a1[8] = { "Ahmad",2388,1400};
	a1[9] = { "Waqas",2327,2000};

	cout << "1. Enter Data Manullay" << endl;
	cout << "0. Go with stored data" << endl;
	cin >> enterData;
	if (enterData)
	{
		for (int i = 0; i < No; i++)
		{
			cout << "Enter data of customer no. " << i + 1 << endl;
			a1[i].Input();
		}
	}
	cout << "=========================================" << endl;
	for (int i = 0;i < No;i++)
	{
		a1[i].LessthanZero();
	}
	cout << "=========================================" << endl;
	for (int i = 0;i < No;i++)
	{
		a1[i].AddHundred();
	}
}