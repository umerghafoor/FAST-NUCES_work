#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define ARRAY_SIZE 1000000

int *array;
int target;
int num_threads;
volatile bool found = false;
int found_index = -1;

typedef struct {
    int thread_id;
    int start;
    int end;
} ThreadArgs;

void* search(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*) args;
    int start = thread_args->start;
    int end = thread_args->end;
    int thread_id = thread_args->thread_id;

    for (int i = start; i <= end; ++i) {
        if (found) {
            return NULL;
        }
        if (array[i] == target) {
            found = true;
            found_index = i;
            printf("Thread %d found the target at index %d\n", thread_id, i);
            return NULL;
        }
    }
    return NULL;
}

int main() {
    
    printf("Enter the target to search: ");
    scanf("%d", &target);
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    array = (int*) malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 100000;
    }
    // array[8238] = target;

    pthread_t threads[num_threads];
    ThreadArgs thread_args[num_threads];
    int chunk_size = ARRAY_SIZE / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int thread_id = i;
        int start = i * chunk_size;
        int end;
        if (i == num_threads - 1) {
            end = ARRAY_SIZE - 1;
        } else {
            end = (i + 1) * chunk_size - 1;
        }
        thread_args[i].thread_id = thread_id;
        thread_args[i].start = start;
        thread_args[i].end = end;
        pthread_create(&threads[i], NULL, search, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    if (found) {
        printf("Target %d found at index %d\n", array[found_index], found_index);
    } else {
        printf("Target %d not found in the array\n", target);
    }

    free(array);
    return 0;
}
