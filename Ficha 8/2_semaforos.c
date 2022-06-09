#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

void * pingThread(void *param) {

    int i;
    for (i = 0; i < 10; i++){

        sem_wait(&sem1);
        printf("PING\n");
        sem_post(&sem2);
    }
    return NULL;
}

void * pongThread(void * param) {

    int i;
    for (i = 0; i < 10; i++){

        sem_wait(&sem2);
        printf("PONG\n");
        sem_post(&sem1);
    }
    return NULL;
}

int main (int argc, const char * argv[]) {

    pthread_t ping, pong;
    sem_init(&sem1,0,1);//inicializado a 1
    sem_init(&sem2,0,0);//inicializado a 0
    pthread_create(&ping, NULL, pingThread, NULL);
    pthread_create(&pong, NULL, pongThread, NULL);
    pthread_join(ping, NULL);
    pthread_join(pong, NULL);
    return 0;
}

