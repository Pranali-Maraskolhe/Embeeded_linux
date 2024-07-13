#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4


sem_t semFuel;

int *fuel;

void* routine(){
	

	//sem_wait(&semFuel);
	*fuel += 50;
	printf("Current value is %d\n", *fuel);
	sem_post(&semFuel);	//increment the value

}


int main(){
	
	pthread_t th[THREAD_NUM];
	fuel = malloc(sizeof(int)); //dymanically allocate the memory
	*fuel = 50; //deferencing the value

	sem_init(&semFuel, 0, 0);	//initialize the semaphore
	int i;
	
	//creating the thread
	for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			perror("Fail to create thread");
		}
	}

	sem_wait(&semFuel);	//waiting for a process to complete it's exceution
	printf("Deallocating Fuel\n"); //Deallocate the memory
	free(fuel); //Free the use memory
		    

	//join the threads
	for(int i=0; i<THREAD_NUM; i++){
		if(pthread_join(th[i], NULL) != 0) {
			perror("Error at joining the thread");
		}
	}
	

	sem_destroy(&semFuel);	//destory the semaphore

	return 0;
}
