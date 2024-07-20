#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define SERVER_FIFO "/home/umerghafoor/myfiles/LAB5/serverFIFO"
#define CLIENT_FIFO "/home/umerghafoor/myfiles/LAB5/clientFIFO"


int main() {
    int server_fd, client_fd;
    char buf[50];
    char dob[50];
    char star_sign[50];

    // Create client FIFO
    printf("Creating Clint . . .\n");
    mkfifo(CLIENT_FIFO, 0666);

    printf("Enter your date of birth (dd/mm): ");
    fgets(buf, sizeof(buf), stdin);

    // Send date of birth to server
    printf("Clint requesting. . .\n");
    client_fd = open(CLIENT_FIFO, O_WRONLY);
    if (client_fd == -1) {
    printf("unable to open myfifo\n");
    }
    else{
        printf("request sent to server\n");
    }
    write(client_fd, buf, strlen(buf) + 1);
    close(client_fd);

    printf("Clint reading. . .\n");
    // Read star sign from server
    server_fd = open(SERVER_FIFO, O_RDONLY);
    read(server_fd, star_sign, sizeof(star_sign));
    close(server_fd);

    // Display star sign received from server
    printf("Your Zodiac sign is %s", star_sign);
    printf("\n");

    // Remove client FIFO
    unlink(CLIENT_FIFO);

    return 0;
}
