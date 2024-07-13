/*Write a code for implementation of the following and build the code for Raspberry Pi using cross compiler setup : 
Create threads
Schedule them on different cores of CPU using pthread_setaffinity_np() and pthread_getaffinity_np() system calls (refer man page) and observe the working on your Raspberry pi’s terminal using top/htop command.
Joining the threads
Detaching the threads and terminate all the threads after completion of tasks.*/



#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#define max 5

void* thread_function(void* arg) {
    int core_id = *(int*)arg;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t thread = pthread_self();
    int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        perror("pthread_setaffinity_np");
    }

    // Confirm CPU affinity setting
    CPU_ZERO(&cpuset);
    s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        perror("pthread_getaffinity_np");
    }

    if (CPU_ISSET(core_id, &cpuset)) {
        printf("Thread %d is running on CPU %d\n", core_id, core_id);
    } else {
        printf("Thread %d is not running on the expected CPU %d\n", core_id, core_id);
    }

    // Simulate work
    for (int i = 0; i < 1000000000; i++);
    while(1);
    return NULL;
}

/*void * thread_task(void * args){
        printf("In child\n");
        //sleep(30);
}*/

int main(){
        pthread_t t_id[max];
        int core_ids[max];
        int ret;
        int n;

        printf("The process id: %d\n",getpid());

        //printf("Before creation of thread\n");

        printf("Enter number of threads : ");
        scanf("%d",&n);
        
        if(n > max){
        	printf("Number of threads exceeds the limits of %d\n", max);
        	return 1;
        }

        for(int i=0; i<n; i++){
        	core_ids[i] = i % sysconf(_SC_NPROCESSORS_ONLN);
                printf("Creating thread %d on core %d\n", i+1,core_ids[i]);
                ret = pthread_create(&t_id[i],NULL,thread_function, &core_ids[i]); //create threads

                if(ret == 0){
                        printf("Thread %d has created successfully\n",i+1);
                }
                else{
                        printf("Problem in creating thread\n");
                }
        }

        for(int i=0; i<n; i++){
                	printf("thread %d\n", i+1);

                       if(i==0){
			       printf("join the thread %d \n",i+1);
                        	ret= pthread_join(t_id[i],NULL);
                        	if(ret){
                                	printf("unable to join threads %d: %d\n",i+1,ret);
                                	exit(1);
                        	}
                       		 else{
                                	printf("Thread %d has terminated\n",i+1);
                        	}
			}

		       else{

                      		 printf("Detaching thread %d\n", i+1);
		      		 ret = pthread_detach(t_id[i]);
		      		 if (ret) {
					printf("Error: unable to detach thread %d:%d\n",i+1, ret);
					exit(EXIT_FAILURE);
			    }

		}
	   

		/*printf("thread %d\n", i+1);

                        printf("join the thread %d \n",i+1);
                        ret= pthread_join(t_id[i],NULL);
                        if(ret){
                                printf("unable to join threads %d: %d\n",i+1,ret);
                                exit(1);
                        }
                        else{
                                printf("Thread %d has terminated\n",i+1);
                        }

                       printf("Detaching thread %d\n", i+1);
		       ret = pthread_detach(t_id[i]);
		       if (ret) {
				printf("Error: unable to detach thread %d:%d\n",i+1, ret);
				exit(EXIT_FAILURE);
			    }*/

	printf("Thread %d executed successfully\n", i+1);
}	


	printf("Threads has been joined, and other threads have been detached\n");
	pthread_exit(NULL);

	while(1);
        return 0;
}
