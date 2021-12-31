#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define NSI 8 //Define number of seats
#define NCLI 10 //Define number of customers

sem_t seats;
sem_t seat_barber; 
sem_t barber_cut;
sem_t barber_sleep;
char remainingChairs = NSI, sleep_barber = 1;

/**
 * Methods semaphores
 */
void down(sem_t *s);
void up(sem_t *s);

/**
 * Method barber pthread
 */
void *barber(void *arg);

/**
 * Method clients pthread
 */
void *clients(void *arg);

/**
 * When a client arrives, the numbers of chairs decreases
 * and shows the total of them
 */
void arrived_client(int id);

/**
 * Wake up the barber and modified flag sleep_barber
 */
void wakeup_barber(int id);

/**
 * Shows the barber sleeping
 */
void sleeping_barber();

/**
 * Show the client waiting for shift
 */
void wait_client(int id);

/**
 * Initiates the client cut
 */
void start_beard_trim(int id);

/**
 * End customer cut
 */
void end_beard_trim(int id);

/**
 * Shows the number of seats
 */
void seats_counter();
