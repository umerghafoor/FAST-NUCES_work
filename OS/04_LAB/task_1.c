#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);
    int status;
    pid_t pid;
    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid == 0) {
            printf("Task %d is running\n", i);
            exit(i);
        }
    }
    for (int i = 0; i < n; i++) {
        pid = wait(&status);
        // printf("PID of completed task: %d\n", pid);
        // printf("Status of completed task: %d\n", status);
        printf("Task %d is completed\n", WEXITSTATUS(status));
    }
    printf("All tasks are completed\n");
    return 0;
}