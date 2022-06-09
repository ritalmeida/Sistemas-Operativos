#include <sys/un.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BUF_SIZE 4096                                                       // block transfer size
#define LISTENQ 2                                                           // Size of the listen Queue


char *socket_path = "/tmp/socket";


int main(int argc, char const *argv[]) {
  int listenfd,connfd,fd,bytes;
  char buf[BUF_SIZE];
  struct sockaddr_un channel_srv;

  if ( (listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
      perror("socket error");
      exit(-1);
  }

  unlink(socket_path);

  memset(&channel_srv, 0, sizeof(channel_srv));
  channel_srv.sun_family = AF_UNIX;
  strncpy(channel_srv.sun_path, socket_path, sizeof(channel_srv.sun_path)-1);

  if (bind(listenfd, (struct sockaddr*)&channel_srv, sizeof(channel_srv)) == -1) {
      perror("bind error");
      exit(-1);
  }
  if (listen(listenfd, LISTENQ) == -1) {
      perror("listen error");
      exit(-1);
  }
  // CRIA�AO DOS FILHOS

  int pids[2];

  for(int i =0; i< 2; i++) {
    if((pids[i]=fork())==0) {
      char*arg[3]= {"client","ufp",NULL};
      execv("client",arg);
      printf("erro\n" );
      exit(-1);
    }
  }
  int k = 0;
  while (k <2) {

      // accept() devia ter uma lista ligada com os utilizadores de espera
      if ((connfd = accept(listenfd, NULL, NULL)) == -1) {                // bloqueia � espera de clientes
          perror("accept error");
          continue;
      }

      while (1) {
          bytes = read(connfd, buf, BUF_SIZE);                                // read from file
          if (bytes <= 0) break;                                          // check for end of file
          write(1, buf, bytes);                                           // write bytes to output
      }                                                      // close file
      close(connfd);
      k++;                                                    // close connection
  }
  return 0;
}
