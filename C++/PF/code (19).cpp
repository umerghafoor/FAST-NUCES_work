#include<iostream>
using namespace std;
int main()
{
int age1,age2,age3;
cout<<"Enter age of first person: ";
cin>>age1;
cout<<"Enter age of second person: ";
cin>>age2;
cout<<"Enter age of third person: ";
cin>>age3;
cout<<endl;
if(1)
{if ((age1 > age2)&&(age1>age3))
{  cout<<"First person is the oldest";
}
else if ((age2 > age1)&&(age2>age3))
{  cout<<"Second person is the oldest";
}
else if ((age3 > age2)&&(age3>age1))
{  cout<<"Third person is the oldest";
}}
cout<<endl;
if(1)
{if ((age1 < age2)&&(age1<age3))
{  cout<<"First person is the youngest";
}
else if ((age2 < age1)&&(age2<age3))
{  cout<<"Second person is the youngest";
}
else if ((age3 < age2)&&(age3<age1))
{  cout<<"Third person is the youngest";
}}}
