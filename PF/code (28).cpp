#include <iostream>
using namespace std;
int main(){
    int dd, dd1,dd2,mm1,mm2, mm, yyyy1, yyyy2, yyyy;
    char a;

    cout<<"Enter date of birth : ";
    cin>>dd>>a>>mm>>a>>yyyy;
    cout<<"Enter current       : ";
    cin>>dd1>>a>>mm1>>a>>yyyy1;

    yyyy2=yyyy1-yyyy;
    mm2=mm1-mm;
    dd2=dd1-dd;

    if (mm2<0)
    {yyyy2=yyyy2-1;
     mm2=12+mm2;}
    if (dd2<0)
    {mm2=mm2-1;
    dd2=30+dd2;}
     if (dd2<0 || mm2<0 || yyyy2<0)
     {
         cout<<"invalid"<<endl;
         return 0;
     }
     else
        cout<<dd2<<" days "<<mm2<<" month "<<yyyy2<<" years"<<endl;

}
