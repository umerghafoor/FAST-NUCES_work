#include <iostream>

using namespace std;
int main()
{
	int sec, min, day;
	cout<<"Enter seconds: ";
	cin>>sec;
	if (sec>=60)
	{
		if (sec>=3600)
		{if (sec>=86400)
		cout<<"Days: "<<sec/86400;
		else
		cout<<"Hours: "<<sec/3600;
		}
		else
		cout<<"Minutes: "<<sec/60;
		
	}
	else
	cout<<"Seconds :"<<sec;
	
}
