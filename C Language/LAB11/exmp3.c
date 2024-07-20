#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *thread_function(void *arg);

char message[] = "I am thread 1";

int main() {
    pthread_t td;
    pthread_attr_t thread_attr;

    pthread_attr_init(&thread_attr);
    // Comment the following line in the 2nd run
    // pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    // Uncomment the following line in the 2nd run
    // pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&td, &thread_attr, thread_function, (void *)message);
    pthread_attr_destroy(&thread_attr);

    int join_ret;
    join_ret = pthread_join(td, NULL);
    if (join_ret == 0) {
        // when join successful
        printf("Join was successful: The main thread was waiting for thread.\n");
    } else {
        printf("Join failed: The main thread is not waiting for thread 1.\n");
    }
    printf("The main thread finished, bye!\n");
    pthread_exit(NULL);
}

void *thread_function(void *arg) {
    printf("thread_function is running. Argument was \"%s\"\n", (char *)arg);
    sleep(4);
    printf("Thread awakened from sleep and exiting now.\n");
    pthread_exit(NULL);
}