#include <iostream>
#include<iomanip>
using namespace std;
int main()
{

int n1, n2, n3, n4, n5;
cout<<"Enter five integers: "<<endl;

cout<<"N1=";
cin>>n1;
cout<<"N2=";
cin>>n2;
cout<<"N3=";
cin>>n3;
cout<<"N4=";
cin>>n4;
cout<<"N5=";
cin>>n5;
int scale;
cout<<"Enter the value of the scale: ";
cin>>scale;

	cout<<setfill('*')<<setw(n1*scale)<<""<<endl;
	cout<<setfill('*')<<setw(n2*scale)<<""<<endl;
	cout<<setfill('*')<<setw(n3*scale)<<""<<endl;
	cout<<setfill('*')<<setw(n4*scale)<<""<<endl;
	cout<<setfill('*')<<setw(n5*scale)<<""<<endl;

return 0;
}



