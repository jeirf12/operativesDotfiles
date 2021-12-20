#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 10

int sillaBarbero;
int sillas[N];
int corte;
sem_t lleno; /* Controla el llenado de sillas */

sem_t barbero; /* Controla el barbero ocupado */ 

sem_t clien;

void * cortando_barbero(void *arg);

void * espera_cliente(void *arg);

void verifica_semaforo(sem_t *cliente);

void verifica_cambio(sem_t *cliente);

int crea_cliente();

void entra_cliente(int nuevo_cliente);

int sale_cliente();

void corte_cliente(int cliente);
