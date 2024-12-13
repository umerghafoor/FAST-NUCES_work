#include<iostream>
using namespace std;
int main()
{
    int arr[9]={22,58,19,87,15,72,9,1,37},arr1[5],arr2[5];
    for(int i=0;i<5;i++)
    {
        arr1[i]=arr[i];
        arr2[i]=arr[i+5];
    }
    cout<<"Array 1 {";
    for(int i=0;i<5;i++)
    {
        cout<<arr1[i];
        if(i!=4)
            cout<<',';
    }
    cout<<'}'<<endl<<"Array 2 {";
    for(int i=0;i<5;i++)
    {
        cout<<arr2[i];
        if(i!=4)
            cout<<',';
    }
    cout<<'}';
}

