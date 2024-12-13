#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>


const char *choices[] = {"rock", "paper", "scissors"};

void get_my_choice(char *my_choice) {
    int choice = 0;
    while (choice != 1 && choice != 2 && choice != 3) {
        printf("1. Rock\n2. Paper\n3. Scissors\n");
        scanf("%d", &choice);
    }
    
    strncpy(my_choice, choices[choice - 1], 256);
}

int main() {
    char result[200];

        int sock;
    while (1) 
    {
        
        // Create the socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            return 1;
        }
       
        // Setup an address
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(3001);
    
        // Connect to server
        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
            perror("Connection failed");
            close(sock);
            return 1;
        }

    char my_choice[256] = {0};
    get_my_choice(my_choice);
    printf("My choice: %s\n", my_choice);
    
    // Send the choice to the server
    send(sock, my_choice, strlen(my_choice), 0);

    // Receive server choice
    char server_option[256] = {0};
    recv(sock, server_option, sizeof(server_option), 0);
    printf("Server chose: %s\n", server_option);

    // Receive Result
    char client_option[256] = {0};
    recv(sock, client_option, sizeof(client_option), 0);
    printf("Result: %s\n", client_option);
        }
    

    // Close the socket
    close(sock);

    return 0;
}
