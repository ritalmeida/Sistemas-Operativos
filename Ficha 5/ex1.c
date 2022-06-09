#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int main() {

    char buff[20];
    int pipe1[2],pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    char *msg = "Sistemas Operativos";
    size_t size = strlen(msg);

    pid_t pid=fork();

    if (pid == -1) {

        printf("erro!!\n");
        exit(-1);
    }

    if (pid == 0){

        printf("Filho: \n");
        printf("%s\n", msg);
        close(pipe1[1]);
        read(pipe1[0], buff, size);
        close(pipe1[0]);
        close(pipe2[0]);
        int i;
        for (i = 0; i < size; i++){

            buff[i] = toupper(buff[i]);
        }
        write(pipe2[1], buff, size);
        close(pipe2[1]);

    }else{

        printf("Pai: \n");
        close(pipe1[0]);
        write(pipe1[1], msg, size);
        close(pipe1[1]);
        wait(NULL);
        close(pipe2[1]);
        read(pipe2[0], buff, size);
        close(pipe2[0]);
        printf("%s\n", buff);
    }
    return 0;
}