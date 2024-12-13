#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void* critical_file_processing(void* arg) {
    printf("Critical file processing started.\n");
    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    int* allocated_memory = (int*)malloc(sizeof(int) * 100);
    if (allocated_memory == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    pthread_cleanup_push(free, allocated_memory);

    for (int i = 0; i < 5; i++) {
        printf("Processing critical file... Step %d\n", i + 1);
        sleep(1);

        pthread_testcancel();
    }

    printf("Critical file processing completed.\n");

    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}


void* non_critical_file_processing(void* arg) {
    printf("Non-critical file processing started.\n");

    for (int i = 0; i < 3; i++) {
        printf("Processing non-critical file... Step %d\n", i + 1);
        sleep(1);
    }

    printf("Non-critical file processing completed.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t critical_thread, non_critical_thread;
    pthread_attr_t attr;
    int err;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    //non-critical thread
    err = pthread_create(&non_critical_thread, &attr, non_critical_file_processing, NULL);
    if (err != 0) {
        fprintf(stderr, "Error creating non-critical thread: %s\n", strerror(err));
        return 1;
    }

    //critical thread
    err = pthread_create(&critical_thread, NULL, critical_file_processing, NULL);
    if (err != 0) {
        fprintf(stderr, "Error creating critical thread: %s\n", strerror(err));
        return 1;
    }

    sleep(2);

    printf("Requesting to cancel the critical thread...\n");
    err = pthread_cancel(critical_thread);
    if (err != 0) {
        fprintf(stderr, "Error canceling critical thread: %s\n", strerror(err));
        return 1;
    }

    err = pthread_join(critical_thread, NULL);
    if (err != 0) {
        fprintf(stderr, "Error joining critical thread: %s\n", strerror(err));
        return 1;
    }

    pthread_attr_destroy(&attr);

    printf("Main thread finished.\n");
    return 0;
}
