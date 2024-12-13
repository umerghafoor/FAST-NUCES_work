#include<iostream>
using namespace std;
int main()
{
    int arr[10],a,i;
    for(int i;i<10;i++)
    {
        cout<<"Enter the number "<<i<<" =";
        cin>>arr[i];
    }
    while (1)
    {
        cout<<"Enter the Array number : ";cin>>a;
        if(a<10 && a>=0)
        {
            cout<<endl<<"Number is : "<<arr[a];
            break;
        }
    }
}
