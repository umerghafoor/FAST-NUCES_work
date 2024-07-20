#include<iostream>
using namespace std;

float celcis(float);

int main()
    {float a,c;
    cin>>a;
    c=celcis(a);
    cout<<c;
    }

float celcis(float n)
    {
        float tmp;
        tmp=(5.0/9.0)*(n-32);
        return tmp;
    }









/*int main()
{
   int marks[3][2],marksum;
   for (int i=0;i<2;i++)
   {
        for(int j=0;j<3;j++)
        {
            cout<<"Enter the array ("<<i<<" "<<j<<") :";
            cin>>marks[i][j];
            marksum=marksum+marks[i][j];
        }
        cout<<endl;
   }
   //cout<<marksum;
   for (int i=0;i<2;i++)
   {
        for(int j=0;j<3;j++)
        {
            cout<<setw(4)<<marks[j][i];
        }
        cout<<endl;
   }
}
/*int main()
{
   int marks[2][3]={{2,3,4},{5,6,7}};
   for (int i=0;i<2;i++)
   {
        for(int j=0;j<3;j++)
        {
            cout<<setw(4)<<marks[i][j];
        }
        cout<<endl;
   }
}*/
