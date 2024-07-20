// Consider a simulation of a shared bank account, where multiple threads (representing bank clients) need to perform
// financial operations on the same account. These operations include deposits and withdrawals. The main challenge is
// to ensure that these operations do not interfere with each other—for example, a withdrawal should not start 
// processing based on an outdated balance if a deposit is meant to occur first.
// Your task is to implement a thread-safe management system for this bank account using mutexes to synchronize access 
// to the account balance. Specifically, ensure that:No two operations (deposit or withdrawal) can run concurrently,
// thereby avoiding any race conditions.Withdrawals do not proceed if the balance is insufficient, and no overdrafts
// are allowed.
// Write a C program using POSIX threads that:
// Initializes a bank account with a given balance.
// Creates multiple threads where each thread can either deposit or withdraw money.
// Uses mutexes to ensure that the balance updates are thread-safe and prevent race conditions.
// Prints out the account balance after all operations have completed to verify the correct sequence of operations.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int balance = 0;
int total_deposit = 30000;
int total_withdraw = 40000;

pthread_mutex_t mutex;

void *deposit(void *arg)
{
    int total_deposit = *((int *)arg);
    //deposit in segments of 50 to simulate a long running process
    for (int i = 0; i < total_deposit; i += 50)
    {
        if(total_deposit<=0)
            break;
        // Lock the mutex
        pthread_mutex_lock(&mutex);

        balance += 50;
        total_deposit -= 50;
        printf("Deposited 50  Balance: %d\n",balance);

        // if(i==total_deposit-50)
        //     printf("Balance: %d\n",i);
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        
    }
    pthread_exit(NULL);
}

void *withdraw(void *arg)
{
    int total_withdraw = *((int *)arg);
    //withdraw in segments of 50 to simulate a long running process
    for (int i = 0; i < total_withdraw; i += 50)
    {
        if(total_withdraw<=0)
            break;
        // Lock the mutex
        pthread_mutex_lock(&mutex);
        
        if(balance>=50)
        {
            balance -= 50;
            total_withdraw -= 50;
            printf("Withdrawn 50  Balance: %d\n",balance);
        }
        else
        {
            i-=50;
            printf("Insufficient balance, Retying\n");
        }

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        // if(i==total_withdraw-50)
        //     printf("Balance: %d\n",i);
    }
    pthread_exit(NULL);
}

int main()
{
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    balance = 10000;

    // Create the threads for deposit and withdrawal
    pthread_t threads[4];
    int amounts[4] = {30000, 40000, 30000, 40000};

    for (int i = 0; i < 4; i++)
    {
        if (i % 2 == 0)
        {
            pthread_create(&threads[i], NULL, deposit, &amounts[i]);
        }
        else
        {
            pthread_create(&threads[i], NULL, withdraw, &amounts[i]);
        }
    }

    // Join the threads
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Print the final balance
    printf("Final balance : %d\n", balance);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}