#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 4444
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int clientSockets[MAX_CLIENTS];

void *client_handler(void *arg) {
    int clientSocket = *((int *)arg);
    char buffer[BUFFER_SIZE];
    int recv_bytes;

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recv_bytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (recv_bytes <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s\n", buffer);

        // Respond back to all the clients
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientSockets[i] != -1 && clientSockets[i] != clientSocket) {
                send(clientSockets[i], buffer, strlen(buffer), 0);
                printf("Sent to client %d\n", i);
            }
        }
    }

    close(clientSocket);
    pthread_exit(NULL);
}

int main() {
    int sockfd, ret;
    struct sockaddr_in serverAddr;
    struct sockaddr_in cliAddr;
    socklen_t addr_size;
    pthread_t tid;

    // Initialize client sockets
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientSockets[i] = -1;
    }

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error in connection.\n");
        exit(1);
    }

    printf("Server Socket is created.\n");

    // Allow address reuse
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Initialize address structure
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket
    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        printf("Error in binding.\n");
        exit(1);
    }

    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n\n");
    }

    addr_size = sizeof(cliAddr);

    while (1) {
        int clientSocket = accept(sockfd, (struct sockaddr*)&cliAddr, &addr_size);
        if (clientSocket < 0) {
            exit(1);
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

        // Add the client socket to the array
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientSockets[i] == -1) {
                clientSockets[i] = clientSocket;
                printf("Client %d added to the array\n", i);
                break;
            }
        }

        // Create a new thread for the client
        if (pthread_create(&tid, NULL, client_handler, (void *)&clientSocket) != 0) {
            perror("pthread_create");
            exit(1);
        }
        pthread_detach(tid);
    }

    close(sockfd);
    return 0;
}
