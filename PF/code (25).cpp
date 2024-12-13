#include <iostream>
using namespace std;
int main()
{
	char x;
	cout<<"Enter a character: ";
	cin>>x;
if (x>='A'&& x<='Z' || x>='a'&& x<='z' || x>='0'&& x<='9')
{
		
		if(x>='A'&& x<='Z')
		cout<<"The given character is an Uppercase alphabet"<<endl;
		if(x>='a'&& x<='z')
		cout<<"The given character is an Lowercase alphabet"<<endl;
		if(x>='0'&& x<='9')
		cout<<"The given character is a single digit number"<<endl;
	}
		else
		cout<<"The given character is a special character";
	}
