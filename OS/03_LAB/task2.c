#include "stdio.h"
#include "unistd.h"

// Q2. Write
// a program to find sum of even numbers in parent process and sum of odd numbers in child process.
// Examples: 
// Input : 1, 2, 3, 4, 5
// Output :
// Parent process
// Sum of even no. is 6
// Child process
// Sum of odd no. is 9

int sumofEven(int *arr, int size)
{
    if (arr == NULL || size <= 0)
    {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            sum += arr[i];
        }
    }
    return sum;
}

int sumofOdd(int *arr, int size)
{
    if (arr == NULL || size <= 0)
    {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 != 0)
        {
            sum += arr[i];
        }
    }
    return sum;
}

int main()
{

    int size;
    printf("Enter the number of terms: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        printf("Enter number %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    
    pid_t pid =  fork();

    if (pid<0)
    {
        printf(" Error");
        return -1;
    }

    if (pid)
    {
        int sume = sumofEven(arr,size);
        wait(pid);
        printf("Sum of Even : %d\n",sume);
    }
    else
    {
         int sumo = sumofOdd(arr,size);
        printf("Sum of Even : %d\n",sumo);

    }
}