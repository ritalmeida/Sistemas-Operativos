#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
                  pid_t  pid;
                  /* fork another process */
                  pid = fork();
                  if (pid < 0) { /* error occurred */
                        printf("Fork Failed\n");
                        exit(-1);
                  }
                  else if (pid == 0) { /* child process */
                        execlp("/bin/ls", "ls", NULL);
                      printf("Passei a execlp!");
			printf("Passei o execlp!\n");
                  }
                  else { /* parent process */
                         /* parent waiting for the child to complete */
                        waitpid (pid,NULL,0);
                        printf ("Child Complete\n");
                        exit(0);
} 
}
