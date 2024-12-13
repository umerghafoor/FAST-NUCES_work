// ## Task2:
// The parent process is a client requesting a mathematical operation (e.g., &quot;Multiply 3 by 4&quot;)
// to the child process, which acts as a calculator. The child receives the operation, performs
// the calculation, and sends the result back to the parent. Parent will check whether the
// answer is correct or not. If the answer is correct Parent will print “Correct Answer” else it
// will print “Incorrect Answer”.
// ### Example:
// Parent sends: &quot;Multiply 3 by 4&quot;
// Child calculates 3 * 4 and replies: &quot;Result: 12&quot;
// Parent: “Correct Answer”

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int doOperation(int a,int b,char *op)
{
    if (strcmp(op, "+") == 0)
    {
        return a + b;
    }
    else if (strcmp(op, "-") == 0)
    {
        return a - b;
    }
    else if (strcmp(op, "*") == 0)
    {
        return a * b;
    }
    else if (strcmp(op, "/") == 0)
    {
        if (b == 0)
        {
            printf("Division by zero is not possible\n");
            return -1;
        }
        return a / b;
    }
    else
    {
        printf("Invalid operation\n");
        return -1;
    }
}

int main()
{
    int pipe1[2], pipe2[2];
    char str[100], str1[100];
    int a, b;
    char op[100];
    pid_t pid;

    if (pipe(pipe1) == -1)
    {
        printf("Pipe 1 Failed to create");
        return -1;
    }
    if (pipe(pipe2) == -1)
    {
        printf("Pipe 2 Failed to create");
        return 1;
    }
    pid = fork();
    if (pid < 0)
    {
        printf("Fork Failed");
        return 1;
    }
    
    if (pid > 0)
    {
        close(pipe1[0]);
        printf("Enter the first number : ");
        scanf("%d", &a);
        printf("Enter the second number : ");
        scanf("%d", &b);
        printf("Enter the operation : ");
        scanf("%s", op);

        write(pipe1[1], &a, sizeof(a));
        write(pipe1[1], &b, sizeof(b));
        write(pipe1[1], op, strlen(op) + 1);
        close(pipe1[1]);

        wait(NULL);

        close(pipe2[1]);
        int result;
        read(pipe2[0], &result, sizeof(result));
        printf("Result: %d\n", result);
        if (result == doOperation(a, b, op))
        {
            printf("Correct Answer\n");
        }
        else
        {
            printf("Incorrect Answer\n");
        }
        close(pipe2[0]);

    }
    else
    {
        close(pipe1[1]);
        char str[100];
        // printf("waiting for a\n");
        read(pipe1[0], &a, sizeof(a));
        // printf("waiting for b\n");
        read(pipe1[0], &b, sizeof(b));
        // printf("waiting for op\n");
        read(pipe1[0], op, 100);
        close(pipe1[0]);

        close(pipe2[0]);
        // printf("Debug %d %d %s\n", a, b, op);
        int result = doOperation(a, b, op);
        write(pipe2[1], &result, sizeof(result));
        close(pipe2[1]);
        exit(0);
    }
    return 0;
}