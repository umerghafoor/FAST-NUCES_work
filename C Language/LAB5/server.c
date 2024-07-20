#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define SERVER_FIFO "/home/umerghafoor/myfiles/LAB5/serverFIFO"
#define CLIENT_FIFO "/home/umerghafoor/myfiles/LAB5/clientFIFO"


int main() {
    int server_fd, client_fd;
    char buf[50];
    char cmd[50];
    
    printf("Server is Starting\n");
    // Creating server FIFO
    mkfifo(SERVER_FIFO, 0666);
    
    printf("Server is Runing\n");
        while(1){
        // Open server FIFO for writing
        
        // Read input from client FIFO
        client_fd = open(CLIENT_FIFO, O_RDONLY);

        if (client_fd == -1) {
            //close(client_fd);
            continue;
        }

        read(client_fd, buf, sizeof(buf));
        close(client_fd);
        
        // Extract day and month from input
        char *dob = strtok(buf, "=");
        int day, month;
        sscanf(dob, "%d/%d", &day, &month);
        
        // Determine star sign using date2star
        char star_sign[50];
        if(month>0 && month <13){
            sprintf(cmd, "./date2star %d %d", day, month);
            FILE *fp = popen(cmd, "r");
            if (fp == NULL) {
                perror("popen");
                exit(EXIT_FAILURE);
            }
        fgets(star_sign, sizeof(star_sign), fp); //geting response for dat2star
        pclose(fp);
        }

        // Send star sign to client
        server_fd = open(SERVER_FIFO, O_WRONLY);
        write(server_fd, star_sign, strlen(star_sign) + 1);
        close(server_fd);

        // Display star sign on server terminal
        printf("Star sign: %s", star_sign);
        //printf("\n");
        printf(" Received date: %s", buf);
        //printf("\n");
        }
    return 0;
}
