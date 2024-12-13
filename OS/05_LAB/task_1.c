// Task 1:
// The parent process is a task manager requesting the child to check whether the string sent is
// a palindrome or not. The parent sends a task request (e.g., &quot;Rotator&quot;) to the child through
// one pipe. Once the task is completed, the child responds with a status update (e.g., &quot;Yes
// Palindrome&quot;) through another pipe, acknowledging the completion of the task. Then the
// parent will then read that message and print that “ Task Manager is exiting now”.
// Example:
// Parent sends: &quot;Rotator&quot;
// Child replies: &quot;Yes Palindrome&quot;
// Parent :” Task Manager exiting now.”

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int isPlindrome(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] != str[len - i - 1])
        {
            return 0;
        }
    }
    return 1;
}

int main() {
    int pipe1[2], pipe2[2];
    char str[100], str1[100];
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
        printf("Enter the string : ");
        scanf("%s", str);
        write(pipe1[1], str, strlen(str) + 1);
        close(pipe1[1]);

        wait(NULL);
        
        close(pipe2[1]);
        read(pipe2[0], str1, 100);
        printf("%s\n", str1);
        close(pipe2[0]);
        
        printf("Task Manager is exiting now\n");
    }
    else
    {
        close(pipe1[1]);
        char str[100];
        // printf("waiting for read\n");
        read(pipe1[0], str, 100);
        close(pipe1[0]);

        close(pipe2[0]);
        if (isPlindrome(str))
        {
            write(pipe2[1], "Yes Palindrome", 14);
        }
        else
        {
            write(pipe2[1], "Not Palindrome", 14);
        }
        close(pipe2[1]);
        exit(0);
    }
    return 0;
}