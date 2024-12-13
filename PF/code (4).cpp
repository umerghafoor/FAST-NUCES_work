#include <iostream>
using namespace std;
int main(){
    int x,i=0,j;
 for(x=1; x!=6; )
 {
     cin>>x;
     switch(x)
     {
         case 1:
            for(i=0 ; i<=10; i++)
	             { for(int j=0 ; j<i; j++)
		           {cout<<"*";}
		           cout<<endl;}
		    break;
	     case 2:
	         for(i=0 ; i<=10; i++)
	             { for(int j=0 ; j<10-i; j++)
		           {cout<<"*";}
                    cout<<endl;}
		    break;
		    case 3:
	         for(i=0 ; i<=10; i++)
	             {  for(int j=0; j<i; j++)
                   {cout<<" ";}
                    for(int j=0 ; j<10-i; j++)
		           {cout<<"*";}
                    cout<<endl;}
		    break;
		    case 4:
	         { for(i=0 ; i<=10; i++)
                {for(int j=0 ; j<10-i; j++)
                {cout<<" ";}
                for(int j=0 ; j<i; j++)
                {cout<<"*";}
		        cout<<endl;}}
		    break;
		    case 5:
	         for(i=0 ; i<=20; i+=2)
	             {  if(i<=9)
	                 {for(int j=0 ; j<9-i; j+=2)
		           {cout<<" ";}
	                 for(int j=0 ; j<=i; j++)
		           {cout<<"*";}}
		           else
                   {
                       for(j=i; j>20; j--)
                        cout<<"v";
                   }
                    cout<<endl;}
		    break;
}}}


