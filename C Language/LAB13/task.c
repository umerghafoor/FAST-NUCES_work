#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 10256
#define MAX_Itrations 10
int buffer[MAX_ITEMS];
int fill = 0;
int use = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void export(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX_ITEMS;
}

int import() {
    int tmp = buffer[use];
    use = (use + 1) % MAX_ITEMS;
    return tmp;
}

void* producer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < MAX_Itrations; i++) {
        printf("Producer %d: trying to Export an item to buffer\n", id);
        
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        export(i);
        printf("Producer %d: an item has been placed in the buffer\n", id);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < MAX_Itrations; i++) {
        printf("Consumer %d: trying to import an item from the buffer\n", id);
        
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int tmp = import();
        printf("Producer %d: an item has been imported in buffer\n", id);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
    }
    return NULL;
}

void* exporter(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < MAX_Itrations; i++) {
        printf("Producer %d: trying to Export an item to buffer\n", id);
        
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        export(i);
        printf("Producer %d: an item has been placed in the buffer\n", id);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* importer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < MAX_Itrations; i++) {
        printf("Consumer %d: trying to import an item from the buffer\n", id);
        
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int tmp = import();
        printf("Producer %d: an item has been imported in buffer\n", id);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
    }
    return NULL;
}

int main() {
    pthread_t producers, consumers, impoter, exporter;
    int prod_ids[2] = {1, 2};
    int cons_ids[2] = {1, 2};
    
    sem_init(&empty, 0, MAX_ITEMS); 
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
 

    // create 4 threads importer expoter producer consmer
    pthread_create(&producers, NULL, producer, &prod_ids[0]);
    pthread_create(&producers, NULL, producer, &prod_ids[1]);
    pthread_create(&consumers, NULL, consumer, &cons_ids[0]);
    pthread_create(&consumers, NULL, consumer, &cons_ids[1]);

    pthread_join(producers, NULL);
    pthread_join(consumers, NULL);
    pthread_join(impoter, NULL);
    pthread_join(exporter, NULL);
    

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
