#include <iostream>

using namespace std;

bool Compare(char* c1, char* c2)
{
	for (int i = 0;i < 10;i++)
	{
		if (*(c1 + i) != *(c2 + i))
		{
			return 0;
		}
	}

	return 1;
}
int main()
{
	char c1[10], c2[10];

	cout << "Enter the first Array" << endl;
	cin >> c1;
	cout << "Enter the second Array" << endl;
	cin >> c2;
//	cout << c1;
//	cout << c2;
	if (Compare(c1, c2))
	{
		cout << "True\n";
	}
	else
	{
		cout << "False\n";
	}
	
}