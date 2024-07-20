#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define PIPE_PATH "/home/umerghafoor/myfiles/OSLAB/serverFIFO"

int main() {
    int pipe_fd;
    char buffer[BUFSIZ];

    // Create the named pipe
    if (mkfifo(PIPE_PATH, 0666) == -1) {
        perror("mkfifo");
        //exit(EXIT_FAILURE);
    }

    // Open the named pipe for reading
    if ((pipe_fd = open(PIPE_PATH, O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Server is running. Waiting for messages...\n");

    // Read messages from the named pipe
    while (1) {
        ssize_t bytes_read = read(pipe_fd, buffer, BUFSIZ);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Received message from client: %s\n", buffer);
            if (strcmp(buffer, "quit") == 0)
                break;
        }
    }

    // Close and remove the named pipe
    close(pipe_fd);
    unlink(PIPE_PATH);

    return EXIT_SUCCESS;
}
