#include <iostream>
using namespace std;
int main()
{int arr[10] = {25, -10, 3, 4, 99, 100, 74, -890, 0, 1}, val,
sum,sum2=0,s2=0,sum3=0,s3=0,sml=0,lrg,a;
	for(int i = 0; i < 10; i++)
	{
		sum=arr[i]+sum;
		if(arr[i]%2==0){sum2=arr[i]+sum2;s2++;}
		if(arr[i]%2!=0){sum3=arr[i]+sum3;s3++;}
		if(arr[i]<=sml){sml=arr[i];}
		if(arr[i]>lrg){lrg=arr[i];}
	}

		cout << "Average of all     : "<<sum/10<<endl;
		cout << "Average of even    : "<<sum2/s2<<endl;
		cout << "Average of odd     : "<<sum3/s3<<endl;
		cout << "Average of average : "<<(sum2+sum3)/(s2+s3)<<endl;
		cout << "Smallest           : "<<sml<<endl;
		cout << "Largest            : "<<lrg<<endl;
		cout<<'{';
		for (int i=0;i<=8;i++){
        for (int j=i+1;j<=9;j++){
            if (arr[j]<arr[i]){
            a=arr[i];
            arr[i]=arr[j];
            arr[j]=a;
            }
            }
        }
        for (int l=0;l<=9;l++){
            cout<<arr[l];
            cout<<", ";
            }
            cout<<'}';

}
