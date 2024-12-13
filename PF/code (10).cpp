#include <iostream>
using namespace std;
int main()
{
    float a, b, c;
    cout<<"Enter number of units : ";
    cin>>a;
if(1)
    {if(a<100)
    {
        b=a*9;
    }
    if(a<200 && a>=100)
    {
        b=a*11;
    }
    if(a>=200 && a<=300)
    {
        b=a*9;
    }}
    cout<<endl;
    cout<<"bill without tax : "<<b<<endl;

    if(b<750)
    {
        c=.05*b;
        c=c+b;
        cout<<"Total bill is : "<<c;
    }
    if(b>=750)
    {
        c=.07*b;
        c=c+b;
        cout<<"Total bill is : "<<c;
    }

    return 0;
}
