#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionA(void *);
void *functionB(void *);

pthread_mutex_t mutex1;

pthread_t thread1, thread2;

int counter = 0;

int main()
{
    pthread_mutex_init(&mutex1, NULL);
    pthread_create(&thread1, NULL, &functionA, NULL);
    pthread_create(&thread2, NULL, &functionB, NULL);

    printf("Thread 1 ID : %ld \n", thread1);
    printf("Thread 2 ID : %ld \n", thread2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex1);

    pthread_exit(NULL);
    exit(0);
}

void *functionA(void *p)
{
    int a;
    pthread_mutex_lock(&mutex1);
    a = counter;
    a--;
    counter = a;
    sleep(1);
    printf("Thread %ld Counter value: %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
}

void *functionB(void *p)
{
    int b;
    int mycount = 0;
    while (pthread_mutex_trylock(&mutex1) != 0)
    {
        while(mycount <= 800000)
        {
            mycount++;
        }
        // sleep(1);
        mycount = 0;
        printf("Thread trying to own lock\n");
    }
    b = counter;
    b++;
    counter = b;
    printf("Thread %ld Counter value : %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
}