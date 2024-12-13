#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

void print_board() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

void get_random_position(int *row, int *col) {
    *row = rand() % 3;
    *col = rand() % 3;
    while (board[*row][*col] != ' ') {
        *row = rand() % 3;
        *col = rand() % 3;
    }
}

void add_choice_to_board(char choice, int row, int col) {
    board[row][col] = choice;
}

void send_board(int client_socket) {
    char board_str[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board_str[i * 3 + j] = board[i][j];
        }
    }
    send(client_socket, board_str, sizeof(board_str), 0);
}

int main() {
    char client_option[3];

    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    listen(server_socket, 5);

    while (1) {
        // Accept the connection
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Receive client's choice
        recv(client_socket, client_option, sizeof(client_option), 0);
        printf("Client chose: %s\n", client_option);
        int row = client_option[0] - '0';
        int col = client_option[1] - '0';

        // Update board with client's choice
        add_choice_to_board('X', row, col);
        print_board();

        // Get random position for server's move
        get_random_position(&row, &col);
        add_choice_to_board('O', row, col);
        printf("Server chose: %d%d\n", row, col);
        print_board();

        // Send updated board to client
        send_board(client_socket);

        // Close the client socket
        close(client_socket);
    }

    // Close the server socket
    close(server_socket);
    return 0;
}
