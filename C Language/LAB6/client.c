#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define SERVER_FIFO "/home/umer/Desktop/LAB8/serverFIFO"
#define CLIENT_FIFO "/home/umer/Desktop/LAB8/clientFIFO"

int main() {
    int server_fd, client_fd;
    char buf[50];

    mkfifo(CLIENT_FIFO, 0666);
    server_fd = open(SERVER_FIFO, O_WRONLY);

    while (1) {
        printf("Enter your command ('hello' or 'done'): ");
        fgets(buf, sizeof(buf), stdin);
        write(server_fd, buf, strlen(buf) + 1);

        client_fd = open(CLIENT_FIFO, O_RDONLY);

        read(client_fd, buf, sizeof(buf));
        printf("Server response: %s\n", buf);

        close(client_fd);

        if (strcmp(buf, "Server cleanup done.\n") == 0) {
            break;
        }
    }
    close(server_fd);
    unlink(CLIENT_FIFO);

    return 0;
}
