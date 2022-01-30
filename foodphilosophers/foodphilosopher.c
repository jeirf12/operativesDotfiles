#include "foodphilosopher.h"

int main(int argc, char *argv[]){
  pthread_t phi_pthread[N];
  int ids[N];
  int philosopher_index;
  
  sem_init(&philosopher_mutex, 0, 1);

  for (philosopher_index = 0; philosopher_index < N; philosopher_index++) {
    sem_init(&philosophers[philosopher_index], 0, 0);
    ids[philosopher_index] = philosopher_index;
    pthread_create(&phi_pthread[philosopher_index], NULL, philosopher, (void *)&ids[philosopher_index]);
  }

  for (philosopher_index = 0; philosopher_index < N; philosopher_index++) {
    pthread_join(phi_pthread[philosopher_index], NULL);
  }

  return EXIT_SUCCESS;
}

void up(sem_t *s){
  sem_post(s);
}

void down(sem_t *s){
  sem_wait(s);
}

void philosopher_eating(int id){
  printf("\tPhilosopher %d is eating.\n", id);
}

void philosopher_thinking(int id){
  printf("Philosopher %d is thinking...\n", id);
}

void philosopher_hungry(int id){
  printf("Philosopher %d is hungry!\n", id);
}

void take_forks(int id){
  down(&philosopher_mutex);
  state[id] = HUNGRY;
  verified_forks(id);
  up(&philosopher_mutex);
  down(&philosophers[id]);
  printf("\tPhilosopher %d has acquired the cutlery!\n", id);
}

void put_forks(int id){
  down(&philosopher_mutex);
  state[id] = THINKING;
  printf("\tPhilosopher %d has just left the cutlery...\n", id);
  verified_forks(PREVIOUS);
  verified_forks(NEXT);
  verified_forks(id);
  up(&philosopher_mutex);
}

void verified_forks(int id){
  if (state[id] == HUNGRY && state[PREVIOUS] != EATING && state[NEXT] != EATING) {
    state[id] = EATING;
    up(&philosophers[id]);
  }
}

void *philosopher(void *arg){
  int id = *(int*)arg;
  philosopher_thinking(id);
  sleep(rand()%3); 
  philosopher_hungry(id);
  take_forks(id);
  philosopher_eating(id);
  sleep(rand()%5);
  put_forks(id);
  philosopher_thinking(id);
  sleep(rand()%3); 
}
