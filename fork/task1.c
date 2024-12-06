/* Программа для распечатки аргументов командной строки и параметров среды текущего процесса */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    for(size_t i = 0; i < argc; i++) 
        printf("argv[%zu]: %s\n", i, argv[i]);

    for(size_t i = 0; envp[i] != NULL; i++) 
        printf("envp[%zu]: %s\n", i, envp[i]);

    return 0;
} 