#include<iostream>
using namespace std;
int main()
{
    float a, t, per;
    char med;
    cout<<"Enter number of classes taken : ";
    cin>>a;
    cout<<"Enter total number of classes : ";
    cin>>t;
    per=(a/t)*100;
if (per<75)
{
    cout<<"Do you have a medical cause(y/n) : ";
    cin>>med;
    if(med=='y')
    {
        cout<<"You can sit in exam";
    }
    else
    {cout<<"You cannot sit in exam"<<endl;
}}
else
{
    cout<<"You can sit in exam";
}
}
