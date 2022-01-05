#include "heap.h"

#include <stdio.h>

int main() {
    heap_t* heap = create_heap(32);

    heap_push(heap, 5);
    heap_push(heap, 25);
    heap_push(heap, 15);
    heap_push(heap, 12);
    heap_push(heap, 125);
    heap_push(heap, 6);
    heap_push(heap, 65);
    heap_push(heap, 35);
    int* a = heap_push(heap, 72);
    heap_push(heap, 825);

    heap_update(heap, a, 5555);

    for (int i = 0; i < 10; i++) {
        printf("%d,", heap_pop(heap));
    }
}