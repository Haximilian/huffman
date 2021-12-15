#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

int main(int argc, char** argv) {
    char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    int size = read(fd, buffer, BUFFER_SIZE);
    buffer[size] = '\0';
    printf("%s\n", buffer);
    return 0;
}
