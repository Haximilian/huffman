#include <stdlib.h>
#include <stdio.h>

#include "build.h"
#include "heap.h"

huffman_t* create_ftable() {
    huffman_t* ftable = malloc(ASCII_SIZE * sizeof(huffman_t));
    
    for (char i = 0; i < ASCII_SIZE; i++) {
        ftable[i].freq = 0;
        ftable[i].type = external;
        ftable[i].val.ch = i;
    }

    return(ftable);
}

void count_chars(huffman_t* ftable, hstring_t* str) {
    for (int i = 0; i < str->size; i++) {
        ftable[str->str[i]].freq++;
    }
}

huffman_t* build_tree(huffman_t* ftable) {
    heap_t* heap = create_heap(ASCII_SIZE);

    for (char i = 0; i < ASCII_SIZE; i++) {
        heap_push(heap, (element_t*) &ftable[i]);
    }

    huffman_t* t;
    while (heap_pop(heap, ((element_t**) &t))) {
        printf("%c: %d\n", t->val.ch, t->freq);
    }

    // temporary
    return(ftable);
}