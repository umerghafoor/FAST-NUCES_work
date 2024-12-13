#include "stdio.h"
#include "unistd.h"

void printFabonocci(int n)
{
    int t1 = 0, t2 = 1, nextTerm;
    printf("Fibonacci Sequence: %d, %d", t1, t2);

    for (int i = 1; i <= n - 2; ++i)
    {
        nextTerm = t1 + t2;
        printf(", %d", nextTerm);
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n");
}

int main()
{
    pid_t pid =  fork();

    
    if (pid<0)
    {
        printf(" Error");
        return -1;
    }

    if (pid)
    {
        wait(pid);
        printf("Done from Parent\n");
    }
    else
    {
        printf("Child Calculating Fabonacci\n");
        int input;
        scanf("%d",&input);
        printFabonocci(input);
    }
}