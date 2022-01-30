#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5                          // Define number of forks and philosoph
#define NEXT (id + 1) % N             // Calculate the following fork
#define PREVIOUS (id + N - 1) % N     // Calculate the previous fork
#define THINKING 0                    // Flag THINKING
#define HUNGRY 1                      // Flag HUNGRY
#define EATING 2                      // Flag EATING

int state[N];                         // Array to keep track of everyone’s state
sem_t philosophers[N];                // Define semaphore for every philosopher
sem_t philosopher_mutex;              // Mutual exclusion for critical regions

/**
 * Methods semaphores
 */
void down(sem_t *s);
void up(sem_t *s);

/**
 * Method philosoph
 */
void *philosopher(void *arg);

/**
 * Init philosopher thinking
 */
void philosopher_thinking(int id);

/**
 * Show philosopher hungry
 */
void philosopher_hungry(int id);

/**
 * show philosopher eating
 */
void philosopher_eating(int id);

/**
 * Philosopher take the cutlery and controls
 * the critical section, where the blockage occurs or 
 * sarvation
 */
void take_forks(int id);

/**
 * Philosopher puts the cutlery and the blockage ends
 * for sarvation
 */
void put_forks(int id);

/**
 * Control the hungry state of each philosopher
 */
void verified_forks(int id);
