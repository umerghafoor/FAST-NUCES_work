#include<iostream>
using namespace std;
int main()
{
    for(int i=1; i<=3; i++)
    {
        if(i==1)
        {cout<<" *           *"<<endl;}
        for(int j=0; j<i; j++)
        {
            cout<<"  ";
        }
        if(i!=4)
        {cout<<" *";}
        for(int j=3; j>i; j--)
        {
            cout<<"  ";
        }
        if(i==1)
            {cout<<"  ";}
        if(i<3)
        {cout<<" *";}
        cout<<endl;
    }
    for(int i=2; i<=4; i++)
    {
        for(int j=4; j>i; j--)
        {
            cout<<"  ";
        }
        cout<<" *";
        for(int j=1; j<i; j++)
        {
            cout<<"  ";
            if(j==2 || j==3)
                cout<<"  ";
        }
        if(i!=1)
        {cout<<" *";}
        cout<<endl;
    }
    for(int i=1; i<=3; i++)
    {
        for(int j=0; j<i; j++)
        {
            cout<<"  ";
        }
        if(i!=4)
        {cout<<" *";}
        for(int j=3; j>i; j--)
        {
            cout<<"  ";
        }
        if(i==1)
            {cout<<"  ";}
        if(i<3)
        {cout<<" *";}
        cout<<endl;
    }
    for(int i=2; i<=4; i++)
    {
        for(int j=4; j>i; j--)
        {
            cout<<"  ";
        }
        cout<<" *";
        for(int j=1; j<i; j++)
        {
            cout<<"  ";
            if(j==2 || j==3)
                cout<<"  ";
        }
        if(i!=1)
        {cout<<" *";}
        cout<<endl;
    }
    for(int i=1; i<=3; i++)
    {
        for(int j=0; j<i; j++)
        {
            cout<<"  ";
        }
        if(i!=4)
        {cout<<" *";}
        for(int j=3; j>i; j--)
        {
            cout<<"  ";
        }
        if(i==1)
            {cout<<"  ";}
        if(i<3)
        {cout<<" *";}
        cout<<endl;
    }
    for(int i=2; i<=4; i++)
    {
        for(int j=4; j>i; j--)
        {
            cout<<"  ";
        }
        cout<<" *";
        for(int j=1; j<i; j++)
        {
            cout<<"  ";
            if(j==2 || j==3)
                cout<<"  ";
        }
        if(i!=1)
        {cout<<" *";}
        cout<<endl;
    }
}
