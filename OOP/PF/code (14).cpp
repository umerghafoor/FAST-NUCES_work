#include<iostream>
using namespace std;
int main()
{
    int a,b;
    int sub;
    cout<<"Enter two numbers/integers:"<<endl;
    cin>>a,b;
    // using if statement

      if(a>b)

          sub=a-b;
          cout<<"Sum="<<sub<<endl;

      else if(b>a)

          sub=b-a;
          cout<<"Sum="<<sub<<endl;

      else
        cout<<"Invalid "<<endl;
      return 0;

}
