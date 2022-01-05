#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <sys/queue.h>

#define BUFFER_SIZE 1024
#define CHAR_SIZE 128

char buffer[BUFFER_SIZE];

int main(int argc, char** argv) {
    char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    int size = read(fd, buffer, BUFFER_SIZE);
    buffer[size] = '\0';

    int frequency[CHAR_SIZE];
    memset(frequency, 0, CHAR_SIZE * sizeof(int));

    for (int i = 0; i < size; i++) {
        frequency[buffer[i]]++;
    }

    char l[2];
    l[1] = '\0';
    for (int i = 0; i < CHAR_SIZE; i++) {
        l[0] = i;
        printf("%s: %d\n", l, frequency[i]);
    }
    
    return 0;
}
