/*Using Threading system calls, create a no. Of threads in a process. Launch the process in background
and run ps -eLf command. Observe whether the threads are created successfully.
Write your observations.*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define max 5

void * thread_task(void * args){
	printf("In thread : %s\n",(char *)args);
	sleep(3);
	while(1);
}

int main(){
	pthread_t t_id[max];
	int ret;
	int n;

	printf("The process id: %d\n",getpid());

	printf("Before creation of thread\n");

	printf("Enter number of threads : \n");
	scanf("%d",&n);

	for(int i=0; i<n; i++){
		printf("Creating thread %d\n", i+1);
		ret = pthread_create(&t_id[i],NULL,thread_task,(void *)"hello"); //create threads

		if(ret == 0){
			printf("Thread %d has created successfully\n",i+1);
		}
		else{
			printf("Problem in creating thread\n");
		}
		printf("Thread %d executed successfully\n",i);
	}

	while(1);
	pthread_exit(NULL);

return 0;
}





