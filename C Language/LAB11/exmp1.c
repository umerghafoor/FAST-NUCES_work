# include <stdio.h>
# include <stdlib.h> 
# include <pthread.h>
# include <unistd.h>

void * thread_functon (void *arg );
char message [] = "iam thread 1 ";

int main () { 
    pthread_t td ; 
    pthread_create(&td ,NULL, thread_functon , ( void *) message ) ; 
    int joinret;
    joinret = pthread_join ( td ,NULL);
    if (joinret == 0) 
        printf (" join was successfull : The main thread was waitng for thread 1\n"); 
    else
        printf (" Join failed : The main thread is not waitng for thread 1\n") ; 
    printf ( "The main thread fnished , bye!\n" ) ;
    pthread_exit (NULL) ;
}

void * thread_functon (void *arg) {
    sleep(2);
    printf ( " thread_functon is running . Argument was\" %s\"\n",(char *) arg );
    printf ( " thread 1 awaked from sleep , and exitng now\n" ) ;
    pthread_exit (NULL);
}