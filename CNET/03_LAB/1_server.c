// # Task 1: Byte Calculation

// You have to create a UDP server and client. The client will send a message to the server and the
// server will calculate the byte size of the message and send it back to the client. This
// communication will continue until the client disconnects.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *message;
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	//memset(&servaddr, 0, sizeof(servaddr));
	//memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
        int len, n;
        char message[MAXLINE];

        len = sizeof(cliaddr);

        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        
        // Calculating Byte Size
        int byte_size = strlen(buffer);
        printf("Client Message: %s\n", buffer);
        sprintf(message, "%d", byte_size);

        sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *) &cliaddr, len);
        printf("Byte Size sent: %s\n", message);

        // // Check for interrupt signal to close the server
        // if (strcmp(buffer, "exit") == 0) {
        //     printf("Server closed.\n");
        //     break;
        // }
    }
	return 0;
}