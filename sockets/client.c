#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define BUFSIZE 108

const char * path = "/tmp/mysocket";

int main(int argc, char * argv[]){
  int soc, numBytes;
  struct sockaddr_un server;
  char buff[BUFSIZE], line[BUFSIZE];

  if ((soc = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("Error creating socket");
    return EXIT_FAILURE;
  }

  memset(&server, 0, sizeof(struct sockaddr_un));
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, path);

  if (connect(soc, (struct sockaddr *)&server, sizeof(struct sockaddr_un))) {
    perror("Failed to connect");
    return EXIT_FAILURE;
  }

  while (!feof(stdin)){
    fgets(line, BUFSIZE, stdin);
    if (write(soc, line, BUFSIZE) == -1) {
      perror("Write failed for client");
      break;
    }
    memset(buff, 0, BUFSIZE);
    /* Receive data! */
    if ((numBytes = recv(soc, buff, BUFSIZE, 0)) == -1) {
      perror("Read failed");
      exit(EXIT_FAILURE);
    }
    buff[numBytes] = '\0';
    printf("Envia el servidor: %s\n", buff);
  }

  close(soc);
  printf("paso el cliente por aqui\n");
}
