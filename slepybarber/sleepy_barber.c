#include "sleepy_barber.h"

int main(int argc, char *argv[]){
  pthread_t bar_pthread, cli_pthread[N];
  int ids[N];
  int customer_index;
  sem_init(&seats, 0, N);
  sem_init(&seat_barber, 0, 1);
  sem_init(&barber_cut, 0, 1);
  sem_init(&barber_sleep, 0, 1);
  for (customer_index = 0; customer_index < N; customer_index++) {
    sem_init(&beard_end[customer_index], 0, 0);
  }
  pthread_create(&bar_pthread, NULL, barber, NULL);
  for(customer_index = 0; customer_index < N; customer_index++){
    ids[customer_index] = customer_index;
    pthread_create(&cli_pthread[customer_index], NULL, clients, (void *)&ids[customer_index]);
  }
  pthread_join(bar_pthread, NULL);
  return EXIT_SUCCESS;
}

void *barber(void *arg){
  while (1) {
    down(&barber_sleep);
    sleeping_barber();
  }
}

void *clients(void *arg){
  int id = *(int*)arg;
  down(&seats); // pregunta, hay sillas vacias
  arrived_client(id); // si hay sillas vacias, entra el cliente
  down(&seat_barber); // pregunta si la silla del barbero esta desocupada
  if (sleep_barber) {
    wakeup_barber(id);  //si esta durmiendo en la silla, levantelo
  }else {
    wait_client(id); //sino esta ocupada con un cliente y tiene que esperar
  }
  up(&seat_barber);
  down(&barber_cut);  // pregunta si esta cortando barba
  sleep(rand() % 2);
  start_beard_trim(id); //inicia el corte
  sleep(rand() % 2);
  end_beard_trim(id); //termina el corte
  up(&barber_cut);
}

void arrived_client(int id){
  printf("Customer arrived %d\n",id);
}

void wakeup_barber(int id){
  printf("client %d wake up barber\n", id);
  sleep_barber = 0;
}

void sleeping_barber(){
  printf("Barber sleeping.....\n");
}

void wait_client(int id){
  printf("Wait client %d to barber....\n", id);
}

void start_beard_trim(int id){
  printf("Beard trim cliente %d \n", id);
}

void end_beard_trim(int id){
  printf("finished cut %d client\n", id);
}

void down(sem_t *s){
  sem_wait(s);
}

void up(sem_t *s){
  sem_post(s);
}
