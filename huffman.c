#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define CHAR_SIZE 128

char buffer[BUFFER_SIZE];

int main(int argc, char** argv) {
    char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    int size = read(fd, buffer, BUFFER_SIZE);
    buffer[size] = '\0';

    int freq_table[CHAR_SIZE];
    memset(freq_table, 0, CHAR_SIZE * sizeof(int));

    for (int i = 0; i < size; i++) {
        freq_table[buffer[i]]++;
    }

    heap_t* heap = create_heap(CHAR_SIZE);

    for (unsigned char i = 0; i < CHAR_SIZE; i++) {
        element_t e;
        e.ch = i;
        e.freq = freq_table[i];
        heap_push(heap, e);
    }

    char l[2];
    l[1] = '\0';
    for (unsigned char i = 0; i < CHAR_SIZE; i++) {
        element_t t;
        t = heap_pop(heap);
        l[0] = t.ch;
        printf("%s: %d\n", l, t.freq);
    }
    
    return 0;
}
