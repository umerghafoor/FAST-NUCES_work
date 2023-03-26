#include <iostream>
using namespace std;

bool Palindrome(char src[], int i)
{
	if (src[i] == '\0')
	{
		return 1;
	}
	else
	{
		if (src[strlen(src) - 1 - i] != src[i])
		{
			return 0;
		}
		Palindrome(src, i + 1);
	}
}

int main()
{
	char src[20] = "hegeh";

	if (Palindrome(src, 0))
		cout << "Number is Palindrome";
	else
		cout << "Number is not Palindrome";

}