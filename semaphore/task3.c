#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

const size_t ShmemSize = 4096;
const char Message[] = "Hello World!\n";
const char Pathname[] = "task3.c";

typedef union semnum 
{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
} semnum;

int main(void) {
    key_t data_key = ftok(Pathname, 0);
    if (data_key == (key_t)(-1)) {
        perror("Cant ftok for data file\n");
        exit(-1);
    }

	int shm_id = shmget(data_key, ShmemSize, 0600 | IPC_CREAT);
	if (shm_id < 0) 
	{
		perror("Cant get shared memory\n");
        exit(-1);
	}

	int sem_id = semget(data_key, 1, 0600 | IPC_CREAT);
	if (sem_id < 0)
	{
		perror("Cant get semaphore\n");
        exit(-1);
	}

	unsigned short sem_vals = 0;
	if (semctl(sem_id, 0, SETALL, (semnum){.array = &sem_vals}) < 0) {
		perror("semctl error\n");
        exit(-1);
	}

	char* shm_buf = (char*)shmat(shm_id, NULL, 0);
	if (shm_buf == (char*)-1)
	{
		perror("shmat error\n");
		exit(-1);
	}
    
    struct shmid_ds shmem_stat;
	shmctl(shm_id, IPC_STAT, &shmem_stat);
	
	int shm_size = shmem_stat.shm_segsz;
	
	strcpy(shm_buf, Message);

    struct sembuf sem_cmd = {
        .sem_num = 0,
        .sem_flg = SEM_UNDO
    };	

    sem_cmd.sem_op = -1;
	semop(sem_id, &sem_cmd, 1);

	sem_cmd.sem_op = 0;
	semop(sem_id, &sem_cmd, 1);

	semctl(sem_id, 0 , IPC_RMID, NULL); // удаление семафора
	
    shmdt(shm_buf);
	shmctl(shm_id, IPC_RMID, NULL);

	return 0;
}
