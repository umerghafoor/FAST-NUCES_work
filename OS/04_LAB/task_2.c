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
        char *args[] = {"ls", NULL};

        // -la is and argument to ls command
        // char *args[] = {"ls", "-la", NULL};

        // Ececuting the task_1.c.o file
        // char *args[] = {"./task_1.c.o", NULL};

        execvp(args[0], args);
        for (int i = 0; i < 500; i++) {
            
        }
        exit(0);
    }
    else{
        printf("Parent is waiting for the child to complete\n");
        wait(&status);
    }
    printf("Task is completed\n");
    return 0;
}