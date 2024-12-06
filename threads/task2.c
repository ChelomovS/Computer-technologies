#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void* any_func(void* arg) {
    while (1) {
        fprintf(stderr, ". ");
        sleep(10);
    }
    return NULL;
}

int main(void) {
    int iterations = 0;
    printf("Введите количество итераций: ");
    
    if (scanf("%d", &iterations) != 1 || iterations <= 0) {
        fprintf(stderr, "Некорректный ввод!\n");
        exit(-1);
    }

    size_t total_time = 0;

    for (size_t i = 0; i < iterations; i++) {
        pthread_t thread;
        void* thread_result = NULL;

        if (pthread_create(&thread, NULL,any_func, NULL)) {
            fprintf(stderr, "Не удалось создать поток\n");
            exit(-1);
        }
        sleep(5);
        pthread_cancel(thread);
        clock_t start_time = clock();

        pthread_join(thread, &thread_result);
        
        if (thread_result == PTHREAD_CANCELED) {
            clock_t end_time = clock();
            total_time += end_time - start_time;
        } else {
            fprintf(stderr, "Поток завершился с ошибкой \n");
            exit(-1);
        }
    }

    printf("Среднее время: %lu\n", total_time / iterations);

    return 0;
}