/*Create a 5 child process from a common parent and launch different
applications from the children processes ­ you may launch pdf viewer,
kwrite, gcc, and w1(based on while1.c) ­ parent process must use waitpid()
to collect the termination status of the child process ­ waitpid()
must be called after all the children are created and the parent has
completed its work real work,if any. You must interpret the exit code of the
cleaned­up processes, using waitpid(), in the parent process
– you must cover all the possible scenarios ­
meaning, terminate the children processes normally(successful/
unsuccessful) or abnormally !!!*/

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
	while(i<5){

	ret = fork(); // create child for the parent by using fork system call

		if(ret < 0){
			printf("No process exceuted\n");
			printf("The final value of i is %d\n",i);
			exit(1);
		}
		
		if(ret > 0){
			printf("\nI am in parent process: \n");
			printf("My parent ppid is %d  and pid is %d\n",getppid(),getpid());
		//	continue;
		//	exit(1);
		}
		
		if(ret == 0)
		{
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
				execl("/usr/bin/gcc","gcc","ques2.c","-o","q2",NULL);	
			}

			else if(i == 3) {
				//Launch hello.txt file
				printf("************ VIM Editor *******************\n");
				execl("/usr/bin/vim","vim","hello.txt",NULL);
			}

			else if(i == 4){
				printf("************ LS -a *******************\n");
				execl("/usr/bin/ls","ls","-a",NULL);
			}

			else
			{
				break;
			}
		
			//break;
		}


		i++;	
	}

	//wait for the termination of child
		if(ret > 0){
			for(i = 0; i < 5; i++){
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
//	while(1);
	return 0;

}

