
#include <iostream>
using namespace std;
int main(){
   int b,fact=1;
   char a;
while(1){
  cout<<"Enter the number : ";
  cin>>b;
     while (b!=0)
   {
    cout<<b;

    fact=fact*b;
   	b--;
   	if(b!=0)
        cout<<"*";
   }
   cout<<"="<<fact<<endl;
   cout<<"Continue(y/n)? ";
   cin>>a;
   if(a=='n')
    break;
  }
}

