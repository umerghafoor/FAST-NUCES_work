#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <netinet/in.h>
int main() {
   
    char request[256] = "I am a message from client";
    char buf[200];

    char username[256];
    char password[256];
   
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    
    // create the socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
   
    //setup an address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);

    // send message to server
    request[0] = '\0';
    strcpy(request, "{");
    strcat(request, username);
    strcat(request, ",");
    strcat(request, password);
    strcat(request, "}");
    // printf("\n %s \n", request);

    //connect to server here
    int p = connect(sock, (struct sockaddr*)&server_address,sizeof(server_address));
	send(sock, request, sizeof(request), 0);

 
    //send message to server
    recv(sock, &buf, sizeof(buf), 0);
	printf("\n %s \n", buf);

   
    close(sock);

    return 0;
}