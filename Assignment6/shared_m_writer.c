#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024
#define SEM_KEY 0x1234
#define SHM_KEY 0x5678


void handleError(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(){
	int shmid, semid;
	char *shmaddr;
	char buff[20];

	//create shared memory
	shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);

	if(shmid == -1){
		handleError("shmget");
	}

	//Attached to shared memory
	shmaddr = shmat(shmid, NULL, 0);

	if(shmaddr == (char *)-1){
		handleError("shmat");
	}

	//Create semaphores
	semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);

	if(semid == -1){
		handleError("semget");
	}

	//Initialize semaphores
	semctl(semid, 0, SETVAL, 1);	//writer semaphore
	semctl(semid, 1, SETVAL, 0);	//reader semaphore

	//Lock semaphore 0 (writer)
	struct sembuf sb = {0, -1, 0};
	semop(semid,&sb,1);

	//write data to shared memory
	
	//printf("Enter data to print\n");
	//fgets(buff,20,stdin);
	snprintf(shmaddr, SHM_SIZE, "Hello from writer process %d", getpid());
	//read(0,buff,strlen(buff));
	//strcpy(shmaddr,buff);


	//Unlock semaphore 1 (reader)
	sb.sem_num = 1;
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	//Wait for reader to read data
	sb.sem_num = 0;
	sb.sem_op = -1;
	semop(semid, &sb, 1);


	//Clean up
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID, 0);

	return 0;
}
