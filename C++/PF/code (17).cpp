#include<iostream>
using namespace std;
int main()
{
    float salary, bonus, total, years;
    cout<<"Enter your salary amount : ";
    cin>>salary;
    cout<<"Years of service         : ";
    cin>>years;
    cout<<endl;

    if (years>=5)
    {
        bonus = 0.05*salary;
        total = bonus+salary;
        cout<<"The net bonus is : "<<bonus<<endl;
        cout<<"Total salary is  : "<<total<<endl;
    }
else
    {
        bonus=0;
        total=salary;
        cout<<"The net bonus is : "<<bonus<<endl;
        cout<<"Total salary is  : "<<total<<endl;
    }
}
