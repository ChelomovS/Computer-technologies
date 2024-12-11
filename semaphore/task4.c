#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>


const size_t ShmemSize = 4096;
const char Pathname[] = "task4.c ";

int main (const int argc, const char* argv[]) {
    key_t data_key = ftok(Pathname, 0);
    if (data_key == (key_t)(-1)) {
        perror("Error ftok for pathname file");
        exit(-1);
    }

    int shm_id = shmget(data_key, ShmemSize, 0600);
	if (shm_id == -1) {
		perror("shmget error\n");
        exit(-1);
	}
	
	int sem_id = semget(data_key, 1, 0600);
	if (sem_id == -1) {
		perror("semget error\n");
        exit(-1);
	}

    char* shm_buf = (char*)shmat(shm_id, NULL, 0);
	if (shm_buf == (char *) -1) {
		perror("shmat error\n");
        exit(-1);
	}

	printf("Message: %s\n", shm_buf);

	int semop_res = semop(sem_id, &(struct sembuf){.sem_num = 0, .sem_op = 1, .sem_flg = SEM_UNDO}, 1);
	if (semop_res < 0) {
        perror("Cant sub 1, semaphore error\n");
    }

	shmdt (shm_buf);

	return 0;
}