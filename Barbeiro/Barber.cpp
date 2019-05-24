#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define CHAIR 5
#define TRUE 1

sem_t customers;
sem_t barbers;

//Semaforo para acessar variavel waiting
sem_t mutex;

//Quantidade de clientes esperando
int waiting = 0;

void* barber(void* arg);
void* customer(void* arg);
void cut_hair();
void customer_arrived();
void get_haircut();
void giveup_haircut();


int main(){
	sem_init(&customers, TRUE, 0);
	sem_init(&barbers, TRUE, 0);
	sem_init(&mutex, TRUE, 1);

	pthread_t b, c;

	pthread_create(&b, NULL, barber, NULL);

	while(TRUE){
		pthread_create(&c, NULL, customer, NULL);
		sleep(1);
	}
	return 0;
}

void* barber(void* arg){
	while(TRUE){
		//Se não houver clientes, o barbeiro dorme, sendo acordado somente quando chegam clientes
		sem_wait(&customers);
		sem_wait(&mutex);
		waiting--;
		sem_post(&barbers);
		sem_post(&mutex);
		cut_hair();
	}
	pthread_exit(NULL);
}

void* customer(void* arg){
	sem_wait(&mutex);
	if(waiting < CHAIR){
		customer_arrived();
		waiting++;
		sem_post(&customers);
		sem_post(&mutex);
		sem_wait(&barbers);
		get_haircut();
	}else{
		sem_post(&mutex);
		giveup_haircut();
	}
	pthread_exit(NULL);
}

void cut_hair(){
	printf("Barber is cutting someone hair\n");
	sleep(3);
}

void customer_arrived(){
	printf("Client arrived\n");
}
void get_haircut(){
	printf("Client is getting his hair cut\n");
}

void giveup_haircut(){
	printf("Client give up, the room is full\n");

}