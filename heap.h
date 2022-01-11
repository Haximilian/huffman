typedef struct element element_t;
struct element {
    int freq;
    char ch;
};

typedef struct heap heap_t;
struct heap {
    int size;
    int cap;
    element_t arr[0];
};

heap_t* create_heap(int cap);

element_t* heap_push(heap_t* heap, element_t value);

element_t heap_pop(heap_t* heap);
