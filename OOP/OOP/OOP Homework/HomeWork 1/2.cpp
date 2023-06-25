#include <iostream>
using namespace std;

void Search(char src[], int i)
{
	if (src[i] == '\0')
	{
		return;
	}
	else
	{
		if (src[i] == 'a' || src[i] == 'e' || src[i] == 'i' || src[i] == 'o' || src[i] == 'u' ||
			src[i] == 'A' || src[i] == 'E' || src[i] == 'I' || src[i] == 'O' || src[i] == 'U' )
		{
			cout << src[i] << ' ';
		}
		Search(src, i + 1);
	}
}

int main()
{
	char src[20] = "Hello World";
	cout << src << endl;
	cout << "Vowels are ";
	Search(src, 0);
}