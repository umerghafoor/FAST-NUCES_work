#include<iostream>
using namespace std;
int main()
{
   int x;
   cout<<"Enter a number:  ";
   cin>>x;
   if ((x%3==0)&&(x%5==0))
  {
     cout<<"The number is divisible by 3 and 5.";
}
else
cout<<"The number is not divisble by 3 and 5.";


return 0;
}
