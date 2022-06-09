// This program forks two children connected by a pipe
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 256

int main(int argc,char **argv)
{
	int fds[2],n;
	char buffer[MAXSIZE];
	pid_t pid;

	pipe(fds);										/* create the pipe...will be shared by both children */
	
	if((pid=fork())==0){							/* Child 1 */
		close(fds[0]);								/* Closing the read end of the pipe */
		sprintf(buffer, "Hello Brother!\n");								
		write(fds[1],buffer,strlen(buffer));
		close(fds[1]);
		exit(0);	
	}
	else{
		if((pid=fork())==0){						/* Child 2 */
		close(fds[1]);								/* Closing the write end of the pipe */
		n=read(fds[0], buffer, MAXSIZE);			/* Reading ...*/
		buffer[n]='\0';
		write(STDOUT_FILENO,buffer,strlen(buffer));
		close(fds[0]);
		exit(0);	
		}

		else{										/* Parent */
			close(fds[0]);
			close(fds[1]);
			waitpid(-1,NULL,0);
			waitpid(-1,NULL,0);
			exit(0);
		}
	}
	return 0;
}
