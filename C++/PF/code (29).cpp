#include<iostream>
using namespace std;
int main()
{
    char x;
    cout<<"Enter any character: ";
    cin>>x;
    if(x!=0)
    {
        if((x>='a')&&(x<='z'))
        cout<<"The entered character is a lower case alphabet";
        else if((x>='A')&&(x<='Z'))
        cout<<"The entered character is an upper case alphabet";
        else if((x>='0')&&(x<='9'))
        cout<<"The entered character is a number";
        else
            cout<<"special character";
    }
    return 0;
}
