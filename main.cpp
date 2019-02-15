#include <iostream>
#include <pthread.h>

pthread_mutex_t mutex;          // Mutex that controls access to the global variables.
int x = 1;                      // Shared global variable.
int totalNumReaders = 0;        // Total number of readers
int numWaitingReaders = 0;      //  Number of readers waiting to acquire the mutex

// 2 condition variables
pthread_cond_t readPhase = PTHREAD_COND_INITIALIZER;
pthread_cond_t writePhase = PTHREAD_COND_INITIALIZER;

void *write() {
    // Wait random amount of time

    // Enter critical section

    // Critical section

    // Exit critical section
}

void *read() {
    // Wait random amount of time

    // Enter critical section

    // Critical section

    // Exit critical section
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    pthread_t readers[5];
    pthread_t writers[5];


    return 0;
}