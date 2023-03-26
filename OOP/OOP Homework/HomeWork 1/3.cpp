#include <iostream>
using namespace std;

int CountDigit(int src)
{
	if (src == 0)
	{
		return 0;
	}
	else
	{
		src = src / 10;
		return CountDigit(src) + 1;
	}
}

int main()
{
	int src = 383838;
	cout << src << endl;
	cout << "Number of digits are " << CountDigit(src);
}