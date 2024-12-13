# include <stdio.h>
# include <stdlib.h> 
# include <pthread.h>

void *functionC(void*);

//pthread_mutex_tmutex1 = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex1 ;
pthread_t thread1 , thread2;
int counter = 0;

int main()
{
    pthread_mutex_init(&mutex1 ,NULL);
    pthread_create(&thread1,NULL,&functionC ,NULL);
    pthread_create(&thread2,NULL,&functionC ,NULL);

    printf("Thread 1 ID : %ld \n", thread1);
    printf("Thread 2 ID : %ld \n", thread2);

    sleep(3) ;
    // pthread_join ( thread1 , NULL) ;
    // pthread_join ( thread2 , NULL) ;
    pthread_mutex_destroy(&mutex1);

    pthread_exit(NULL);
    exit(0);
}

void *functionC (void *)
{
    pthread_mutex_lock(&mutex1);
    counter ++;
    printf ("Thread %ld Counter value : %d\n",pthread_self(), counter);
    pthread_mutex_unlock( &mutex1);
    pthread_exit(NULL);
}
