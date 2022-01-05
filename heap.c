#include "heap.h"

#include <stdlib.h>

heap_t* create_heap(int cap) {
    heap_t* heap = malloc(sizeof(heap_t) + cap * sizeof(int));
    heap->size = 0;
    heap->cap = cap;
    return heap;
}

int elem_to_index(heap_t* heap, int* elem) {
    return (elem - heap->arr) / sizeof(int);
}

int* heap_push(heap_t* heap, int value) {
    if (heap->size >= heap->cap) {
        return(0);
    }

    heap->arr[heap->size] = value;
    int curr = heap->size++;
    int parent;
    while (curr != 0) {
        parent = (curr - 1) / 2;

        if (heap->arr[parent] > heap->arr[curr]) {
            break;
        } else {
            heap->arr[curr] = heap->arr[parent];
            heap->arr[parent] = value;
        }

        curr = parent;
    }

    return &(heap->arr[curr]);
}

void _bubble_down(heap_t* heap, int curr) {
    int l;
    int r;
    int large;
    int t;
    for (;;) {
        l = curr * 2 + 1;
        r = curr * 2 + 2;

        if (l < heap->size && r < heap->size) {
            if (heap->arr[l] > heap->arr[r]) {
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

        if (heap->arr[curr] <= heap->arr[large]) {
            t = heap->arr[large];
            heap->arr[large] = heap->arr[curr];
            heap->arr[curr] = t;

            curr = large;
        } else {
            break;
        }
    }
}

int heap_pop(heap_t* heap) {
    if (heap->size == 0) {
        return(-1);
    }

    int to_return = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];

    _bubble_down(heap, 0);

    return(to_return);
}

int* heap_update(heap_t* heap, int* elem, int value) {
    if (heap->size == 0) {
        return(0);
    }

    *elem = heap->arr[--heap->size];

    int curr = elem_to_index(heap, elem);

    _bubble_down(heap, curr);

    return heap_push(heap, value);
}
