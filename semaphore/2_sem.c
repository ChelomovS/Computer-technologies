#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

int main(int argc, char *argv[], char *envp[])
{
    int   semid;
    char  pathname[]= "2_sem.c";
    key_t key;
    struct sembuf mybuf; // структура для операций над семафорос
    
    key = ftok(pathname, 0); // генерация IPC ключа
    
    // создаем семафор или получаем его id
    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }
    
    mybuf.sem_num = 0; // номер семафора в наборе 
    mybuf.sem_op  = 1; // операция - увеличение семафора на 1
    mybuf.sem_flg = 0;
    // выполнение операции над семафором 
    if(semop(semid, &mybuf, 1) < 0)
    {
        printf("Can\'t add 1 to semaphore\n");
        exit(-1);
    }  
        
    printf("The condition is present\n");
    return 0;
}
