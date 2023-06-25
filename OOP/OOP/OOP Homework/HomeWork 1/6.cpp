#include <iostream>
using namespace std;

void PrintEven(int src[], int i)
{
	if (src[i] == '\0')
	{
		return;
	}
	else
	{
		if (src[i]%2==0)
		{
			cout << src[i] << ' ';
		}
		PrintEven(src, i + 1);
	}
}

int main()
{
	int src[20] = { 1,2,3,2,3,4,5,4,5 };
	cout << "Even Numbers are ";
	PrintEven(src, 0);
}