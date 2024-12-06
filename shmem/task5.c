#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHM_KEY_BASE 0xDEADBABE // Базовый ключ для формирования уникального ключа разделяемой памяти
#define SHM_MAXSIZE (1 << 20)   // Максимальный размер разделяемой памяти (1 МБ)
#define DELAY 1                 // Задержка в микросекундах между циклами опроса
#define OFFSET 100              // Смещение для хранения сообщения в разделе памяти

int main() {
    printf(
        "--------------------\n"
        "SHM-Chat 0.1\n"
        "--------------------\n"
        "To send message just type it and press Enter. Another instance of SHM-Chat receives and displays it.\n"
        "--------------------\n"
        "stdin: %s\n"
        "stdout: %s\n"
        "--------------------\n"
        "Enter any number (chat is among instances with the same number):",
        ttyname(fileno(stdin)), ttyname(fileno(stdout))
    );

    int shm_key;      
    scanf("%d", &shm_key);
    shm_key += SHM_KEY_BASE; // Уникальный ключ

    printf("--------------------\n\n");
    int shmid_test = shmget(shm_key, 4096, 0777);  // Получение идентификатора сегмента разделяемой памяти
    struct shmid_ds buf;                           // Структура для получения информации о сегменте
    shmctl(shmid_test, IPC_STAT, &buf);            // Получение статуса сегмента

    // Проверка на количество подключенных процессов
    if (buf.shm_nattch > 2 && buf.shm_nattch < 0xFF)
    {
        printf("Only tet-a-tet chat is supported! Now exiting...\n");
        exit(1); // Завершение программы, если подключено более двух терминалов
    }

    pid_t childpid; // Переменная для хранения идентификатора дочернего процесса

    if ((childpid = fork()) == -1) {
        perror("fork error");
    }
    
    if (childpid == 0) {
        usleep(DELAY);                            // Задержка перед началом работы
        int shmid = shmget(shm_key, 4096, 0777);  // Получение идентификатора сегмента разделяемой памяти
        char* mem = (char*)shmat(shmid, NULL, 0); // Присоединение сегмента к адресу процесса
        mem[0] = 0; // Инициализация первого байта для проверки наличия сообщения
        for (;;) {
            if (mem[0] != 0 && strcmp(mem, ttyname(fileno(stdout))) != 0) // Проверка на наличие сообщения и что оно не от текущего терминала
            {
                printf("--> %s\n", mem + OFFSET); // Вывод сообщения, начиная с OFFSET
                mem[0] = 0; // Сброс первого байта после чтения сообщения
            }
            usleep(DELAY); // Задержка перед следующим циклом
        }
    } 
    else {
        // Родительский процесс: считывает исходящие сообщения
        int shmid = shmget(shm_key, 4096, IPC_CREAT | 0777); // Создание сегмента разделяемой памяти, если он не существует
        char* mem = (char*)shmat(shmid, NULL, 0); // Присоединение сегмента к адресу процесса        
        usleep(DELAY); // Задержка перед началом работы
        for (;;)
        {
            fgets(mem + OFFSET, SHM_MAXSIZE - OFFSET, stdin);
            // Первый байт взводим в '1' для обозначения наличия сообщения
            mem[0] = '1'; 
            usleep(DELAY); // Задержка перед следующим циклом
        }
    }
} 