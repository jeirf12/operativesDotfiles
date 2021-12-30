#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

sem_t seats;
sem_t seat_barber; 
sem_t barber_cut;
sem_t barber_sleep;
sem_t beard_end[10];
sem_t seats_full;
char remainingChairs = N, sleep_barber = 1;

/**
 * Methods semaphores
 */
void down(sem_t *s);
void up(sem_t *s);

/**
 * Logic bussines
 */
void *barber(void *arg);
void *clients(void *arg);
void arrived_client(int id);
void wakeup_barber(int id);
void sleeping_barber();
void wait_client(int id);
void start_beard_trim(int id);
void end_beard_trim(int id);
