#include <iostream>
#include <pthread.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <random>

typedef struct {
    int total;
    int waiting;
} counter_t;

const int NUM_READERS = 5;
const int NUM_WRITERS = 5;

int x = 1;                      // Shared global variable.

pthread_mutex_t mutex;          // Mutex for e counter variable.
counter_t readersCounter = {0, 0};

// 2 condition variables
pthread_cond_t readPhase = PTHREAD_COND_INITIALIZER;
pthread_cond_t writePhase = PTHREAD_COND_INITIALIZER;

void *write(void *args) {
    // Wait random amount of time
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10); // distribution in range [1, 6]
    std::this_thread::sleep_for (std::chrono::seconds(dist6(rng)));

    // Enter critical section
    pthread_mutex_lock(&mutex);
    while (readersCounter.total != 0) {
        pthread_cond_wait(&writePhase, &mutex);
    }
    readersCounter.total = -1;
    pthread_mutex_unlock(&mutex);

    // Critical section
    x = x * 3 + 1;
    std::cout << "Value Written: " << x << std::endl;
    std::cout << "Number of Readers Waiting: " << readersCounter.waiting << std::endl;

    // Exit critical section
    pthread_mutex_lock(&mutex);
    readersCounter.total = 0;
    if (readersCounter.waiting > 0) {
        pthread_cond_broadcast(&readPhase);
    } else {
        pthread_cond_signal(&writePhase);
    }
    pthread_mutex_unlock(&mutex);
}

void *read(void *args) {
    // Wait random amount of time
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10); // distribution in range [1, 6]
    std::this_thread::sleep_for (std::chrono::seconds(dist6(rng)));

    // Enter critical section
    pthread_mutex_lock(&mutex);
    readersCounter.waiting++;
    while (readersCounter.total == -1) {
        pthread_cond_wait(&readPhase, &mutex);
    }
    readersCounter.waiting--;
    readersCounter.total++;
    pthread_mutex_unlock(&mutex);

    // Critical section
    std::cout << "Value Read: " << x << std::endl;
    std::cout << "Number of Readers Present: " << readersCounter.total << std::endl;

    // Exit critical section
    pthread_mutex_lock(&mutex);
    readersCounter.total--;
    if (readersCounter.total == 0) {
        pthread_cond_signal(&writePhase);
    }
    pthread_mutex_unlock(&mutex);
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    for (pthread_t *p = readers; p != readers + NUM_READERS; p++) {
        pthread_create(p, nullptr, read, nullptr);
    }

    for (pthread_t *p = writers; p != writers + NUM_WRITERS; p++) {
        pthread_create(p, nullptr, write, nullptr);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], nullptr);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], nullptr);
    }

    return 0;
}