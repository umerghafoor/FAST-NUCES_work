#include <iostream>

using namespace std;
int main()
{
    int mm, dd, yyyy;
   char a;
   cout<<"Enter date 1 : ";
   cin>>dd>>a>>mm>>a>>yyyy;
      int mm2, dd2, yyyy2;
   char a2;
   cout<<"Enter date 2 : ";
   cin>>dd2>>a2>>mm2>>a2>>yyyy2;
      cout<<endl;
      cout<<dd<<'/'<<mm<<'/'<<yyyy<<endl;
      cout<<dd2<<'/'<<mm2<<'/'<<yyyy2<<endl;

    if (yyyy>yyyy2)
    {
        if(mm>mm2)
        {
            if(dd>dd2)
            {cout<<dd<<'/'<<mm<<'/'<<yyyy<<" is greater"<<endl;}
            else
             cout<<dd2<<'/'<<mm2<<'/'<<yyyy2<<" is greater"<<endl;
        }
        else
             cout<<dd2<<'/'<<mm2<<'/'<<yyyy2<<" is greater"<<endl;
    }
    else
             cout<<dd2<<'/'<<mm2<<'/'<<yyyy2<<" is greater"<<endl;
}
