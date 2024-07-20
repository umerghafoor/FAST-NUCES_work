#include<iostream>
using namespace std;
int main()
{
    int arr[10]={1,2,3,4,5,6,7,8,9,10},b;
    bool a;
    for(int i; i<10;i++)
    {
        if(arr[i+1]<arr[i])
            {
                if(!a)
                {b=1;}
                a++;
            }
        }
        cout<<"Array {";
    for(int i=0;i<10;i++)
    {
        cout<<arr[i];
        if(i!=9)
            cout<<',';
    }
    cout<<'}'<<endl;
    if(b){cout<<"Array is not in ascending order";}
    else {cout<<"Array is in ascending order";}
}


