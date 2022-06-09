#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc,char **argv)
{
    int fp=open("text.txt", O_RDONLY);
    char buff;

    int pipefd[2];
    pipe(pipefd);

    pid_t cpid1=fork();
    pid_t cpid2=fork();

    if(cpid1==0){
        close(pipefd[0]);
        while(read(fp,&buff,1)>0)
            write(pipefd[1],&buff,1);
        close(pipefd[1]);
        exit(0);
    }
    else if(cpid2==0){
        close(pipefd[0]);
        while(read(fp,&buff,1)>0)
            write(pipefd[1],&buff,1);
        close(pipefd[1]);
        exit(0);
    }
    wait(NULL);
    close(pipefd[1]);
    while(read(pipefd[0],&buff,1)>0)
        write(1,&buff,1);
    wait(NULL);
    while(read(pipefd[0],&buff,1)>0)
        write(1,&buff,1);
    exit(0);
}