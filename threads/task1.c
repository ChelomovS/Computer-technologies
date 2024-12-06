#include <stdio.h>
#include <pthread.h> // для работы с потоками исполнения

void* any_func(void* arg) // Выполняется в отдельном потоке
{
    int a = *((int *)arg);
    ++a;
    return (void*)(size_t)a; // Возвращаем void указатель на выделенную память 
                             // (кастуем к size_t тк размер будет соответствовать размеру указателя на данной платформе)
}

int main(void)
{
    pthread_t thread; // Переменная для идентификации потока
    int parg = 2007;
    if (pthread_create(&thread, NULL, &any_func, &parg) != 0) // Создает новый поток, он выполняет функцию any_func
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    int data = 0;
    pthread_join(thread, (void**)&data); // Ожидаем завершения потока, после чего получаем результат и помещаем его в padata
    
    int res = (int)(size_t)any_func(&data); // Чтобы получить 2009

    printf("%d\n", res);
    return 0;
}