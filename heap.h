#include <stdbool.h>

// interface / memory layout
typedef struct element element_t;
struct element {
    int freq;
};

typedef struct heap heap_t;
struct heap {
    int size;
    int cap;
    element_t* arr[0];
};

heap_t* create_heap(int cap);

bool heap_push(heap_t* heap, element_t* ptr);

bool heap_pop(heap_t* heap, element_t** r_val);