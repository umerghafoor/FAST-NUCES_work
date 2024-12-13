#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define PORT 4444
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10
#define SHM_KEY 1234
#define SEM_KEY 5678

// Union for semaphore operations
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Semaphore operations
void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0}; // P operation
    semop(semid, &sb, 1);
}

void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0}; // V operation
    semop(semid, &sb, 1);
}

int main() {
    int sockfd, ret;
    struct sockaddr_in serverAddr, cliAddr;
    socklen_t addr_size;
    pid_t childpid;
    int shm_id, sem_id;
    int *clientSockets;
    char buffer[BUFFER_SIZE];

    // Create shared memory segment
    shm_id = shmget(SHM_KEY, MAX_CLIENTS * sizeof(int), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }
    clientSockets = (int *)shmat(shm_id, NULL, 0);
    if (clientSockets == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize client socket array in shared memory
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientSockets[i] = -1;
    }

    // Create semaphore
    sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }

    union semun sem_union;
    sem_union.val = 1; // Initialize semaphore value
    if (semctl(sem_id, 0, SETVAL, sem_union) < 0) {
        perror("semctl");
        exit(1);
    }

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
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
        perror("bind failed");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n\n");
    } else {
        perror("listen failed");
        close(sockfd);
        exit(1);
    }

    addr_size = sizeof(cliAddr);

    while (1) {
        int clientSocket = accept(sockfd, (struct sockaddr*)&cliAddr, &addr_size);
        if (clientSocket < 0) {
            perror("accept failed");
            continue; // Continue accepting new clients
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

        // Fork a new process for the client
        if ((childpid = fork()) == 0) {
            // Close the listening socket in the child process
            close(sockfd);

            // Add the client socket to the shared array
            sem_wait(sem_id);
            int client_added = 0;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clientSockets[i] == -1) {
                    clientSockets[i] = clientSocket;
                    printf("Client %d added to the array\n", i);
                    client_added = 1;
                    break;
                }
            }
            sem_signal(sem_id);

            if (!client_added) {
                printf("No space available for new client.\n");
                close(clientSocket);
                shmdt(clientSockets);
                exit(0);
            }

            while (1) {
                memset(buffer, 0, BUFFER_SIZE);
                int recv_bytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
                if (recv_bytes <= 0) {
                    printf("Client disconnected.\n");
                    break;
                }

                printf("Client: %s\n", buffer);

                // Send the message to all connected clients
                sem_wait(sem_id);
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (clientSockets[i] != -1 && clientSockets[i] != clientSocket) {
                        send(clientSockets[i], buffer, strlen(buffer), 0);
                        printf("Sent to client %d\n", i);
                    }
                }
                sem_signal(sem_id);
            }

            // Remove the client socket from the shared array
            sem_wait(sem_id);
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clientSockets[i] == clientSocket) {
                    clientSockets[i] = -1;
                    printf("Client %d removed from the array\n", i);
                    break;
                }
            }
            sem_signal(sem_id);

            close(clientSocket);
            shmdt(clientSockets);
            exit(0);
        } else {
            // Close the client socket in the parent process
            close(clientSocket);
        }
    }

    // Close the listening socket
    close(sockfd);
    // Cleanup shared memory and semaphore
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    return 0;
}
