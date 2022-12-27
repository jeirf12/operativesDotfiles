#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#define BUFSZ 108

char error;
const char *path = "/tmp/mysocket";

double selectOperation(char *chain);
double sum(double operand1, double operand2);
double subtract(double operand1, double operand2);
double multiplication(double operand1, double operand2);
double division(double operand1, double operand2);
int isNumeric(char *chain);

int main(int argc, char *argv[]) {
  int idserver, clielen, result, c;
  double resultOperation;
  char buf[BUFSZ], line[BUFSZ];
  struct sockaddr_un server;
  struct sockaddr_un client;

  /* create local stream socket */
  if ((idserver = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("Error Creating Socket");
    exit(EXIT_FAILURE);
  }

  /* initialize local address */
  memset(&server, 0, sizeof(struct sockaddr_un));
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, path);
  /* bind local address to socket */
  if (bind(idserver, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) ==
      -1) {
    perror("Error binding socket");
    exit(EXIT_FAILURE);
  }

  /* Ready for connections... */
  listen(idserver, 10);

  c = accept(idserver, (struct sockaddr *)&client, &clielen);
  while (1) {
    memset(buf, 0, BUFSZ);
    result = read(c, buf, BUFSZ);
    if (result == 0) break;
    if (result == -1) {
      perror("Error reading from client");
      break;
    }
    printf("Envia el cliente: %s\n", buf);
    buf[strlen(buf) - 1] = '\0';
    error = 0;
    resultOperation = selectOperation(buf);
    if (error < 0) strcpy(line, "Digito mal los argumentos");
    else if (error > 0) strcpy(line, "No se puede dividir por cero");
    else sprintf(line, "%1.2f", resultOperation);
    if (send(c, line, BUFSZ, 0) == -1) {
      perror("Error write from server");
      exit(EXIT_FAILURE);
    }
  }
  close(c);
  close(idserver);
  unlink(path);
}

double selectOperation(char *chain) {
  char *token, *option, *auxOperando2;
  double operand1, operand2, result = -1;
  option = ((token = strtok(chain, " ")) != NULL) ? token : "0";
  operand1 = ((token = strtok(NULL, " ")) != NULL) ? isNumeric(token) : error--;
  operand2 = ((token = strtok(NULL, " ")) != NULL) ? isNumeric(token) : error--;
  auxOperando2 = malloc(4 * sizeof(char *));
  sprintf(auxOperando2, "%1.0f", operand2);
  if (strstr(token, auxOperando2) && operand2 == 0 && strstr(option, "/")) {
    error = 1;
    return result;
  } else if (error < 0) {
    return result;
  } else if (strstr(option, "0")) {
    error = -1;
    return result;
  }
  switch (option[0]) {
    case '+': result = sum(operand1, operand2); break;
    case '-': result = subtract(operand1, operand2); break;
    case '/': result = division(operand1, operand2); break;
    case '*': result = multiplication(operand1, operand2); break;
  }
  return result;
}

double sum(double operand1, double operand2) { return operand1 + operand2; }

double subtract(double operand1, double operand2) { return operand1 - operand2; }

double multiplication(double operand1, double operand2) { return operand1 * operand2; }

double division(double operand1, double operand2) { return operand1 / operand2; }

int isNumeric(char *chain) {
  char *ptr = chain;
  if (chain[0] == '-') ptr++;
  while (*ptr && isdigit(*ptr)) ptr++;
  return (*ptr ? error-- : atoi(chain));
}
