#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2=PTHREAD_MUTEX_INITIALIZER;

void * pingThread(void *param) {

    int i;
    for (i = 0; i < 10; i++){
        pthread_mutex_lock(&mutex);
        printf("PING\n");
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void * pongThread(void * param) {

    int i;
    for (i = 0; i < 10; i++){
        pthread_mutex_lock(&mutex2);
        printf("PONG\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main (int argc, const char * argv[]) {

    pthread_t ping, pong;
    pthread_create(&ping, NULL, pingThread, NULL);
    pthread_create(&pong, NULL, pongThread, NULL);
    pthread_join(ping, NULL);
    pthread_join(pong, NULL);
    return 0;
}
