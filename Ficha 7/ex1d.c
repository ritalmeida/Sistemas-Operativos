#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

void* fun_fact(void* arg) {

    int *prime_ptr = (int*)arg;//transformar um void* num int*
    int prime = *prime_ptr;	//tirar o contudo do pointer para um int
    int i;

    int fact = 1;
    //calc fact
    for(i = 2; i <= prime; i++){
        fact*=i;
    }
    *prime_ptr = fact; //alterar o valor no vetor

    pthread_exit(NULL);
}


int main () {

    pthread_t thread1_id;
    pthread_t thread2_id;
    int i;

    pthread_t threads[5]; //array com endereço dos 5 threads

    int primes[5] = {2,3,5,7,11};//array de primos(mais simples se esta fosse global)


    for(i = 0; i < 5; i++)
        pthread_create(&threads[i],NULL,&fun_fact,&primes[i]);

    for(i = 0; i < 5; i++)
        pthread_join(threads[i],NULL);

    for(i = 0; i < 5; i++)
        printf("[%d]->%d\n",i,primes[i]);

    /* Now we can safely return.  */
    return 0;
}