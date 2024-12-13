// Task 2: Simple Customer Shopping Using Threads
// Objective:
// Simulate a single customer buying fruits from shop using a thread. The goal is to understand
// basic thread creation and termination.
// Scenario:
// You need to write a program where a single customer thread attempts to buy Apples and 2
// Apricots from a shop. The price of Apples is Rs 300/kg and Apricots is 250/kg. There is a
// total balance in the bank account of the customer, when the customer pays for the fruits
// through his bank card, the amount is deducted from his total balance.

// Requirements:
// 1. Create 1 customer thread using pthread_create(). The thread should:
// o Ask user the amount of Apples and Apricots they have to buy in kgs.
// o Print &quot;Customer attempting to buy x kgs of Apples and y kgs of Apricots&quot;.
// o Use pthread_self() to print the thread&#39;s unique ID.
// o Check if there is enough balance in the account (starting with $1000). If so,
// deduct the total cost of fruits from the balance and print &quot;Withdrawal
// successful&quot;. Otherwise, print &quot;Insufficient funds&quot;.
// o After completing the withdrawal, the thread should terminate
// using pthread_exit().

// 2. Main thread:
// o The main thread should print the final balance after the customer thread has
// attempted to buy fruits using his/her bank card.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define APPLE_PRICE 300
#define APRICOT_PRICE 250

int balance = 1000;

void* customer_thread(void* arg) {
    int apples, apricots;
    printf("Enter the amount of Apples   : ");
    scanf("%d", &apples);
    printf("Enter the amount of Apricots : ");
    scanf("%d", &apricots);

    printf("Customer want to buy %d kgs of Apples and %d kgs of Apricots\n", apples, apricots);
    printf("Thread ID: %lu\n", pthread_self());

    int total_cost = (apples * APPLE_PRICE) + (apricots * APRICOT_PRICE);
    if (total_cost <= balance) {
        balance -= total_cost;
        printf("Withdrawal  successful\n");
    } else {
        printf("Insufficient   funds\n");
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t customer;
    pthread_create(&customer, NULL, customer_thread, NULL);
    pthread_join(customer, NULL);

    printf("Final balance: %d\n", balance);
    return 0;
}
