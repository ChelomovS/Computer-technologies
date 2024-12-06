#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

const int BUFFER_SIZE = 64;

int ReadFromFile(const char* file_name);
int WriteToFile(const char* file_name);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments provided\n");
        return EXIT_FAILURE;
    }

    pid_t child_pid = fork();
    if (child_pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return EXIT_FAILURE;
    }

    if (child_pid == 0) {
        return WriteToFile(argv[1]);
    } else {
        return ReadFromFile(argv[1]);
    }
}

int ReadFromFile(const char* file_name) {
    int file_descriptor = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777); 

    if (file_descriptor < 0) {
        fprintf(stderr, "Unable to open file: %s\n", file_name);
        return EXIT_FAILURE;
    }

    while (1) {
        char buffer[BUFFER_SIZE + 1] = {0};
        ssize_t bytes_read = read(file_descriptor, buffer, BUFFER_SIZE);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            write(fileno(stdout), buffer, (size_t)bytes_read);
        }
    }

    close(file_descriptor); // Закрываем дескриптор файла перед выходом
    return EXIT_SUCCESS;
}

int WriteToFile(const char* file_name) {
    int file_descriptor = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777); 

    if (file_descriptor < 0) {
        fprintf(stderr, "Unable to open file: %s\n", file_name);
        return EXIT_FAILURE;
    }

    while (1) {
        char buffer[BUFFER_SIZE + 1] = {0};
        ssize_t bytes_read = read(fileno(stdin), buffer, BUFFER_SIZE);
    
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            write(file_descriptor, buffer, (size_t)bytes_read);
        }
    }

    close(file_descriptor);
    return EXIT_SUCCESS;
}