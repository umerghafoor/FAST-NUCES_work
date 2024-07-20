#include<iostream>
using namespace std;
int main()
{
    int a,rem,hh,mm;
    cout<<"Enter the number of seconds: ";
    cin>>a;
    if(a>=3600)
    {
        hh=a/3600;
        rem=a%3600;
        mm=rem/60;
        rem=rem%60;
        cout<<hh<<"hours "<<mm<<"minutes "<<rem<<"seconds "<<endl;

    }
    else if(a>=60)
    {
        mm=a/60;
        rem=a%60;
        cout<<mm<<"minutes "<<rem<<"seconds "<<endl;

    }
    else
        cout<<a<<"seconds ";
}
