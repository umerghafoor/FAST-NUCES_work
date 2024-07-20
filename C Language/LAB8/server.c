#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

#define SERVER_FIFO "/home/umerghafoor/myfiles/LAB8/serverFIFO"
#define CLIENT_FIFO "/home/umerghafoor/myfiles/LAB8/clientFIFO"

int server_fd, client_fd;

void closingProcess() {
    // Close FIFOs
    
}

void sigintHandler(int signum) 
{
    printf("Ctrl+C is disabled. Use 'Done' command to exit.\n");
}

int main() {
    char buf[50];
    
    // Set up signal handler for SIGINT (Ctrl+C) to call a balnk function
    signal(SIGINT, sigintHandler);
    
    printf("Server is Starting . . .\n");

    mkfifo(SERVER_FIFO, 0666);
    
    printf("Server is Running\n");

    while (1) 
    {
        server_fd = open(SERVER_FIFO, O_RDONLY);
        read(server_fd, buf, sizeof(buf));
        close(server_fd);

        client_fd = open(CLIENT_FIFO, O_WRONLY);

        if (strcmp(buf, "hello\n") == 0) 
        {
            write(client_fd, "Hi", 3);
        }
        else if (strcmp(buf, "Hello\n") == 0) 
        {
            write(client_fd, "Hi", 3);
        }
        else if (strcmp(buf, "done\n") == 0) 
        {
            close(server_fd);
            close(client_fd);
            unlink(SERVER_FIFO);
            unlink(CLIENT_FIFO);
    
            printf("Closing Process . . .\n");
            exit(EXIT_SUCCESS);
        }
        else 
        {
            write(client_fd, "! INVALID command !", 15);
        }
        close(client_fd);
    }
    return 0;
}
