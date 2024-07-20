#include <iostream>

using namespace std;

int main()
{
	char c1[20], c2;
	char* pc1 = c1;
	char* pc2 = &c2;
	cout << "Enter a string : ";
	cin >> c1;
	cout << "Enter the Search term : ";
	cin >> c2;

	bool check = 0;
	
	for (int i = 0;*(pc1 + i) != '\0'; i++)
	{
		if (*(pc1 + i) == *pc2)
		{
			check = 1;
		}	
		if(check){ cout << *(pc1 + i); }
	}
}