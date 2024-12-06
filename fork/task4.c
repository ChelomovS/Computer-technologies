/* Пример программы для изменения пользовательского контекста (запуска новой программы) в порожденном процессе. */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[], char *envp[]) {
    pid_t pid, ppid, chpid;
    int counter = 0, result;
 
    chpid = fork();
    
    if (chpid == -1)
    { 
        fprintf(stderr, "Can\'t fork a child process\n");
        exit(-1);
    } 
    if (chpid > 0)
    {
        /* Родительский процесс */
        ++counter;
        
        pid = getpid();
        ppid = getppid();

        printf("pid = %d, ppid = %d, result = %d\n", (int)pid, (int)ppid, counter); 
    } else {
        
        /* Порожденный процесс */
        
        /* Мы будем запускать команду cat c аргументом командной строки без изменения параметров среды,
        т.е. фактически выполнять команду "cat имя файла", которая должна выдать содержимое данного файла на экран.
        Для функции execle в качестве имени программы мы указываем ее полное имя с путем от корневой директории.
        Первое слово в командной строке у нас должно совпадать с именем запускаемой программы. 
        Второе слово в командной строке - это имя файла, содержимое которого мы хотим распечатать.
        */

        result = execle("/bin/cat", "/bin/cat", argv[1], NULL, envp);
        
        getchar();

        if (result < 0)
        {
            fprintf(stderr, "Error on program start\n");
            exit(-1);
        }
    }
    return 0;
}
