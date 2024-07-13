/*Write a code for implementation of the following and build the code for Raspberry Pi using cross compiler setup : 
Create 3 child processes from a common parent using fork() system call and assign multiple tasks to them usin exec() system call.
Schedule them on different cores of CPU using sched_getaffinity() and sched_setaffinity() system calls (refer man page) and observe the working on your Raspberry pi’s terminal using top/htop command.
After completion of their tasks terminate the child processes and wait them by their parent using wait() system call.*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <sched.h>
#include <errno.h>
#include <string.h>



// Function to fetch the number of CPU cores available
int get_cpu_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

// Function to set CPU affinity for a process
void set_cpu_affinity(pid_t pid, int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    if (sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset) == -1) {
        fprintf(stderr, "Error setting CPU affinity: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}


int main(){

	int ret;
	int i = 0,status;
	
	int num_cores = get_cpu_cores();
	printf("Number of cpu available: %d\n", num_cores);

	if(num_cores < 2){
		fprintf(stderr, "At least 3 CPU cores are required for this program \n");
		exit(EXIT_FAILURE);
	}

	//create 3 child using fork system call
//	for(i=0; i<3; i++)
	while(i<4){

	ret = fork(); // create child for the parent by using fork system call

		if(ret < 0){
			printf("No process exceuted\n");
			printf("The final value of i is %d\n",i);
			exit(1);
		}

		if(ret > 0){
			set_cpu_affinity(getpid(), i);
			printf("\nI am in parent process: \n");
			printf("My parent ppid is %d  and pid is %d\n",getppid(),getpid());
		//	continue;
		//	exit(1);
		}

		if(ret == 0)
		{
			set_cpu_affinity(getpid(), i);
			printf("\nI am in child process: \n");
			printf("The child %d ppid  is %d and pid is %d \n",i,getppid(),getpid());
			if(i == 0){
				//printf("i = %d\n",i);
				//execl is used to launch any process and remove the current proces
				//Launch the pdf reader
				printf("************ PDF Viewer *******************\n");
				execl("/usr/bin/evince","evince","BL_Fellowship Selection_PracticeProblems -V01.pdf",NULL);
			}

			else if(i == 1){
				//printf("i = %d\n",i);
				//Launch ques1.c file
				printf("************GCC 1 *******************\n");
				execl("/usr/bin/gcc","gcc","ques1.c","-o","ques1",NULL);
			}

			else if(i == 2){
				//Launch ques2.c file
				printf("************GCC 2 *******************\n");
				execl("/usr/bin/gcc","gcc","ques1.c","-o","q2",NULL);
			}

			else if(i == 3) {
				//Launch hello.txt file
				printf("************ VIM Editor *******************\n");
				execl("/usr/bin/vim","vim","hello.txt",NULL);
			}

			else
			{
				//break;
			}

			//break;
		}


		i++;
	}

	//wait for the termination of child
		if(ret > 0){
			for(i = 0; i < num_cores; i++){
				ret = waitpid(-1,&status,0);

				//child process terminated
				if(ret > 0){
					if(WIFEXITED(status)) //check if the process terminated normally
					{

						if(WIFEXITED(status) == 0)
						{
							printf("normal and successful termination of %d\n", ret);
						}
						else{
							printf("Normal and unsuccessful of pid %d\n",ret);
						}
					}

					else{
						printf("Abnormal and unsuccessful pid %d\n", ret);
					}
				}

				if(ret < 0){

					exit(0);
				}
			}
		}



	printf("All child process terminated successfully and exit from child process\n");
	


	while(1);
	return 0;

}
