#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{

   int ret,pid,status,flag_unsuccessful=0,flag_abnormal=0;
   unsigned long int i=0;
//is this i variable on the stack or data segment ??
//---->stack segment
//
//on the stack of which process, since this program and
//main() will be part of a parent process and 5 children
//processes - some more children processes may also be 
//created and managed ??
//this stack variable is set-up, in the parent and 
//duplicated, for every child , when stack segment 
//is duplicated
//
//so, this i /its value will be propagated to children
//processes - follow the code and concurrent executions??
//

    pid=getpid();
    printf("processid  = %d\n",pid);

 //in the parent process block, create multiple children
//processes, for different jobs - each child process will
//be assigned different job
//
//there is only one active application
//
//in this active application, there will be several processes
//- each process will do a part of the application's job 
//  
//in these samples, one active application instance
//is managed using multiple processes - 
//meaning, multiple processes are 
//used to implement multitasking, in a given active
//application instance  
//- in this context, each new child process is used to 
//do a specific job, for an active instance of
//the  application 
//block1 

  while(i++<5){
   ret = fork();
   
   if(ret<0)
   { 
           perror("error in fork"); 
           printf("the final value of i is %lu\n", i);
           exit(1); 
   }

   if(ret>0)
   { 
	   printf("I am in parent process context\n"); 
           printf("in parent .. ppid is %lu...and child is %lu\n\n", 
		   getppid(),getpid());
           continue;
   }   
   //this is a child process context and a code block
   //executed, in a each child context 
   if(ret==0) //in a child process context/instance 
   { 
	   printf("I am in child process context\n"); 
        	   
	if(i==1)//first child process context/instance 
                //block2
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
        ret = execl("/usr/bin/gcc","gcc","-c","a1.c","-o","a1.o",NULL);  
        if(ret==-1) { perror("error in execl"); exit(33); }       
       //??if the above execl() executes successfully, what will happen
       //    to the code, after execl(), in the first child's execution context ?? 
        //some more examples of execl()
        //
	}//block2 ends here 

        //this is the second instance of the child process
        //it is assigned another job, using execl() 
        //gcc is used to compile another object file 	
	if(i==2) //block3
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
        ret = execl("/usr/bin/gcc","gcc","-c","a2.c","-o","a2.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }       
	}//block3 ends here
	if(i==3)//block4
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
	   
        ret = execl("/usr/bin/gcc","gcc","-c","a3.c","-o", "a3.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }     
	}//block4 ends here 
	if(i==4)//block5 
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
	   
	ret = execl("/usr/bin/gcc","gcc","-c","a4.c","-o","a4.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }       
	}//block5 ends here 
	if(i==5)//block6
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
	   
	ret = execl("/usr/bin/gcc","gcc","-c","a5.c","-o","a5.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }      
	}//block6 ends here 
   }
  } //while loop ends here 




 //block7 - this block will be executed, by the parent 
 //         process 
 if(ret>0) //this block of code will execute, 
           //in the parent's context only 
 {
 
 pause();

   while(1)
   {
     ret = waitpid(-1,&status,0);
     if(ret>0) //in this context, a child has been cleaned-up 
     {
            printf("child with id %d terminated\n",ret);
       if(WIFEXITED(status))  
       {
            printf("wifexited\n");
           if(WEXITSTATUS(status) == 0)
           { 
              printf("wexitstatus\n");       
           }
           else  //this condition is, when the child process terminated 
           {
               flag_unsuccessful = 1;
               printf("unsuccessful\n");
           }
       }
       else //this block will execute, when the child process terminated 
            //abnormally / was a forced termination
       {
           // signal = WTERMSIG(status);
            flag_abnormal = 1;
       }
     }
     if(ret<0)
     {   
        //the parent process terminates, unsuccessfully ??? 
        if(flag_unsuccessful || flag_abnormal) 
          {
           printf("error in compiling an object file\n"); 
           exit(1); } //applicationi terminates, with error

        else break; //if all the children processes have 
     }
   }//second while
  }//second parent block if


  //only parent processi will reach this stage of code
  //children processes will never reach this stage 
  //of code 
  //
  //
  //if our children processes complete their jobs successfully, 
  //the parent process continues to do more jobs, for
  //this applicationi 

   ret = fork(); //the parent creates another child process, for 
                 //linking the object files and generating a 
                 //final binary ???
   
   if(ret<0)
   { 
           perror("error in fork"); 
           printf("the final value of i is %lu\n", i);
           exit(1); 
   }
   if(ret>0)
   { 
	   printf("I am in parent process context\n"); 
           printf("in parent .. ppid is %lu...and child is %lu\n\n", getppid(),getpid());
   }

   if(ret==0) 
   { 
	   printf("I am in    COMBINING     child process context\n"); 
           printf("in child .. ppid is %lu ...and pid is %lu\n",getppid(),getpid());           	   
       
        //there is one more child process created, in this applicationi
        //what is the job of this child process ??
        //
	ret = execl("/usr/bin/gcc","gcc","a5.o","a4.o",
                        "a3.o","a2.o","a1.o","-o", "final",NULL);  
  	   if(ret<0) { perror("error in execl"); exit(33); }      
   }

 flag_unsuccessful = 0;
 flag_abnormal =0; 

 //again, waitpid() is used to clean-up a child process and 
 //check the termination status code/exit code, for the application 
 if(ret>0)
 {
   while(1)
   {

     ret = waitpid(-1,&status,0);
     if(ret>0)
     {
            printf("child with id %d terminated\n",ret);

       if(WIFEXITED(status))
       {
            printf("wifexited\n");
           if(WEXITSTATUS(status) == 0)
           { 
              printf("wexitstatus\n");       
           }
           else
           {
               flag_unsuccessful = 1;
               printf("unsuccessful\n");
           }
       }
       else
       {
	      if(flag_unsuccessful || flag_abnormal) {printf("error in compiling an object file\n"); exit(1); }
              flag_abnormal = 1;
       }
     }

     if(ret<0)
     {   
        break;  //you must check conditions properly - this code is incomplete ??  
     }

   }//second while

  }//second parent block if 



 //you must verify that the linking child process completed 
 //successfully and then go far loading/launching 
 //the compiled new program
   
 //once the above jobs are done, with the help of children processes, 
 //one more child process is created, for loading/launching the 
 //new compiled/linked binary file 

 //return 0; //equivalent to exit(0);

 exit(0);
   
}


