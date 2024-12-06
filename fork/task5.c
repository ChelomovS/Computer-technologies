#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

const size_t BUFFER_SIZE = 128;

int main(int argc, char* argv[]) {
    char buffer[BUFFER_SIZE];

    if (argc <= 1) {
        fprintf(stderr, "Few input files\n");
        exit(EXIT_FAILURE);
    }
    
    int file_desc = open(argv[1], O_RDONLY);
    
    if (file_desc < 0) {
        fprintf(stderr, "Can't open file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (1) {
        ssize_t size = read(file_desc, buffer, BUFFER_SIZE);
        
        if (size < 0) {
            fprintf(stderr, "Error reading file\n");
            close(file_desc);
            exit(EXIT_FAILURE);
        }

        if (size == 0)
            break;

        int write_status = write(STDOUT_FILENO, buffer, size);
        // STDOUT_FILENO дескриптор файла, в данном случае = 1, пишем в терминал
        // второй аргумент - указатель на buffer
        if (write_status == -1) {
            fprintf(stderr, "Write error\n");
            close(file_desc);
            exit(EXIT_FAILURE);
        }
    }

    int close_status = close(file_desc); 

    if (close_status < 0) {
        fprintf(stderr, "Can't close file\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}