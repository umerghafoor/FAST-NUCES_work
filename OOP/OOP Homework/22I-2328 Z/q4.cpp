#include <iostream>
using namespace std;
/*Q4: Write a program that takes a pointer to array of integers.
Create a dynamic array of integers through CreateArray() function
(without recursion). After that pass it to the sum function to
calculate sum of perfect numbers using recursion.(10)
NOTE: A perfect number is a number that is numerically equal to the sum of
its divisors. For example, 6 is a perfect number because the divisors of 6
are 1,2,3 and 1+2+3=6.
int sum (int *array, int size)*/
bool isPerfect(int n, int i, int sum)
{
    if (i >= n)
    {
        return sum == n;
    }
    if (n % i == 0)
    {
        sum += i;
    }
    return isPerfect(n, i + 1, sum);
}

int sum(int* array, int size)
{
    static int result = 0;
    if (size == 1)
    {
        return result;
    }
    else if (isPerfect(array[0], 1, 0))
    {
        result = result + array[0];
    }
    return sum(array + 1, size - 1);
}


int* CreateArray(int size)
{
    int* arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        cout << "Enter Array Element [" << i << "] : ";cin >> arr[i];
    }
    return arr;
}

int main()
{
    int size;
    cout << "Enter the Size of Arrray : ";cin >> size;
	cout<<sum(CreateArray(size), size);
}