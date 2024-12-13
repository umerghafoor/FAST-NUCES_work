// Task 1: Redirecting stderr to a File
// In this task, you will redirect the standard error (stderr)
// to a file:
// Open a
// file for writing.
// Use dup2() to duplicate the file descriptor of
// the opened file and replace stderr's
// file descriptor.
// Write
// an error message to stderr.
// Close
// the file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int file = open("error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file < 0) {
        perror("open");
        exit(1);
    }

    if (dup2(file, 2) < 0) {
        perror("dup2");
        exit(1);
    }

    fprintf(stderr, "This is an error message printed to the file\n");

    close(file);

    return 0;
}