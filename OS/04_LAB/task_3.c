// ## Task 3: Passing Arguments with `execve()`

// Write a C
// program that uses `fork()` to create a child process. In the child process, use
// `execve()` to replace the current process with the `/bin/echo` program, passing
// a custom message as an argument (e.g., `echo "Hello, from execve!"`).
// The parent process should wait for the child to complete before exiting.

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int status;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        printf("Task  is running `ls`\n");

        char *args[] = {"/bin/echo", "Hello, from execve!", NULL};
        execve(args[0], args, NULL);

        exit(0);
    }
    else{
        printf("Parent is waiting for the child to complete\n");
        wait(&status);
    }
    printf("Task is completed\n");
    return 0;
}