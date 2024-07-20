#include <iostream>
using namespace std;
int main(){
   int a, n1,n2;
   cout<<"Enter any positive number : ";
   cin>>a;
  int n, reverse=0, rem;
   n=a;
  while(n!=0)
  {
     rem=n%10;
     reverse=reverse*10+rem;
     n/=10;
  }
 a=reverse;
while (a!=0){
   n1=a%10;
   a=a/10;
   n2=n2+n1;
   cout<<n1;
   if(a!=0){cout<<"+";}
}
cout<<"="<<n2;
}

