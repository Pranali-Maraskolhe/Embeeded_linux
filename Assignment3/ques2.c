/*Create a number of threads (Lets say n), try joining them and run the process. Run ps command and
note down your observations.*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define max 5


void * thread_task(void * args){
        printf("In thread : %s\n",(char *)args);
	//sleep(3);
	//while(1);
	pthread_exit(NULL);
}

int main(){
        pthread_t t_id[max];
        int ret;
        int n;

        printf("The process id: %d\n",getpid());

        printf("Before creation of thread\n");

        printf("Enter number of threads : ");
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
        }

        for(int i=0; i<n; i++){
                printf("thread %d\n", i+1);

                        printf("join the thread %d \n",i+1);
                        ret= pthread_join(t_id[i],NULL); //join multiple threads
                        if(ret){
                                printf("unable to join threads %d\n",ret);
                                exit(1);
                        }
                        else{
                                printf("Thread %d has terminated\n",i+1);
                        }
                        printf("Thread %d executed successfully",i+1);


	}

	//while(1);


        return 0;
}


