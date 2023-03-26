#include <iostream>
using namespace std;

void midline(int l,int m)
{
    if (l > m)
    {
        cout << '*';
        midline(l, m + 1);
    }
}

void pattern(int n, int k,int* l) {
    if (n < 1) return;
    if (k <= n)
    {
        cout << '*';
        pattern(n, k + 1,l);
        cout << '*';
    }
    else
    {
        cout << endl;
        pattern(n - 1, 1,l);
        if (n == 1)
        {
            midline(*l, 1);
        }
        else
        cout << endl;
    }
}

int main() {
    int rows;
    cout << "Enter the number of rows: ";
    cin >> rows;
    pattern(rows, 1,&rows);
    return 0;
}