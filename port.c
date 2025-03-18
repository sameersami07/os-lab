#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#define MAX_PORTS 5
sem_t ports_semaphore;
void* openPort(void* arg){
    printf("open the port %ld..",(long)arg);
    sem_wait(&ports_semaphore);
    printf("action on the port %ld..",(long)arg);
    sleep(2);
    printf("close the port %ld..",(long)arg);
    sem_post(&ports_semaphore);

    return NULL;
}
int main(){
    pthread_t threads[10];
    long i;
    sem_init(&portSemaphore,0,MAX_PORTS);
    for(i=0;i<10;i++){
        pthread_create(&threads[i],NULL,openPort,(void*)i);

    }
    for(i=0;i<10;i++){
        pthread_join(threads[i],NULL);

    }
    sem_destroy(&ports_semaphore);
}
