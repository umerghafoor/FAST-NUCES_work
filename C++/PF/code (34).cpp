///////////////////////////////////////////Date validator////////////////////////////////////////////

#include <iostream>
using namespace std;
int main(){
   int mm, dd, yyyy;
   char a;
   cout<<"Enter date : ";
   cin>>dd>>a>>mm>>a>>yyyy;
      cout<<dd<<'/'<<mm<<'/'<<yyyy<<endl;
      if(mm<=12){
    switch(mm){
     case 1:  if (dd>31) 
	 {cout<<"   ! Date is not valid !, because janvary has 31 days";} 
	 else cout<<"date is valid";
	 break;
     case 2:  if (dd>28) 
	 {cout<<"   ! Date is not valid !, because febrary has 28 days";} 
	 else cout<<"date is valid";
	 break;
     case 3:  if (dd>31) 
	 {cout<<"   ! Date is not valid !, because march has 31 days";} 
	 else cout<<"date is valid";
	 break;
     case 4:  if (dd>30) 
	 {cout<<"   ! Date is not valid !, because april has 30 days";} 
	 else cout<<"date is valid";
	 break;
     case 5:  if (dd>31) 
	 {cout<<"   ! Date is not valid !, because may has 31 days";} 
	 else cout<<"date is valid";
	 break;
     case 6:  if (dd>30) 
	 {cout<<"   ! Date is not valid !, because june has 30 days";} 
	 else cout<<"date is valid";
	 break;
     case 7:  if (dd>31) 
	 {cout<<"   ! Date is not valid !, because july has 31 days";} 
	 else cout<<"date is valid";
	 break;
     case 8:  if (dd>31) 
	 {cout<<"   ! Date is not valid !, because august has 31 days";} 
	 else cout<<"date is valid";
	 break;
     case 9:  if (dd>30) 
	 {cout<<"   ! Date is not valid !, because september has 30 days";} 
	 else cout<<"date is valid";
	 break;
     case 10: if (dd>31) 
	 {cout<<"   ! Date is not valid !, because october has 31 days";} 
	 else cout<<"date is valid";
	 break;
     case 11: if (dd>30) 
	 {cout<<"   ! Date is not valid !, because november has 30 days";} 
	 else cout<<"date is valid";
	 break;
     case 12: if (dd>31) 
	 {cout<<"   ! Date is not valid !, because december has 31 days";} 
	 else cout<<"date is valid";
	 break;}}
    else 
    cout<<"Months can't exceed 12";
}
