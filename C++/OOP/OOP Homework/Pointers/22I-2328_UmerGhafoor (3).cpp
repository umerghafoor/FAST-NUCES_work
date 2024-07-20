#include <iostream>
using namespace std;

void pattern(int n, int k){
    if (n < 1) return;
    if (k <= n)
    {
        pattern(n, k+1);
        cout << "*";
    }
    else 
    {
        pattern(n-1, 1);
        cout << endl;
    }
}

int main(){
    int rows;
    cout << "Enter the number of rows: ";
    cin >> rows;
    pattern(rows, 1);
    return 0;
}