#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

    int primes[] = {0,1,2,3,5,7,11,13,17,19};         //10 primeiros numeros primos

    pid_t pid1 = fork();                            //primeiro filho
    if(pid1 == 0){
        int i, sum1 = 0;
        for(i = 0; i < 10; i++){
            if(i % 2 == 0){
                sum1 += primes[i];
                primes[i] = 0;
            }
        }
    exit(sum1);
    }

    pid_t pid2 = fork();                              //segundo filho
    if(pid2 == 0){
        int j, sum2 = 0;
        for(j = 0; j < 10; j++){
            if(j % 2 != 0){
                sum2 += primes[j];
                primes[j] = 0;
            }
        }
    exit(sum2);
    }

    int result1;
    waitpid(pid1,&result1,0);
    printf("Child1: %d\n",WEXITSTATUS(result1));

     int result2;
    waitpid(pid2,&result2,0);
    printf("Child2: %d\n",WEXITSTATUS(result2));

    return 0;
}
