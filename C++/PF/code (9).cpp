#include <iostream>
using namespace std;
int main(){
   int num1, num2;
   char op;
   cout<<"Enter first number : ";
   cin>>num1;
   cout<<"Enter operator : ";
   cin>>op;
   cout<<"Enter Second  number : ";
   cin>>num2;
   cout<<endl;
   cout<<num1<<op<<num2
   <<endl;

   switch (num2==0)
   {
       case 1: cout <<"num2 cannot be zero";
       case 0:
        switch(op){
   	    case '+':
   	cout<<"Answer is : "<<num1+num2;
   	break;
   	    case '-':
   	cout<<"Answer is : "<<num1-num2;
   	break;
	    case '*':
   	cout<<"Answer is : "<<num1*num2;
   	break;
	    case '/':
   	cout<<"Answer is : "<<num1/num2;
   	break;
   	    case '%':
   	cout<<"Answer is : "<<num1%num2;
   	break;
	default:
		cout<<" INVALID INPUT";
   }
   }
   return 0;
}
