// Task 1: Echo Server
// You have to create an authentication TCP server that will validate a client trying to connect to it.
// The client will send the server a username and password. If these credentials match the
// credentials stored on the server, the server will send a message welcoming the user. Otherwise
// the server will throw an error message.

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

int main() {

	char server_message[256] = "Connection Succesfull";
	char buf[200];

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

    // accept the connection
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    
    // send the message
    int recived = recv(client_socket, &buf, sizeof(buf), 0);
    // printf("\n %s \n", recived);
    if(strcmp(buf, "{umer,1234}") == 0)
    {
        printf("Umer Connected");
        send(client_socket, server_message, sizeof(server_message), 0);
    }
    else
    {
        printf("Invalid Credentials");
        server_message[0] = '\0';
        strcpy(server_message, "Invalid Credentials");
        send(client_socket, server_message, sizeof(server_message), 0);
        printf("\n %s \n", buf);
    }
    // close the socket
    close(server_socket);


	
	return 0;
}