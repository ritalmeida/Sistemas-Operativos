#include <sys/un.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
char *socket_path = "/tmp/socket";

#define BUF_SIZE 4096

int main(int argc, char **argv)
{
    int c, uds, bytes;
    char buf[BUF_SIZE];
    struct sockaddr_un channel;

    if (argc != 2) {
        printf("Usage: client file-name\n");
        exit(1);
    }

    if ( (uds = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(1);
    }

    memset(&channel, 0, sizeof(channel));
    channel.sun_family= AF_UNIX;
    strncpy(channel.sun_path, socket_path, sizeof(channel.sun_path)-1);

    if (connect(uds, (struct sockaddr*)&channel, sizeof(channel)) == -1) {
        perror("connect error");
        exit(-1);
    }


    int fd = open(argv[1],O_RDONLY);
    char p;

    char buffer[BUF_SIZE] ;
    sprintf(buffer,"[%d]",getpid());

    write(uds,&buffer,strlen(buffer));
    while(read(fd,&p,1)!=0) {
      write(uds,&p,1);
    }
    close(uds);
    close(fd);
    exit(getpid());

}
