// Task 1: Using dup() with Pipes
// Objective:
// In this task, you will create a program where two processes communicate via a pipe. You will
// use dup() to redirect the standard input (stdin) and standard output (stdout) to achieve inter-
// process communication.
// Task Steps:
// 1. Create a pipe: Use the pipe() system call to create a unidirectional communication
// channel.
// 2. Fork a child process: The parent process will send data to the child process using the
// pipe.
// 3. Redirect stdout in the parent process: The parent process will write data to the pipe
// using dup() to duplicate the write end of the pipe as stdout.
// 4. Redirect stdin in the child process: The child process will read data from the pipe by
// duplicating the read end of the pipe as stdin.
// 5. Write and read data: The parent process will write data to stdout, which is
// redirected to the pipe, and the child process will read that data from stdin.
// Expected Output:
//  The parent process writes a message (e.g., &quot;Hello from parent&quot;) to the pipe.
//  The child process reads the message from the pipe and prints it on the terminal.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[128];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -2;
    }

    if (pid > 0) 
    { 
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        printf("Hello from parent\n");

        fflush(NULL);

        wait(NULL);
    } 
    else 
    {
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        fgets(buffer, sizeof(buffer), stdin);
        printf("Child received: %s ", buffer);
    }
    return 0;
}
