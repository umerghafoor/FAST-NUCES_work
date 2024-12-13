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

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *message;
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	//memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
    while(1)
    {
        int n, len;
        char message[MAXLINE];

        printf("Enter message (Enter exit to Exit): ");
        scanf("%s", message);

        if(strcmp(message, "exit") == 0)
        {
            printf("Client Exit...\n");
            break;
        }
        
        sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
            
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len);
        buffer[n] = '\0';
        printf("Server : byte size is %s\n", buffer);
        
    }
    close(sockfd);
    return 0;
}