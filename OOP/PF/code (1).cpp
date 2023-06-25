#include <iostream>
#include <string>
using namespace std;
int main()
{int age;
cout<<"Enter your age : ";
cin>>age;

string a = (age<18)? "You cannot vote" : "You can vote"
cout<<a;
return 0;
}
