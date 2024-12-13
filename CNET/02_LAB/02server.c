#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

char *choices[] = {"rock", "paper", "scissors"};

void get_random_choice(char *my_choice)
{
    strcpy(my_choice, choices[rand() % 3]);
}

int main() {
    char server_option[256];
    char client_option[256];

    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 5);

    while (1) {
        // accept the connection
        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);

        // send the message
        recv(client_socket, &client_option, sizeof(client_option), 0);
        printf("Client chose: %s\n", client_option);
        get_random_choice(&server_option);
        printf("Server chose: %s\n", server_option);
        send(client_socket, server_option, sizeof(server_option), 0);

        // compare the choices
        if (strcmp(client_option, server_option) == 0)
        {
            char server_message[256] = "It's a tie!";
            printf("It's a tie!\n");
            send(client_socket, server_message, sizeof(server_message), 0);
        }
        else if (strcmp(client_option, "rock") == 0 && strcmp(server_option, "scissors") == 0)
        {
            char server_message[256] = "Client win!";
            printf("Client win!\n");
            send(client_socket, server_message, sizeof(server_message), 0);
        }
        else if (strcmp(client_option, "paper") == 0 && strcmp(server_option, "rock") == 0)
        {
            char server_message[256] = "Client win!";
            printf("Client win!\n");
            send(client_socket, server_message, sizeof(server_message), 0);
        }
        else if (strcmp(client_option, "scissors") == 0 && strcmp(server_option, "paper") == 0)
        {
            char server_message[256] = "Client win!";
            printf("Client win!\n");
            send(client_socket, server_message, sizeof(server_message), 0);
        }
        else
        {
            char server_message[256] = "Client lose!";
            printf("Client lose!\n");
            send(client_socket, server_message, sizeof(server_message), 0);
        }

        // close the client socket
        close(client_socket);
    }

    // close the server socket
    close(server_socket);

    return 0;
}
