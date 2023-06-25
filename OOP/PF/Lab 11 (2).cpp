#include<iostream>
using namespace std;
int main()
{
    int arr[10]={1,5,4,1,1,3,2,5,1,5},a,f;
    cout<<"Enter a number in an array = ";cin>>a;
    for(int i=0;i<10;i++)
    {
        if(arr[i]==a)
        {
            f++;
        }
    }
    cout<<"occurance "<<a<<":"<<f;
}
