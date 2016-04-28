#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>


sem_t semaforo;

void printearA(){


	printf("Quiere  A%s\n");
}


void printearB(){


	printf("Quiere  B%s\n");
}





int main(int argc, char** argv) {

	sem_init(&semaforo,0,1);
	pthread_t threads[2];
	long taskids[2];

	for (int i = 0; i < 2; i++) {
		taskids[i] = i;


		
		pthread_create(&threads[i], NULL, printearA, (void*)taskids[i]);
		sem_post(&semaforo);
		sem_wait(&semaforo);
		pthread_create(&threads[i], NULL, printearB, (void*)taskids[i]);

	}

	for (int i = 0; i < 2; i++){
		pthread_join(threads[i],NULL);
	}

	

	// aqui se destruye el semaforo

	pthread_exit(NULL);
	sem_destroy(&semaforo);


}