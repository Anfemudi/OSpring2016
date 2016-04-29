#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>
#define MAXTHREAD 50


sem_t semaforo;

int count=0;

int n=2;


int espera(int delay) {
	int r;
	srand(time(NULL));
	r=rand()%delay;
	usleep(r*1000);
	return r;
}


void* calcular(void *arg) {

	long id = (long) arg;


	sem_wait(&semaforo);

	count += 1 ;
	printf ("entro el hilo %ld \n",id);
	espera(500);
	printf ("salio el hilo %ld \n",id);
	sem_post(&semaforo);


	pthread_exit(0);

}




int main(int argc, char** argv) {

	sem_init(&semaforo,0,n);
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];



		for (int i = 0; i < MAXTHREAD; i++){
			taskids[i]=i;
		pthread_create(&threads[i], NULL, calcular, (void*)taskids[i]);
			
	}

		
		
		

	

	for (int i = 0; i < MAXTHREAD; i++){
		pthread_join(threads[i],NULL);
	}

	

	// aqui se destruye el semaforo

	pthread_exit(NULL);
	sem_destroy(&semaforo);


}