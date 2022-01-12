#include "heap.h"

#include <stdbool.h>
#include <stdio.h>

bool validate_min_heap(heap_t* heap) {
    int parent;
    int curr = heap->size - 1;

    for (; curr > 0; curr--) {
        parent = (curr - 1) / 2;

        if (heap->arr[parent].freq > heap->arr[curr].freq) {
            return false;
        }
    }

    return true;
}

void print_heap(heap_t* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d, ", heap->arr[i].freq);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    heap_t* heap = create_heap(64);
    element_t t;

    t.ch = 'a';
    t.freq = 423;
    heap_push(heap, t);

    t.ch = 'b';
    t.freq = 23;
    heap_push(heap, t);

    t.ch = 'c';
    t.freq = 43;
    heap_push(heap, t);

    t.ch = 'd';
    t.freq = 42;
    heap_push(heap, t);

    t.ch = 'e';
    t.freq = 2;
    heap_push(heap, t);

    t.ch = 'f';
    t.freq = 25;
    heap_push(heap, t);

    t.ch = 'g';
    t.freq = 4243;
    heap_push(heap, t);

    print_heap(heap);
    while (heap_pop(heap, &t)) {
        printf("%c : %d : ", t.ch, t.freq);
        if (validate_min_heap(heap)) {
            printf("success\n");
        } else {
            printf("error\n");
        }
        print_heap(heap);
    }

    return(1);
}
