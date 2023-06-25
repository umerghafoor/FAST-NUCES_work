#include <iostream>
using namespace std;

void Reverse(char src[], char dest[], int i)
{
	if (src[i] == '\0')
	{
		dest[i] = '\0';
		return;
	}
	else
	{
		dest[strlen(src) - 1 - i] = src[i];
		Reverse(src, dest, i + 1);
	}
}

int main()
{
	char src[20] = "Hello World", dest[20];

	Reverse(src, dest, 0);
	cout << src << endl;
	cout << dest << endl;
}