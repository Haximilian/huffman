#include "heap.h"

#include <stdlib.h>

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
    int large;
    element_t t;
    for (;;) {
        l = curr * 2 + 1;
        r = curr * 2 + 2;

        if (l < heap->size && r < heap->size) {
            if (heap->arr[l].freq > heap->arr[r].freq) {
                large = l;
            } else {
                large = r;
            }
        }

        if (l < heap->size && r >= heap->size) {
            large = l;
        }

        if (l >= heap->size && r >= heap->size) {
            break;
        }

        if (heap->arr[curr].freq > heap->arr[large].freq) {
            t = heap->arr[large];
            heap->arr[large] = heap->arr[curr];
            heap->arr[curr] = t;

            curr = large;
        } else {
            break;
        }
    }
}

element_t heap_pop(heap_t* heap) {
    element_t to_return = {0, 0};
    if (heap->size == 0) {
        return(to_return);
    }

    to_return = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];

    _bubble_down(heap, 0);

    return(to_return);
}
