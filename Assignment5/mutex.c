#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex;

void* routine() {

	for(int i=0; i<1000000; i++){
		
		pthread_mutex_lock(&mutex); //perform both operation of waiting and locking
		count++;
		pthread_mutex_unlock(&mutex); //unlock

		//Without pthread_mutex system any thread will be exceuting and 
		//the result will unconsistence

	}
}

int main() {
	
	pthread_t p1, p2;

	pthread_mutex_init(&mutex, NULL); //initialize mutex
	
	//create thread
	if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
		return 1;
	}

	if(pthread_create(&p2, NULL, &routine, NULL) != 0){
		return 2;
	}
	
	//join thread
	if (pthread_join(p1, NULL) != 0){
		return 3;
	}

	if (pthread_join(p2, NULL) != 0){
		return 3;
	}

	pthread_mutex_destroy(&mutex);//destory the mutex
	printf("Number of counts: %d\n",count);
	return 0;
}
