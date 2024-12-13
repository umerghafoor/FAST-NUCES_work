#include <iostream>
using namespace std;
int main()
{
    int a, b, B ,c ,C ,d ,D ,e ,E ,f ,F;
    cout<<"Enter number of eggs = ";
    cin>>a;
    cout<<endl;

    b=a/30;
    B=a%30;
    cout<<"For 30 Packing"<<endl<<"Number of packings are "<<b<<" and number of egss  left are "<<B<<endl<<endl;
    
    c=a/24;
    C=a%24;
    cout<<"For 24 Packing"<<endl<<"Number of packings are "<<c<<" and number of egss  left are "<<C<<endl<<endl;
    
	d=a/18;
    D=a%18;  
    cout<<"For 18 Packing"<<endl<<"Number of packings are "<<d<<" and number of egss  left are "<<D<<endl<<endl;
    
	e=a/12;
    E=a%12;
    cout<<"For 12 Packing"<<endl<<"Number of packings are "<<e<<" and number of egss  left are "<<E<<endl<<endl;
    
	f=a/6;
    F=a%6;
    cout<<"For 6 Packing"<<endl<<"Number of packings are "<<f<<" and number of egss  left are "<<F<<endl<<endl;
    
    return 0;
}

