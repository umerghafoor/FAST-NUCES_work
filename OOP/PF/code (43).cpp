#include <iostream>
using namespace std;
int main(){
 int a, b, sum;
 	cout<<"Enter the number : ";cin>>a;
 while (a!=0){
 	b=a%10;
 	sum=sum+b;
 	a=a/10;
 	cout<<b;
 	if(a!=0){
 		cout<<"+";
	 }
 }
 cout<<"="<<sum;
}
