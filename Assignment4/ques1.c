/*Create 5 children processes from a common parent and ensure that the
parent terminates after cleaning all the terminated children using waitpid().
The waitpid() must be called after all the children are created
and the parent has completed its work real work,if any. You must interpret
the exit code of the cleaned­up processes, using waitpid(), in parent process*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>

int main(){

	int ret;
	int i = 0,status;
	
	//create 5 child using fork system call
//	for(i=0; i<5; i++)
	while(i++<5){

	ret = fork(); // create child for the parent by using fork system call
		
		if(ret < 0){
			printf("No process exceuted\n");
			printf("The final value of i is %d\n",i);
			exit(1);
		}

		if(ret == 0){
			
			printf("\nI am in child process: \n");
			printf("The child %d ppid  is %d and pid is %d \n",i,getppid(),getpid());
			//while(1);
			break;
		}

		if(ret > 0){
			printf("\nI am in parent process: \n");
			printf("My parent ppid is %d  and pid is %d\n",getppid(),getpid());
			continue;

		}
	}


		//wait for the termination of child
		if(ret > 0){
			while(1){
				ret = waitpid(-1,&status,0);
				
				//child process terminated
				if(ret > 0){
				if(WIFEXITED(status)) //check if the process terminated normally
					{
						if(WEXITSTATUS(status) == 1) //print the meaagae that process terminated normally
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

		

	printf("All child process terminated successfully and exit from child process");
	while(1);
	return 0;

}

