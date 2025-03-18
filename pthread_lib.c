#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREAD 5

void* thread_task(void* threadID) {
    long tid = (long)threadID;
    printf("Thread-%ld: Starting execution...\n", tid);
    sleep(2);
    printf("Thread-%ld: Stopping execution...\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREAD];
    long i;

    for (i = 0; i < NUM_THREAD; i++) {
        printf("Main: Creating thread %ld\n", i);
        if (pthread_create(&threads[i], NULL, thread_task, (void*)i)) {
            printf("Error: Unable to create thread %ld\n", i);
            exit(-1);
        }
    }

    for (i = 0; i < NUM_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: All threads completed successfully.\n");
    return 0;
}
