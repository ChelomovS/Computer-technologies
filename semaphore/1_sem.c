#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

// Написать комментарии, отладить работу
int main(int argc, char *argv[], char *envp[])
{
    int   semid;
    char  pathname[]= "1_sem.c"; // путь к файлу для генерации ключа 
    key_t key;
    struct sembuf mybuf; // структура для семафора
    
    key = ftok(pathname, 0); // генерируем ключ для семафора 
    // создание набора семафоров с одним семафором
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }
    
    mybuf.sem_num = 0; // индекс семафора в буфере, первый семафор
    mybuf.sem_op  = -1; // уменьшаем значение семафора на 1 (wait)
    mybuf.sem_flg = 0; // ожидание пока семафор не станет доступен
    // ожидание семафора
    if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
    }  
        
    printf("The condition is present\n");
    return 0;
}
