#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PIPE_PATH "/home/umerghafoor/myfiles/OSLAB/serverFIFO"

int main() {
    int pipe_fd;
    char message[BUFSIZ];

    // Open the named pipe for writing
    if ((pipe_fd = open(PIPE_PATH, O_WRONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Send messages to the server
    while (1) {
        printf("Enter message to send (type 'quit' to exit): ");
        fgets(message, BUFSIZ, stdin);
        message[strcspn(message, "\n")] = 0; // Remove trailing newline

        // Write the message to the named pipe
        if (write(pipe_fd, message, strlen(message)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        if (strcmp(message, "quit") == 0)
            break;
    }

    // Close the named pipe
    close(pipe_fd);

    return EXIT_SUCCESS;
}
