#include <iostream>

using namespace std;
int main()
{int a, b, c, d, B, C, D;
	cout<<"Enter number of seconds : ";
	cin>>a;
	cout<<endl;
	B=a/86400;
	b=a%86400;
	C=b/3600;
	c=b%3600;
	D=c/60;
	d=c%60;
	if (a>=60)
	{if (a>=3600)
	{if (a>=86400)
	{cout<<B<<" Days";
	}
	else
	{cout<<C<<" Hours ";
	}
	}
	else
	{cout<<D<<" Minutes ";
	}
	}
	else
	{cout<<d<<" Seconds ";
	}
	cout<<endl;
	cout<<endl;
	cout<<B<<" Days "<<C<<" Hours "<<D<<" Minutes "<<d<<"Seconds";
}
