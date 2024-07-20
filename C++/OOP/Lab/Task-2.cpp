#include <iostream>

using namespace std;

int main()
{
	float arr[5], pro = 1;
	float* pArr = arr, * pPro = &pro;
	cout << "Enter the Array" << endl;
	for (int i = 0;i < 5;i++)
	{
		cin >> *(pArr + i);
		*(pArr + i) = *(pArr + i) / 2;
	}
	cout << "\nArray is : ";
	for (int i = 0;i < 5;i++)
	{
		cout << *(pArr + i) << ",";
		*pPro = *pPro * *(pArr + i);
	}
	cout << endl << "Product is : " << *pPro << endl;

}