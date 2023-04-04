#include <iostream>
using namespace std;

void PrintChar(int size,char ch)
{
    if (size < 1) return;
    else
    {
        PrintChar(size-1,ch);
        cout << ch;
    }
}
void PrintCharSpace(int size, char ch)
{
    if (size < 1) return;
    else
    {
        PrintCharSpace(size - 1, ch);
        cout <<' '<<ch;
    }
}

void ArrowShape(int n, int k) 
{
    if (n < 1) return;
    else
    {
        PrintChar(k-n, ' ');
        PrintChar(k-n, '*');
        cout << endl;
        ArrowShape(n - 1, k);
        PrintChar(k-n-1, ' ');
        PrintChar(k-n-1, '*');
        cout << endl;

    }
}
void RhombusStarPattern(int n,int k)
{
    if (n < 1) return;
    else
    {
        RhombusStarPattern(n - 1, k);
        PrintChar(k - n, ' ');
        PrintCharSpace(k, '*');
        cout << endl;

    }
}
void XStartPattern(int n,int k)
{
    if (n < 1) return;
    else
    {
        PrintChar(k - n, ' ');
        cout << '*';
        PrintCharSpace(n-1, ' ');
        cout << '*';
        cout << endl;
        XStartPattern(n - 1, k);
        PrintChar(k - n, ' ');
        cout << '*';
        PrintCharSpace(n - 1, ' ');
        cout << '*';
        cout << endl;
    }
}
int main()
{
    int size;
    cout << "Enter the Size : ";cin >> size;
    int choice = 1;
    while (choice != 0)
    {
        cout << "1. Print Arrow" << endl;
        cout << "2. Print Rhombus Star Pattern" << endl;
        cout << "3. Print X Start Pattern" << endl;
        cout << "4. Re Enter the Size " << endl;
        cout << "0. Exit" << endl;
        cout << "Enter the choice : ";cin >> choice;
        switch (choice)
        {
        case 1:ArrowShape(size, size);break;
        case 2:RhombusStarPattern(size, size);break;
        case 3:XStartPattern(size, size);break;
        case 4: cout << "Enter the Size : ";cin >> size;break;
        case 0:cout << "\n Thank You \n\n";break;
        default:cout << "Enter Valid Option! " << endl;
        }
        system("pause");
        system("cls");
    }
	
}