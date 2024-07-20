#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function1(void *arg);
pthread_t td1;

int main() {
    pthread_create(&td1, NULL, thread_function1, NULL);
    sleep(2);
    printf("Main thread: Canceling thread 1...\n");
    pthread_cancel(td1);
    printf("Main thread: Exiting\n");
    pthread_exit(NULL);
}

void *thread_function1(void *arg) {
    int i, oldstate;
    // comment following line in 2nd run
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate); // uncomment following line in 2nd run
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    printf("Thread 1: I am running and the old cancel state was %d\n", oldstate);
    for (i = 0; i < 10; i++) {
        printf("Thread 1: I am still running (%d)...\n", i);
        sleep(2);
    }
    pthread_exit(0);
}