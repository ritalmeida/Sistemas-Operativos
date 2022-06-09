#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

sem_t leitores, escritores;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int nl = 0; //numero de peepz a ler
int em_escrita = 0;
int leitores_espera = 0, escritores_espera = 0;

void inicia_leitura() {

    pthread_mutex_lock(&m);
    if (em_escrita || escritores_espera > 0) {

        leitores_espera++;
        pthread_mutex_unlock(&m);
        sem_wait(&leitores);
        pthread_mutex_lock(&m);
    } else

        nl++;
    pthread_mutex_unlock(&m);
}

void acaba_leitura() {

    pthread_mutex_lock(&m);
    nl--;

    if (nl == 0 && escritores_espera > 0) {

        sem_post(&escritores);
        em_escrita = 1;
        escritores_espera--;
    }
    pthread_mutex_unlock(&m);
}

void inicia_escrita() {

    pthread_mutex_lock(&m);

    if (em_escrita || nl > 0) {

        escritores_espera++;
        pthread_mutex_unlock(&m);
        sem_wait(&escritores);
        pthread_mutex_lock(&m);
    } else

        em_escrita = 1;
    pthread_mutex_unlock(&m);
}

void acaba_escrita() {

    pthread_mutex_lock(&m);
    em_escrita = 0;

    if (leitores_espera > 0)
        for (int i = 0; i < leitores_espera; ++i) {

            sem_post(&leitores);
            nl++;
            leitores_espera--;
        }
    else if (escritores_espera > 0) {

        sem_post(&escritores);
        em_escrita = 1;
        escritores_espera--;
    }
    pthread_mutex_unlock(&m);
}

void *ler() {

    while(1) {

        inicia_leitura();
        sleep(rand() % 2);
        acaba_leitura();
    }
}

void *escrever() {

    while(1) {

        inicia_escrita();
        sleep(rand() % 2);
        acaba_escrita();
    }
}

void *print_state() {

    while (1) {

        printf("nL:\t%d\nem_escrita:\t%d\nleitores_espera:\t%d\nescritores_espera\t%d\n", nl, em_escrita,
               leitores_espera, escritores_espera);
        sleep(1);
    }

}

int main(int argc, char **argv) {

    if (argc != 3) {

        printf("Argumentos mal inseridos:\nargv[1] = nLeitores e argv[2] = nEscritores\n");
        exit(1);
    }
    int nLeitores = atoi(argv[1]);
    int nEscritores = atoi(argv[2]);

    sem_init(&leitores, 0, 0);
    sem_init(&escritores, 0, 0);
    pthread_t writers[nLeitores], readers[nLeitores], tprint_state;
    int i;
    for (i = 0; i < nEscritores; ++i) {

        pthread_create(&writers[i], NULL, &escrever, NULL);
    }
    for (i = 0; i < nLeitores; ++i) {

        pthread_create(&readers[i], NULL, &ler, NULL);
    }
    pthread_create(&tprint_state,NULL,&print_state,NULL);

    for (i = 0; i < nEscritores; ++i) {

        pthread_join(writers[i], NULL);
    }
    for (i = 0; i < nLeitores; ++i) {

        pthread_join(readers[i], NULL);
    }

    return 0;
}