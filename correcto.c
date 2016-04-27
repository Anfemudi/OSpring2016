#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 100000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE;
double numRectxThread = (double)(MAXRECT/MAXTHREAD);
double base_length = 0;
double sumTotal = 0;
double partialSums[MAXTHREAD];

double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	long id = (long) arg;
	double lowlimit = id*base_length*numRectxThread;

	double sum = 0;

	for (int i = 0; i < numRectxThread; i++) {
		sum += function(lowlimit + i*base_length) * base_length;
	}
	partialSums[id] = sum;
	printf("sum: %lf\n", sum);
	return 0;
}

int main(int argc, char** argv) {
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];

	base_length = length/MAXRECT;
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		partialSums[i] = 0;
		pthread_create(&threads[i], NULL, calcular, (void*)taskids[i]);
	}
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(threads[i], NULL);
		sumTotal += partialSums[i];
	}
	printf("Suma total %lf\n",sumTotal);
	pthread_exit(NULL);
}

