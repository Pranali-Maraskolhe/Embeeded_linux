#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SEM_KEY 0x1234
#define SHM_KEY 0x5678

void handleError(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int shmid, semid;
    char *shmaddr;
    char buff[20];

    // Get shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1) handleError("shmget");

    // Attach to shared memory
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) handleError("shmat");

    // Get semaphores
    semid = semget(SEM_KEY, 2, 0666);
    if (semid == -1) handleError("semget");

    // Wait for writer to write data (lock semaphore 1)
    struct sembuf sb = {1, -1, 0};
    semop(semid, &sb, 1);

    // Read data from shared memory
    printf("Data from shared memory: %s\n",shmaddr);

    // Unlock semaphore 0 (writer)
    sb.sem_num = 0;
    sb.sem_op = 1;
    semop(semid, &sb, 1);

    // Clean up
    shmdt(shmaddr);

    return 0;
}

