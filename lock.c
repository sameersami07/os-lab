#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_PORTS 3  // Maximum number of ports that can be opened at once

sem_t ports_semaphore;  // Semaphore to control port access
pthread_mutex_t lock;   // Mutex for synchronizing print statements

// Function to open and close ports
void* openPort(void* threadID) {
    long tid = (long)threadID;

    // Request to open a port (decrease semaphore)
    sem_wait(&ports_semaphore);

    // Lock the mutex before printing (critical section)
    pthread_mutex_lock(&lock);
    printf("Port opened by thread %ld\n", tid);
    pthread_mutex_unlock(&lock);

    // Simulate some work for 2 seconds
    sleep(2);

    // Lock again to print port closure
    pthread_mutex_lock(&lock);
    printf("Port closed by thread %ld\n", tid);
    pthread_mutex_unlock(&lock);

    // Release the port (increase semaphore)
    sem_post(&ports_semaphore);

    return NULL;
}

int main() {
    pthread_t threads[10];
    long i;

    // Initialize semaphore with MAX_PORTS permits
    sem_init(&ports_semaphore, 0, MAX_PORTS);

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create 10 threads to simulate opening ports
    for (i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, openPort, (void*)i);
    }

    // Wait for all threads to finish
    for (i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up: destroy semaphore and mutex
    sem_destroy(&ports_semaphore);
    pthread_mutex_destroy(&lock);

    return 0;
}
