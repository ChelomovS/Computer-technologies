#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define MAKE_RAD_ANGLE(DEG_ANGLE) ((((double)(DEG_ANGLE)) / 180.0) * M_PI)

typedef struct {
    double angle;
    double* result;
} ThreadData;

void* cos_sq_by_thread(void* arg) {
    assert(arg);
    ThreadData* data = (ThreadData*)arg;
    fprintf(stderr, "second thread: calculating cos^2\n");
    sleep(5);
    *(data->result) = cos(data->angle) * cos(data->angle);
    return NULL;
}

void* sin_sq_by_thread(void* arg) {
    assert(arg);
    ThreadData* data = (ThreadData*)arg;
    fprintf(stderr, "first thread: calculating sin^2\n");
    sleep(5);
    *(data->result) = sin(data->angle) * sin(data->angle);
    return NULL;
}

int main() {
    printf("Введите угол в градусах: ");
    long angle_in_deg = 0;

    if (!scanf("%ld", &angle_in_deg)) {
        fprintf(stderr, "\nError input\n");
        exit(-1);
    }

    double angle_in_rad = MAKE_RAD_ANGLE(angle_in_deg);

    pthread_t first_thread;
    pthread_t second_thread;

    double sin_sq = 0;
    double cos_sq = 0;

    ThreadData sin_data = { angle_in_rad, &sin_sq };
    ThreadData cos_data = { angle_in_rad, &cos_sq };

    if (pthread_create(&first_thread, NULL, &sin_sq_by_thread, &sin_data)) {
        fprintf(stderr, "Error with first pthread\n");
        exit(-1);
    }

    if (pthread_create(&second_thread, NULL, &cos_sq_by_thread, &cos_data)) {
        fprintf(stderr, "Error with second pthread\n");
        exit(-1);
    }

    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);

    double sum = sin_sq + cos_sq;
    printf("sin^2 + cos^2 = %f\n", sum);
    
    if (fabs(sum - 1.0) < 1e-6)
        printf("Доказано!\n");
    else 
        printf("НЕ доказано!\n");

    return 0;
}