#include<iostream>
using namespace std;
int main()
{
   int x;
   cout<<"Enter a year:  ";
   cin>>x;
   switch ((x%4==0 && x%100!=0)|| x%400==0)
    {
        case 1 : cout<<"The year is a leap year.";
    break ;
      case 0 : cout<<"The year is not leap year";}
return 0;
}
