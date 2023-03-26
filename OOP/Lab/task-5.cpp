#include <iostream>

using namespace std;

const int siz = 20;

void Swap(char* c1, char* c2)
{
	char temp[siz];
	for (int i = 0;i < siz;i++)
	{
		temp[i] = *(c1 + i);
	}
	for (int i = 0;i < siz;i++)
	{
		*(c1 + i) = *(c2 + i);
	}
	for (int i = 0;i < siz;i++)
	{
		*(c2 + i) = temp[i];
	}

}
int main()
{
	char c1[siz], c2[siz];

	cout << "Enter the first Array" << endl;
	cin >> c1;
	cout << "Enter the second Array" << endl;
	cin >> c2;
	
	Swap(c1, c2);
	cout << "First Array   : " << c1 << endl;
	cout << "Second Array  : " << c2 << endl;

}