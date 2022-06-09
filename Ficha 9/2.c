#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int buf[N];
int prodptr=0, consptr=0;
sem_t pode_prod, pode_cons;
pthread_mutex_t trinco_t=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t trinco_p=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t trinco_c=PTHREAD_MUTEX_INITIALIZER;

void *prod() {

    while(1){

        int item=rand() % 20;
        sem_wait(&pode_prod);
        pthread_mutex_lock(&trinco_p);
        buf[prodptr]=item;
        prodptr=(prodptr+1)%N;
        pthread_mutex_unlock(&trinco_p);
        sem_post(&pode_cons);

    }

    return NULL;
}
void *cons() {

    while(1){

        int item;
        sem_wait(&pode_cons);
        pthread_mutex_lock(&trinco_c);
        item=buf[consptr];
        pthread_mutex_unlock(&trinco_c);
        sem_post(&pode_prod);

    }

    return NULL;
}


int main (int argc, const char * argv[]) {

    pthread_t pprod[N];
    pthread_t pcons[N];
    int i;
    sem_init(&pode_prod,0,N);
    sem_init(&pode_cons,0,0);

    for(i = 0; i < N; i++){
        pthread_create(&pprod[i], NULL, prod, NULL);
    }
    for(i = 0; i < N; i++){
        pthread_create(&pcons[i], NULL, cons, NULL);
    }
    while (1){

        for(i = 0 ; i < N; i++)

            printf("[i:%d]->%d",i,buf[i]);
        sleep(1);
        printf("\n");



    }
    for(i = 0; i < N; i++){

        pthread_join(pprod[i], NULL);
    }

    for(i = 0; i < N; i++){

        pthread_join(pcons[i], NULL);
    }


    return 0;
}
