#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <ctype.h>
#define BUFSZ 108

const char *path = "/tmp/mysocket";

double selectOperation(char *chain);
double sum(int operand1, int operand2);
double subtract(int operand1, int operand2);
double multiplication(int operand1, int operand2);
double division(int operand1, int operand2);
int isNumeric(char *chain);

int main(int argc, char * argv[]){
  int idserver, clielen, result, c;
  double resultOperation;
  char buf[BUFSZ], line[BUFSZ];
  struct sockaddr_un server;
  struct sockaddr_un client;

  /* create local stream socket */
  if(( idserver = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
    perror("Error Creating Socket");
    exit(EXIT_FAILURE);
  }
  
  /* initialize local address */
  memset(&server, 0, sizeof(struct sockaddr_un));
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, path);
  /* bind local address to socket */
  if (bind(idserver, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) == -1) {
    perror("Error binding socket");
    exit(EXIT_FAILURE);
  }

  /* Ready for connections... */
  listen(idserver, 10);

  c = accept(idserver, (struct sockaddr *)&client, &clielen);
  while (1) {
    memset(buf, 0, BUFSZ);
    result = read(c, buf, BUFSZ);
    if (result == -1) {
      perror("Error reading from client");
      break;
    }
    if (result == 0) {
      break;
    }
    printf("Envia el cliente: %s\n", buf);
    buf[strlen(buf) - 1] = '\0';
    resultOperation = selectOperation(buf);
    if (resultOperation == -1) strcpy(line, "Digito mal los argumentos");
    else sprintf(line, "%1.3f", resultOperation);
    if(send(c, line, BUFSZ, 0) == -1){
      perror("Error write from server");
      exit(EXIT_FAILURE);
    }
  }
  close(c);
  close(idserver);
  unlink(path);
}

double selectOperation(char *chain){
  char *token, *option;
  int operand1, operand2;
  double result = -1;
  option = ((token = strtok(chain, " ")) != NULL) ? token : "0" ;
  operand1 = ((token = strtok(NULL, " ")) != NULL) ? isNumeric(token) : -1 ;
  operand2 = ((token = strtok(NULL, " ")) != NULL) ? isNumeric(token) : -1 ;
  if (operand1 == -1 || operand2 == -1) {
    return result;
  }
  if (strstr(option, "+")) {
    result = sum(operand1, operand2);
  }else if (strstr(option, "-")) {
    result = subtract(operand1, operand2);
  }else if(strstr(option, "*")){
    result = multiplication(operand1, operand2);
  }else if (strstr(option, "/")) {
    result = division(operand1, operand2);
  }
  return result;
}

double sum(int operand1, int operand2){
  return operand1 + operand2;
}

double subtract(int operand1, int operand2){
  return operand1 - operand2;
}

double multiplication(int operand1, int operand2){
  return operand1 * operand2;
}

double division(int operand1, int operand2){
  return operand1 / operand2;
}


int isNumeric(char *chain){
  char *ptr = chain;
  while (*ptr && isdigit(*ptr)) ptr++;
  return (*ptr ? -1: atoi(chain));
}
