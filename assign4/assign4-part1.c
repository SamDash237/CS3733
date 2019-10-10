#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int nthreads;

void creatPhilosophers(int nthreads){
  printf("%d threads have been completed successfully!\n",nthreads);
  }

void *philosopherThread(void *pVoid){

  int id = *(int *) pVoid; 

  printf("This is philosopher %d\n", id);
  pthread_exit(NULL);
  }

int main(int argc, char *argv[]) {

  int nthreads = atoi(argv[1]);
  int tArr[nthreads];
  pthread_t tid[nthreads];
  int i;
    
  if(argc != 2) {
    printf("Please indicate number of threads to be created!\n");
    exit (1); 
  }
  
  printf("Sam Dash\nAssignment 4: # of threads = %d\n", nthreads);
  
  for(i = 0; i <= nthreads; i++){
  tArr[i] = i; 
  if(pthread_create(&tid[i], NULL, philosopherThread, (void *) &tArr[i]) != 0) {
    printf("pthread_create failed with i = %d\n",i);
    nthreads = i;
    break;
    } 
  }
  for(i=0; i <= nthreads; ++i) {
      pthread_join(tid[i], NULL);
    }
  creatPhilosophers(nthreads);
  return(0);
}
