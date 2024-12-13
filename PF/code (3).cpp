#include <iostream>
#include<math.h>
using namespace std;
int main(){
 float x, n, f=1,tmp=1,tmp2,fi=1,tmp3=1,ans,ans2;
 int a=1;
 cout<<"Enter the number of terms N : ";
 cin>>n;
 cout<<"Enter the Value of X        : ";
 cin>>x;
 while (tmp2<n)
 {
     for(tmp3=1;tmp3<=tmp;tmp3++)
     {
         f=f*fi;
         fi++;
     }
     ans=(a*pow(x,tmp))/f;
     ans2=ans2+ans;
     tmp2++;tmp+=2;
     f=1;fi=1;
     a=-a;
 }
 cout<<"Ans. from given series : "<<ans2<<endl;
 cout<<"Ans. from build-in function : "<<sin(x)<<endl;
 }
