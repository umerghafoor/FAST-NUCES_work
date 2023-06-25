#include <iostream>
using namespace std;

long Combination(int n, int r) {
    if (r == 0 || r == n)
        return 1;
    return Combination(n - 1, r - 1) + Combination(n - 1, r);
}
int main()
{
	int n, r;
    cout << "Enter n : ";cin >> n;
    cout << "Enter r : ";cin >> r;
    if (r > n) { cout << "INVALID INPUT !"; return 0; }
    else
        cout<<"C(n,r) = " << Combination(n, r);
}