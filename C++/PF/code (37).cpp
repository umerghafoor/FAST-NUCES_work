#include <iostream>
using namespace std;
int main(){
int N,num=1, num2=2,k=1;
cout<<"Enter the number of terms"<<endl;
cin>>N;
cout<<endl;
for (int i=0;i<N;i++)
{
    cout<<num<<"  ";
    num=num+num+1;
}
cout<<endl;
for (int i=0;i<N;i++)
{
    for(int j=0;j<k;j++)
    {cout<<"-";}
    cout<<", ";
    if(i%2==0 && i!=0)
        k++;
}
cout<<endl;
for(int i=0;i<N;i++)
{
    cout<<num2<<"  ";
    num2*=2;
}
return 0;
}
