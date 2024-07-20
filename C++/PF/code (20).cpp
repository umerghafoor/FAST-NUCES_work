#include<iostream>
using namespace std;
int main()
{
   int x;
   cout<<"Enter a year:  ";
   cin>>x;
 if(x%100!=0)
 {
     if(x%4==0)
     cout<<"The year is a leap year.";
 }
else if((x%400)==0)
 {
      cout<<"The year is a leap year";
}

else
{cout<<"The year is not a leap year.";

}
return 0;
}
