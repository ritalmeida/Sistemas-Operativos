#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

#define SIZE 6

int primes[SIZE] = {2,3,5,7,11,13};
int soma = 0;

void* sum(void* arg) {

    int *ptr = (int*)arg;
    int ch = *ptr;
    int i;

    if(ch == 0){                                                    //par

        for(i = 0; i < SIZE; i++){

            if(primes[i] % 2 == 0){

                soma += primes[i];
                primes[i] = 0;
            }
        }
    }
    if(ch == 1){                                                    //impar
        for(i = 0; i < SIZE; i++){

            if(primes[i] % 2 != 0){

                soma += primes[i];
                primes[i] = 0;
            }
        }
    }

}


int main () {

    pthread_t thread1_id;
    pthread_t thread2_id;

    int i;

    int pi[2] = {0,1};                                                      //0=par, 1=impar

    pthread_t threads[2];

    for(i = 0; i < 2; i++)
        pthread_create(&threads[i],NULL,&sum,&pi[i]);

    for(i = 0; i < 2; i++)
        pthread_join(threads[i],NULL);


    printf("\nSoma = %d\n",soma);

    for(i = 0; i < 6; i++)
        printf("[%d] -> %d\n",i,primes[i]);

    return 0;
}