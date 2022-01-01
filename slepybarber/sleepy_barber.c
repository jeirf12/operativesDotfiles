#include "sleepy_barber.h"

int main(int argc, char *argv[]){
  pthread_t bar_pthread, cli_pthread[NCLI];
  int ids[NCLI];
  int customer_index;
  sem_init(&seats, 0, NSI-1);
  sem_init(&seat_barber, 0, 1);
  sem_init(&barber_cut, 0, 1);
  sem_init(&barber_sleep, 0, 1);
  pthread_create(&bar_pthread, NULL, barber, NULL);
  for(customer_index = 0; customer_index < NCLI; customer_index++){
    ids[customer_index] = customer_index;
    if (NSI > customer_index) {
      pthread_create(&cli_pthread[customer_index], NULL, clients, (void *)&ids[customer_index]);
    } else {
      sleep(NSI + 1);
      if (remainingChairs > 0) {
        up(&seats);
        pthread_create(&cli_pthread[customer_index], NULL, clients, (void *)&ids[customer_index]);
      }else {
        printf("Client %d leaving the barbershop....\n", customer_index);
      }
    }
  }
  pthread_join(bar_pthread, NULL);
  return EXIT_SUCCESS;
}

void *barber(void *arg){
  while (1){
    down(&barber_sleep);
    sleeping_barber();
    seats_counter();
    up(&seats);
  }
}

void *clients(void *arg){
  int id = *(int*)arg;
  down(&seats); // pregunta, hay sillas vacias
  down(&seat_barber); // pregunta si la silla del barbero esta desocupada
  sleep(1);
  arrived_client(id); // si hay sillas vacias, entra el cliente
  if (sleep_barber) wakeup_barber(id);  //si esta durmiendo en la silla, levantelo
  else wait_client(id); //sino esta ocupada la silla barbero con un cliente y tiene que esperar
  up(&seat_barber);
  down(&barber_cut);  // pregunta si esta cortando barba
  sleep(5);
  start_beard_trim(id); //inicia el corte
  sleep(rand() % 10);
  end_beard_trim(id); //termina el corte
  up(&barber_cut);
}

void arrived_client(int id){
  printf("Customer arrived %d\n", id);
  --remainingChairs;
  seats_counter();
}

void wakeup_barber(int id){
  printf("Client %d wake up barber\n", id);
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
  ++remainingChairs;
  seats_counter();
}

void end_beard_trim(int id){
  printf("finished cut %d client\n", id);
}

void seats_counter(){
  printf("Unoccupied chairs: %d\n", remainingChairs);
}

void down(sem_t *s){
  sem_wait(s);
}

void up(sem_t *s){
  sem_post(s);
}
