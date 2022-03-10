#include <stdint.h>

#ifndef HUFFMAN
#define HUFFMAN

// assume this is 4 bytes
typedef enum huffman_type {
    external = 0, 
    internal
} huffman_type_t;

typedef struct huffman {
    uint32_t freq;

    huffman_type_t type; 
    union {
        // initial byte belongs to l and ch
        struct {
            uint32_t l;
            uint32_t r;
        };
        unsigned char ch;
    };
} huffman_t __attribute__ ((aligned(4)));

#endif
