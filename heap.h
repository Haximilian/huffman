typedef struct heap heap_t;
struct heap {
    int size;
    int cap;
    int arr[0];
};

heap_t* create_heap(int cap);

int* heap_push(heap_t* heap, int value);

int heap_pop(heap_t* heap);

int* heap_update(heap_t* heap, int* elem, int value);