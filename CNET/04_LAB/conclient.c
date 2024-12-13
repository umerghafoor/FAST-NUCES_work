#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h> // Include select header

#define PORT 4444
#define BUFFER_SIZE 1024

int main() {
    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    char name[BUFFER_SIZE];

    // Get the client's name
    printf("Enter your name: ");
    fgets(name, BUFFER_SIZE, stdin);

    printf("Connecting as %s", name);

    // Creating socket id
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Client Socket is created.\n");

    // Initializing server address structure
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Connected to Server.\n");

    fd_set read_fds; // Set of file descriptors for select

    while (1) {
        // Clear the set
        FD_ZERO(&read_fds);

        // Add the client socket and stdin to the set
        FD_SET(clientSocket, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        // Wait for an activity on one of the sockets
        int activity = select(clientSocket + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0) {
            printf("Error in select.\n");
            break;
        }

        // Check if there is data to read from the server
        if (FD_ISSET(clientSocket, &read_fds)) {
            memset(buffer, 0, BUFFER_SIZE);
            int recv_bytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (recv_bytes <= 0) {
                printf("Disconnected from server.\n");
                break;
            }
            printf(" %s", buffer);
        }

        // Check if there is user input to send to the server
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);

            // Add the client's name to the buffer as username:buffer
            char tempBuffer[BUFFER_SIZE];
            // Remove '\n' from name
            name[strcspn(name, "\n")] = '\0';
            sprintf(tempBuffer, "%s\t: %s", name, buffer);
            strcpy(buffer, tempBuffer);
            
            send(clientSocket, buffer, strlen(buffer), 0);
        }
    }

    // Close the client socket
    close(clientSocket);
    return 0;
}
