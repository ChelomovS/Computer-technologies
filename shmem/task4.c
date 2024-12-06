#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv) {
    int shm_id;     // идентификатор сегмента разделяемой памяти
    char* shm_buf;  // указатель на буфер, который будет использоваться для доступа к разделяемой памяти
    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }

    shm_id = atoi(argv[1]); // Преобразуем строку в число

    // Присоединяем сегмент разделяемой памяти к адресу процесса
    shm_buf = (char *)shmat(shm_id, 0, 0);
    // shm_id - идентификатор сегмента разделяемой памяти
    // Первый 0 означает, что система сама выберет адрес
    // Второй 0 означает, что флаги не используются

    // Проверяем на ошибку при присоединении
    if (shm_buf == (char *)-1) { // shmat возвращает -1 в случае ошибки
        fprintf(stderr, "shmat() error\n");
        return 1; 
    }

    printf("Message: %s\n", shm_buf); // Печать сообщения, хранящегося в сегменте разделяемой памяти

    shmdt(shm_buf); 

    return 0;
}
