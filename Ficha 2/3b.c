#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    	
	printf("UID = %d\n", (int) getuid());
	printf("GID = %d\n", (int) getgid());
	printf("PID = %d\n", (int) getpid());
	printf("PPID = %d\n", (int) getppid());
	printf("PPID = %d\n", (int) getppid());
	printf("PATH = %s\n", getenv("PATH"));
	printf("HOME = %s\n", getenv("HOME"));
	char cwd[265];
	printf("CWD = %s\n", getcwd(cwd, sizeof(cwd)));
    return 0;
}