#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>

#define PORT 4444
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

typedef struct {
    int sockfd;
    int id;
} client_t;

// Shared memory and semaphore setup
int shmid;
client_t *clients;
sem_t *sem;

// Function to broadcast messages to all connected clients except the sender
void broadcast_message(const char *message, int sender_id) {
    sem_wait(sem); // Lock the semaphore before accessing shared memory
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].sockfd != 0 && clients[i].id != sender_id) {
            send(clients[i].sockfd, message, strlen(message), 0);
            printf("redirecting to %d\n", clients[i].sockfd);
        }
    }
    sem_post(sem); // Unlock the semaphore after access
}

// Signal handler to clean up shared memory and semaphore on exit
void cleanup(int signo) {
    shmdt(clients);
    shmctl(shmid, IPC_RMID, NULL);
    sem_close(sem);
    sem_unlink("/client_sem");
    exit(0);
}

// Function to handle communication with a connected client
void handle_client(int index) {
    client_t *cli = &clients[index];
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    sprintf(message, "Client%d has connected\n", cli->id);
    printf("%s", message);
    broadcast_message(message, cli->id);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int recv_bytes = recv(cli->sockfd, buffer, BUFFER_SIZE, 0);

        if (recv_bytes <= 0 || strcmp(buffer, "exit\n") == 0) {
            sprintf(message, "Client%d has disconnected\n", cli->id);
            printf("%s", message);
            broadcast_message(message, cli->id);
            close(cli->sockfd);

            // Mark the client slot as available
            sem_wait(sem);
            clients[index].sockfd = 0;
            sem_post(sem);

            exit(0); // Terminate the child process
        }

        // Format and send the message to all clients
        sprintf(message, "Client%d: %s", cli->id, buffer);
        printf("%s", message);
        broadcast_message(message, cli->id);
    }
}

int main() {
    int sockfd, new_sock;
    struct sockaddr_in serverAddr, cliAddr;
    socklen_t addr_size;
    int client_index;

    // Setup shared memory for clients
    shmid = shmget(IPC_PRIVATE, MAX_CLIENTS * sizeof(client_t), IPC_CREAT | 0666);
    clients = (client_t *)shmat(shmid, NULL, 0);
    memset(clients, 0, MAX_CLIENTS * sizeof(client_t)); // Initialize all clients as disconnected

    // Setup semaphore for synchronizing client list access
    sem = sem_open("/client_sem", O_CREAT, 0644, 1);

    // Handle termination signals to clean up shared memory and semaphores
    signal(SIGINT, cleanup);

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    // Allow address reuse
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Initialize server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket to the address
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listen error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        addr_size = sizeof(cliAddr);
        new_sock = accept(sockfd, (struct sockaddr *)&cliAddr, &addr_size);

        if (new_sock < 0) {
            perror("Accept error");
            continue;
        }

        sem_wait(sem);

        // Find an empty slot for the new client
        for (client_index = 0; client_index < MAX_CLIENTS; client_index++) {
            if (clients[client_index].sockfd == 0) {
                clients[client_index].sockfd = new_sock;
                clients[client_index].id = client_index + 1;
                break;
            }
        }

        sem_post(sem);

        if (client_index == MAX_CLIENTS) {
            printf("Max clients reached. Connection refused.\n");
            close(new_sock);
        } else {
            // Fork a new process to handle the client
            if (fork() == 0) {
                close(sockfd); // Close the listening socket in the child process
                handle_client(client_index); // Handle communication with this client
            }
            // Print all Client IDs
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].sockfd != 0) {
                    printf("Client%d is connected\n", clients[i].id);
                }
            }
        }
    }

    close(sockfd);
    return 0;
}