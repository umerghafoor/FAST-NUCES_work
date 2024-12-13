#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionA(void *);
void *functionB(void *);

pthread_mutex_t mutex1;
pthread_t thread1, thread2;
pthread_t thread3, thread4;

int counter = 0;

int main()
{
    pthread_mutex_init(&mutex1, NULL);
    pthread_create(&thread1, NULL, &functionA, NULL);
    pthread_create(&thread2, NULL, &functionB, NULL);
    pthread_create(&thread3, NULL, &functionA, NULL);
    pthread_create(&thread4, NULL, &functionB, NULL);

    printf("Thread 1 ID :%ld\n", thread1);
    printf("Thread 2 ID :%ld\n", thread2);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    
    pthread_mutex_destroy(&mutex1);
    
    pthread_exit(NULL);
    exit(0);
}

void *functionA(void *)
{
    int a=0;
    // pthread_mutex_lock(&mutex1);
    a = counter;
    a--;
    counter--;
    printf("Thread 1 ID :%ld Counter value:%d\n", pthread_self(), counter);
    // pthread_mutex_unlock(&mutex1);
    // pthread_exit(NULL);
}

void *functionB(void *)
{
    int b=0;
    // pthread_mutex_lock(&mutex1);
    b = counter;
    b++;
    counter++;
    printf("Thread 2 ID :%ld Counter value:%d\n", pthread_self(), counter);
    // pthread_mutex_unlock(&mutex1);
    // pthread_exit(NULL);
}