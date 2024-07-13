#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define THREAD_NUM 4

pthread_mutex_t mutexFuel;

int fuel = 50;

void* routine(){
	
	pthread_mutex_lock(&mutexFuel);
	fuel += 50;
	printf("Current value is %d\n",fuel);
	pthread_mutex_unlock(&mutexFuel);

}


int main(){
	
	pthread_t th[THREAD_NUM];
	pthread_mutex_init(&mutexFuel, NULL);
	int i;

	for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			perror("Fail to create thread");
		}
	}

	for(int i=0; i<THREAD_NUM; i++){
		if(pthread_join(th[i], NULL) != 0) {
			perror("Error at joining the thread");
		}
	}

	pthread_mutex_destroy(&mutexFuel);

	return 0;
}
