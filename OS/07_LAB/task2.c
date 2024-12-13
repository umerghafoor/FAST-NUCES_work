// Task 2: Redirection with fork()
// Write
// a program where a parent process creates a child process using fork().
// The child process will:
// Redirect
// its stdout to
// a file using dup2().
// Execute
// a command like ls or date using execlp() to demonstrate that the output is
// redirected to the file.
// The
// parent process should wait for the child to complete.
// Expected
// Output: The output of the ls or date command
// executed by the child should be written to the file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {

    int file = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file < 0) 
    {
        perror("open");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) 
    {
        perror("fork");
        exit(1);
    }

    // Child process
    if (pid == 0) 
    {
        if (dup2(file, 1) < 0) 
        {
            perror("dup2");
            exit(1);
        }

        execlp("date", "date", NULL);
        // execlp("ls", "ls", NULL);

        exit(1);
    }

    // Parent process
    int status;
    wait(&status);

    close(file);

    return 0;
}