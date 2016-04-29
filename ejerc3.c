#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>


sem_t semaforo;

int count=0;



void* calcular(void *arg) {


	sem_wait(&semaforo);
	count += 1 ;
	sem_post(&semaforo);

	pthread_exit(0);

}




int main(int argc, char** argv) {

	sem_init(&semaforo,0,1);
	pthread_t threads[2];
	long taskids[2];



		
		pthread_create(&threads[0], NULL, calcular, (void*)taskids[0]);
		pthread_create(&threads[1], NULL, calcular, (void*)taskids[1]);
		

	

	for (int i = 0; i < 2; i++){
		pthread_join(threads[i],NULL);
	}


	printf("count =  %d \n",count);

	

	// aqui se destruye el semaforo

	pthread_exit(NULL);
	sem_destroy(&semaforo);


}