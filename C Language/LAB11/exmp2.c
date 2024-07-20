#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function1(void *arg);
void *thread_function2(void *arg);

char message1[] = "I am thread 1";
char message2[] = "I am thread 2";

pthread_t tid1, tid2;

int main() {
    pthread_create(&tid1, NULL, thread_function1, (void *)message1);
    pthread_create(&tid2, NULL, thread_function2, (void *)message2);
    pthread_detach(tid1);

    int joinret;
    joinret = pthread_join(tid1, NULL);

    if (joinret == 0) {
        printf("Join was successful: The main thread was waiting for thread 1\n");
    } else {
        printf("Join failed: The main thread was not waiting for thread 1\n");
    }
    pthread_join(tid2, NULL);
    printf("The main received exit status from tid2, now exiting. Bye!\n");
    pthread_exit(NULL);
}

void *thread_function1(void *arg) {
    sleep(2);
    printf("thread_function1 is running. Argument was %s\n", (char *)arg);
    sleep(5);
    printf("thread 1 awakened from sleep and exiting now\n");
    pthread_exit(NULL);
}

void *thread_function2(void *arg) {
    sleep(1);
    int joinret;
    joinret = pthread_join(tid1, NULL);

    if (joinret == 0) {
        printf("Join was successful: The thread 2 was waiting for thread 1\n");
    } else {
        printf("Join failed: The thread 2 is not waiting for thread 1\n");
    }

    printf("thread_function2 is running. Argument was %s\n", (char *)arg);
    printf("thread 2 is exiting now\n");
    pthread_exit(NULL);
}
