#include <iostream>
using namespace std;
int main(){
   int mm, dd, yyyy;
   char a;
   cout<<"Enter month: ";
   cin>>mm;
switch(mm)
   {
    case 1:
	 cout<<"Janvary has 31 days";
	 break ;
    case 2:
	 cout<<"Febrary has 28 days";
    break ;
    case 3:
	 cout<<"March has 31 days";
	 break ;
    case 4:
	 cout<<"April has 30 days";
	 break ;
    case 5:
	 cout<<"May has 31 days";
	 break ;
    case 6:
	 cout<<"june has 30 days";
	 break ;
    case 7:
	 cout<<"july has 31 days";
	 break ;
    case 8:
	 cout<<"August has 31 days";
	 break ;
    case 9:
	 cout<<"September has 30 days";
	 break ;
    case 10:
	 cout<<"october has 31 days";
	 break ;
    case 11:
	 cout<<"November has 30 days";
	 break ;
    case 12:
	 cout<<"December has 31 days";
	 break ;
    default:
        cout<<"Invalid month";}
}
