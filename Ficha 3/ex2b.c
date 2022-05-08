#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
    int i;
    for(i=0; i<5; i++){

        pid_t pid=fork();

        if(pid==0){             //processo filho

            srandom(getpid());
            int r = random()%100;
            printf("Child: %d\n",r);
            exit(r);
        }else{
            int status;
            waitpid(pid,&status,0);
            printf("Parent: %d\n",WEXITSTATUS(status));
        }
    }
return 0;
}
