#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char **argv)
{
	int fp;
	fp = open(argv[1],O_CREAT|O_APPEND|O_WRONLY,0644);
	if(fp == -1){
		printf("Can't redirect output!\n");
		exit(1);
	}
	else{
		//close (1);
		//dup(fp);
		dup2(fp,1); // exactly the same…
		printf("Olá Mundo!\n");

	}
	return 0;
}