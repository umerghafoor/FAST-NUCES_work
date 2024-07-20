#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>



void sigsegv_handler(int sig, siginfo_t *siginfo, void *context) {
    printf("Caught segmentation fault: SIGSEGV\n");
    printf("Address causing the fault: %p\n", siginfo->si_addr);
    _Exit(EXIT_FAILURE); // Use _Exit to exit immediately without calling cleanup functions
}



void stackOverflow(int count) {
    printf("Stack depth: %d\n", count);
    stackOverflow(count + 1);
}

int main() {
  struct sigaction sa;

    memset(&sa, 0, sizeof(sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigsegv_handler;

    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Deliberately cause a segmentation fault
  //  int *ptr = NULL;
   // *ptr = 42;
 stackOverflow(1);
    return 0;
}