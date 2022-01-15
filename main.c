#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define CHAR_SIZE 128

typedef struct m_string m_string_t;
struct m_string {
    int size;
    char str[0];
};

m_string_t* file_to_string(char* filename) {
    struct stat s;
    
    int descriptor = open(filename, O_RDONLY);

    fstat(descriptor, &s);

    m_string_t* to_return = malloc(sizeof(m_string_t) + s.st_size + 1);

    to_return->str[s.st_size] = '\0';

    to_return->size = read(descriptor, &(to_return->str), s.st_size);

    return(to_return);
}

int main(int argc, char** argv) {
    char* filename = argv[1];

    m_string_t* str = file_to_string(filename);

    int freq_table[CHAR_SIZE];
    memset(freq_table, 0, CHAR_SIZE * sizeof(int));

    for (int i = 0; i < str->size; i++) {
        freq_table[str->str[i]]++;
    }

    heap_t* heap = create_heap(CHAR_SIZE);

    for (unsigned char i = 0; i < CHAR_SIZE; i++) {
        element_t t;
        t.ch = i;
        t.freq = freq_table[i];
        heap_push(heap, t);
    }

    element_t t;
    while (heap_pop(heap, &t)) {
        printf("%c: %d\n", t.ch, t.freq);
    }
    
    return 0;
}
