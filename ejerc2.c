#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>


sem_t semaforo;
sem_t semaforo1;

void* printearA(void *arg){


	
	printf("Quiere  A\n");
	sem_post(&semaforo1);

 	 
	sem_wait(&semaforo);
	printf("Quiere  A2 \n");


}


void* printearB(void *arg){

	printf("Quiere  B\n");
	sem_post(&semaforo);


	sem_wait(&semaforo1);
	printf("Quiere  B2\n");
}





int main(int argc, char** argv) {

	sem_init(&semaforo,0,0);
	sem_init(&semaforo1,0,0);
	pthread_t threads[2];
	long taskids[2];



		
		pthread_create(&threads[0], NULL, printearA, (void*)taskids[0]);
		pthread_create(&threads[1], NULL, printearB, (void*)taskids[1]);

	

	for (int i = 0; i < 2; i++){
		pthread_join(threads[i],NULL);
	}

	

	// aqui se destruye el semaforo

	pthread_exit(NULL);
	sem_destroy(&semaforo);


}