#include "barberodormilon.h"

int main(int argc, char *argv[]) {
  pthread_t bar_thread;
  pthread_t cli_thread;
  corte = 0;

  sem_init(&barbero, 0, 1);

  sem_init(&lleno, 0, N);

  sem_init(&clien, 0, 0);

  pthread_create(&bar_thread, NULL, cortando_barbero, NULL);
  pthread_create(&cli_thread, NULL, espera_cliente, NULL);
  sleep(10);
  return EXIT_SUCCESS;
}

void * cortando_barbero(void *arg){
  int nuevo_cliente;
  while (1) {
    nuevo_cliente = crea_cliente();
    verifica_semaforo(&clien);
    verifica_semaforo(&lleno);
    entra_cliente(nuevo_cliente);
    verifica_cambio(&lleno);
    verifica_cambio(&barbero);
  }
}

void * espera_cliente(void *arg) {
  int cliente;
  while(1) {
    verifica_semaforo(&barbero);
    cliente = sale_cliente();
    verifica_cambio(&clien);
    corte_cliente(cliente);
  }
}

void verifica_semaforo(sem_t *cliente) {
  sem_wait(cliente);
}

void verifica_cambio(sem_t *cliente) {
  sem_post(cliente);
}

int crea_cliente() {
  sleep(rand() % 5);
  return rand() % 100;
}

void entra_cliente(int nuevo_cliente) {
  printf("Entra cliente %d en %d\n", nuevo_cliente, corte);
  fflush(stdout);
  sillas[corte++] = nuevo_cliente;
}

int sale_cliente() {
  int cliente;
  cliente = sillas[--corte];
  return cliente;
}

void corte_cliente(int cliente) {
  printf(" Barbero cortando %d\n", cliente);
  fflush(stdout);
  sleep(rand() % 2);
}
