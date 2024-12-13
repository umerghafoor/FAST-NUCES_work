#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main()
{
    char *fifo_pipe_send = "/home/umerghafoor/OS/06_LAB/fifo_2";
    char *fifo_pipe_recv = "/home/umerghafoor/OS/06_LAB/fifo_1";
    int send_res = mkfifo(fifo_pipe_send, 0666);
    int recv_res = mkfifo(fifo_pipe_send, 0666);
    char str1[100];
    char str2[100];
    int fd1, fd2;
    fd2 = open(fifo_pipe_recv, O_RDONLY);
    fd1 = open(fifo_pipe_send, O_WRONLY);

    if (fd1<0 || fd2<0)
        return -1;


    printf("opened pipe %d\n",fd1);
    printf("Chat started\n");
    while (1)
    {
        if (fd2 < 0)
            break;
        read(fd2, str2, 100);
        printf("recived: %s\n", str2);
        if (strncmp(str2, "exit", 4) == 0)
            break; 

        fgets(str1, 100, stdin);

        write(fd1, str1, strlen(str1) + 1);

        if (strncmp(str1, "exit", 4) == 0)
            break; 

    }
    close(fd1);
    close(fd2);
    unlink(fifo_pipe_send);
    return 0;
}