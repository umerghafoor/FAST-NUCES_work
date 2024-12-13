#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

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

void get_my_choice(int *row, int *col) {
    printf("Enter row and column (0-2 for both): ");
    scanf("%d %d", row, col);
    if (*row < 0 || *row > 2 || *col < 0 || *col > 2 || board[*row][*col] != ' ') {
        printf("Invalid choice. Please try again.\n");
        get_my_choice(row, col);
    }
}

void receive_board(int sock) {
    char board_str[9];
    recv(sock, board_str, sizeof(board_str), 0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = board_str[i * 3 + j];
        }
    }
    print_board();
}

int main() {
    int sock;
    struct sockaddr_in server_address;

    // Setup server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);

    // Create the socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    while (1) {
        int row, col;
        get_my_choice(&row, &col);

        // Format the choice for sending
        char my_choice[3] = {row + '0', col + '0', '\0'};
        printf("My choice: %s\n", my_choice);

        // Send the choice to the server
        send(sock, my_choice, strlen(my_choice), 0);

        // Receive and print the updated board from the server
        receive_board(sock);

        // Close the socket after each iteration
        close(sock);

        // Recreate and reconnect to the server for the next turn
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            return 1;
        }

        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
            perror("Connection failed");
            close(sock);
            return 1;
        }
    }

    return 0;
}
