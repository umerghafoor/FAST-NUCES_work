#include <iostream>
using namespace std;
int main()
{
    int i=2;

    for(int k=0; k<1;k++)
    {
        cout<<"+------+"<<endl;
        for(int q=0;q<2;q++)
{
        for(int i=2; i<=4; i++)
    {
         cout<<"|";
         for(int j=4; j>i; j--)
         {
             cout<<" ";
         }
         cout<<"^";
         for(int j=1; j<i; j++)
         {
             if(j!=1)
             cout<<" ";
             if(j==2 || j==3)
                 cout<<" ";
         }
         if(i!=1)
         {cout<<"^";}
         for(int j=4; j>i; j--)
         {
             cout<<" ";
         }
         cout<<"|"<<endl;
    }}
    cout<<"+------+"<<endl;
    for(int q=0;q<2;q++)
{
        for(int i=1; i<=3; i++)
    {
        cout<<"|";
        for(int j=1; j<i; j++)
        {
            cout<<" ";
        }
        if(i!=4)
        {cout<<"v";}
        for(int j=3; j>i; j--)
        {
            cout<<"  ";
        }
        if(i<=3)
        {cout<<"v";}
        for(int j=1; j<i; j++)
        {
            cout<<" ";
        }
        cout<<"|"<<endl;
    }
    }
    cout<<"+------+"<<endl;}
}
