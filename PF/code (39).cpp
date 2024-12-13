#include<iostream>
using namespace std;
int main()
{
    for(int i=1; i<=10; i++)
    {
        for(int j=10; j>i; j--)
        {
            cout<<"  ";
        }
        for(int j=1; j<i; j++)
        {
            cout<<" "<<j;
        }
        int a=i-2;
        for(int j=1; j<i; j++)
        {
            if(a!=0)
            {cout<<" "<<a;}
            a--;
        }
        cout<<endl;
    }
   for(int i=1; i<=10; i++)
   {
       for(int j=1; j<i; j++)
        {
            cout<<"  ";
        }
        cout<<"  ";
        for(int j=9,k=1; j>i; j--)
        {
            cout<<" "<<k;
            k++;
        }
        cout<<endl;
   }
}
