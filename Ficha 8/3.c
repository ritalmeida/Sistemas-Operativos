#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define M 100

pthread_t spots[N]={0,0,0,0,0};

sem_t sem;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void * shop() {
    int i;

    while(1){
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);
        for(i=0;i<N;i++){
            if(spots[i]==0){
                spots[i]=pthread_self();
                printf("[%d] Parked\n",pthread_self());
                break;
            }
        }
        pthread_mutex_unlock(&mutex);
        printf("[%d] A comprar...\n",pthread_self());
        int r = rand() % 40;
        sleep(r);
        pthread_mutex_lock(&mutex);

        spots[i]=0;

        printf("[%d] Left\n",pthread_self());
        pthread_mutex_unlock(&mutex);
        sem_post(&sem);
        printf("[%d] Foi para casa...\n",pthread_self());
        r = rand() % 100;
        sleep(r);
    }

    return NULL;
}


int main (int argc, const char * argv[]) {

    pthread_t threads[M];
    int i;
    sem_init(&sem,0,N);//inicializado a 10

    for(i=0;i<M;i++){
        pthread_create(&threads[i], NULL, &shop, NULL);
    }

    for(i=0;i<M;i++){
        pthread_join(threads[i], NULL);
    }


    return 0;
}

