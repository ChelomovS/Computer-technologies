/* Пример создания нового процесса с разной работой процессов ребенка и родителя */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    pid_t pid, ppid, chpid;
    size_t counter = 0;
    
    chpid = fork();
    if (chpid < 0)
    {
        fprintf(stderr, "Ошибка\n");
        return 1;
    } 
    if (chpid == 0)
    {
        /* Порожденный процесс */
        ++counter;
        pid = getpid();
        ppid = getppid();

        printf("pid = %d, ppid = %d, counter = %zu\n", pid, ppid, counter); 
    } else {
        /* Родительский процесс */
        pid = getpid();
        ppid = getppid();

        printf("My pid = %d, my ppid = %d, counter = %zu\n", pid, ppid, counter); 
    }

    return 0;
}