#include "heap.h"

#include <stdlib.h>
#include <stdbool.h>

heap_t* create_heap(int cap) {
    heap_t* heap = malloc(sizeof(heap_t) + cap * sizeof(element_t));
    heap->size = 0;
    heap->cap = cap;
    return heap;
}

int elem_to_index(heap_t* heap, element_t* elem) {
    return (elem - heap->arr) / sizeof(element_t);
}

element_t* heap_push(heap_t* heap, element_t value) {
    if (heap->size >= heap->cap) {
        return(0);
    }

    int curr = heap->size++;
    int parent = (curr - 1) / 2;

    heap->arr[curr] = value;

    while (curr != 0 && heap->arr[parent].freq > heap->arr[curr].freq) {
        heap->arr[curr] = heap->arr[parent];
        heap->arr[parent] = value;

        curr = parent;
        parent = (curr - 1) / 2;
    }

    return &(heap->arr[curr]);
}

void _bubble_down(heap_t* heap, int curr) {
    int l;
    int r;
    int small;
    element_t t;
    for (;;) {
        l = curr * 2 + 1;
        r = curr * 2 + 2;

        if (l < heap->size && r < heap->size) {
            if (heap->arr[l].freq < heap->arr[r].freq) {
                small = l;
            } else {
                small = r;
            }
        }

        if (l < heap->size && r >= heap->size) {
            small = l;
        }

        if (l >= heap->size && r >= heap->size) {
            break;
        }

        if (heap->arr[curr].freq > heap->arr[small].freq) {
            t = heap->arr[small];
            heap->arr[small] = heap->arr[curr];
            heap->arr[curr] = t;

            curr = small;
        } else {
            break;
        }
    }
}

bool heap_pop(heap_t* heap, element_t* r_val) {
    if (heap->size == 0) {
        return(false);
    }

    *r_val = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];

    _bubble_down(heap, 0);

    return(true);
}
