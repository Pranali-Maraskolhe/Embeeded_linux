
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

void * thread_task(void * args){
	printf("In child\n");
	sleep(30);
}

int main(){
	pthread_t t_id;
	int ret;
	
	printf("Get process id = %d\n",getpid());
	printf("Before creation of thread\n");

	ret = pthread_create(&t_id,NULL,thread_task,NULL);
	
	if(ret == 0){
		printf("Threads has created successfully\n");
	}
	else{
		printf("Problem in creating thread\n");
	}

	pthread_join(t_id,NULL);
	printf("Threads has been terminated\n");
	return 0;
}


