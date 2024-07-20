#include <signal.h>
#include<stdio.h>



int main() {
    sigset_t set;
    int ret;

	// Initialize the signal set to be empty
	///ret = sigemptyset(&set);
	//if (ret != 0) {
	// Handle error
	//} 

	// Alternatively, to initialize the set to contain all signals:
	 ret = sigfillset(&set);

	// Add SIGINT to the set
	//ret = sigaddset(&set, SIGINT);
	if (ret != 0) {
	    perror("error creating signal set\n");
	}

	// Add another signal, e.g., SIGQUIT
	//ret = sigaddset(&set, SIGQUIT);
	//if (ret != 0) {
	    // Handle error
	//}
	
	//if (sigismember(&set, SIGINT)) {
	//    printf("SIGINT is in the set\n");
	//} else {
	//    printf("SIGINT is not in the set\n");
	//}
	
	
	// Block signals
	ret = sigprocmask(SIG_BLOCK, &set, NULL);
	if (ret != 0) {
	    // Handle error
	}

	// Do work here with the signals blocked
	printf("all the signals are blocked for 5 seconds\n");
	sleep(5);

    

	// Unblock signals
	ret = sigprocmask(SIG_UNBLOCK, &set, NULL);
	if (ret != 0) {
	    // Handle error
	}
	printf("all the signals are unblocked now\n");
	


    return 0;
}