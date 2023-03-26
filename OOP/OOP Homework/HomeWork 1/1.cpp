#include <iostream>
using namespace std;

void Copy(char src[], char dest[], int i)
{
	if (src[i] == '\0')
	{
		dest[i] = '\0';
		return;
	}
	else
	{
		dest[i] = src[i];
		Copy(src, dest, i + 1);
	}
}

int main()
{
	char src[20]="Hello World", dest[20];
	Copy(src, dest, 0);
	cout << src << endl;
	cout << dest << endl;
}