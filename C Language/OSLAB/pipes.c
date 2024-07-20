#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{

    int pid;
    int pipefd[2];


    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe not created");
        exit(EXIT_FAILURE);
    }

    // Fork process
    pid = fork();

    if (pid == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }

    if(pid==0)
    {
        printf("I am Child\n");
        close(pipefd[0]);

        const char msg[20] = "Hello from Child\n";
        printf("%s\n",msg);
        
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("I am parent\n");
        close(pipefd[1]);
        
        char msg[20];
        //read(pipefd[0], msg, sizeof(msg) - 1);
        int bytes_read = read(pipefd[0], msg, sizeof(msg) - 1); // Read with buffer size - 1
        if (bytes_read == -1)
        {
            perror("Error reading from pipe");
            exit(EXIT_FAILURE);
        }
        msg[bytes_read] = '\0';
        //end
        close(pipefd[0]);


        printf("%s\n",msg);
        wait(NULL);
        exit(EXIT_SUCCESS);

    }
}