#include<iostream>
using namespace std;
int main(){
    int dd,mm;
    cout<<"Enter day :";
    cin>>dd;
    cout<<"Enter month :";
    cin>>mm;
     //clean months
    if(mm>3)
     {cout<<"winter";}
    else if(mm>3 && mm<6)
     {cout<<"Spring";}
    else if(mm>6 && mm<9)
     {cout<<"Summer";}
    else if(mm>9 && mm<12)
     {cout<<"fall";}
     //complex months
     else if(mm==3)
      {if(dd>15){cout<<"spring";}
       else {cout<<"winter";}
      }
     else if(mm==6)
      {if(dd>15){cout<<"spring";}
       else {cout<<"summer";}
      }
     else if(mm==9)
      {if(dd>15){cout<<"summer";}
       else {cout<<"fall";}
      }
      if(mm==12)
      {if(dd>15){cout<<"fall";}
       else {cout<<"winter";}
      }

}
