// Task 2: Palindrome check
// Design a UDP server and client. The client will send the server a string and the server will have
// to validate if the received string is a palindrome or not. The server will return “True” to the
// client if the string is a palindrome. Otherwise it will return false


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

int checkPalindrome(char *str) {
    int l = 0;
    int h = strlen(str) - 1;
    while (h > l) {
        if (str[l++] != str[h--]) {
            return 0;
        }
    }
    return 1;
}

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
        printf("Client Message: %s\n", buffer);
        if(checkPalindrome(buffer))
        {
            sendto(sockfd, (const char *)"True", strlen("True"), 0, (const struct sockaddr *) &cliaddr, len);
            printf("Palindrome: True\n");
        }
        else
        {
            sendto(sockfd, (const char *)"False", strlen("False"), 0, (const struct sockaddr *) &cliaddr, len);
            printf("Palindrome: False\n");
        }
        // sprintf(message, "%d", byte_size);

        // sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *) &cliaddr, len);
        // printf("Byte Size sent: %s\n", message);

        // // Check for interrupt signal to close the server
        // if (strcmp(buffer, "exit") == 0) {
        //     printf("Server closed.\n");
        //     break;
        // }
    }
	return 0;
}