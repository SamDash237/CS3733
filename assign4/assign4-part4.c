#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int nthreads;
pthread_mutex_t chopsticks[5];

void thinking(int threadIndex) {
  	int rand_num = rand() % 500 + 1;
	int sleep_time = rand_num % nthreads;
	printf("Philosopher %d thinks for %d seconds\n", threadIndex, sleep_time);
	sleep(sleep_time);
}

void pickUpChopsticks(int threadIndex) {
  int rc1,rc2;

	int left = (threadIndex + nthreads) % nthreads;
	int right = (threadIndex + 1) % nthreads;
	if (threadIndex & 1) {
    while (pthread_mutex_trylock(&chopsticks[right]) != 0){
    }
		while (pthread_mutex_trylock(&chopsticks[left]) != 0) {
    }
		printf("Philosopher %d has picked up chopsticks\n", threadIndex);
	}      
	else {
		while (pthread_mutex_trylock(&chopsticks[left]) != 0) {
    }   
		while (pthread_mutex_trylock(&chopsticks[right]) != 0) {
    }   
		printf("Philosopher %d has picked up chopsticks\n", threadIndex);
	}
}

void eating(int threadIndex) {
  	int rand_num = rand() % 500 + 1;
	int sleep_time = rand_num % nthreads;
	printf("Philosopher %d eats for %d seconds\n", threadIndex, sleep_time);
	sleep(sleep_time);
}

void putDownChopsticks(int threadIndex) {
	printf("Philosopher %d has finished eating\n", threadIndex);
	pthread_mutex_unlock(&chopsticks[(threadIndex + 1) % nthreads]);
	pthread_mutex_unlock(&chopsticks[(threadIndex + nthreads) % nthreads]); 
	pthread_exit(NULL);
}

void *func(void *threadIndex) {
	int ti = (int)threadIndex;
        thinking(ti);
	pickUpChopsticks(ti);
	eating(ti);
	putDownChopsticks(ti);
	return;
}

int main(int argc, char *argv[]) {

  srand(time(NULL));
	nthreads = atoi(argv[1]);
	pthread_t tid[nthreads];

	if(argc != 2) {
    	printf("Please indicate number of threads to be created!\n");
    	exit (1); 
  	}
  
  	printf("Sam Dash\nAssignment 4: # of threads = %d\n", nthreads);

	int i;
	for (i = 1; i <= nthreads; i++) {
		pthread_mutex_init(&chopsticks[i], NULL);
	}
	
	for (i = 1; i <= nthreads; i++) {
		pthread_create(&tid[i], NULL, (void *)func, (void *)i);
	}
	
	for (i = 1; i <= nthreads; i++) {
		pthread_join(tid[i], NULL);
	}

	for (i = 1; i <= nthreads; i++)
       {
          pthread_mutex_destroy(&chopsticks[i]);
       }

	return 0;
}