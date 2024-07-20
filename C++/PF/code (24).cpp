#include <iostream>
using namespace std;
int main ()
{
	int day, month , year;
	cout<<"Enter day: ";
	cin>>day;
	cout<<"Enter month in numeric form: ";
	cin>>month;
	cout<<"Enter year two digits: ";
	cin>>year;
	if (year==(month*day))
	{
		cout<<"Your date is magic.";
	}
	else
	cout<<"Your date is not magic.";
}
