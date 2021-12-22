#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/queue.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

// todo: create container type for heap_t

typedef struct heap heap_t;
struct heap {
    size_t size;
    int value;
    heap_t* l;
    heap_t* r;
};

heap_t* create_heap(int value) {
    heap_t* t = malloc(sizeof(heap_t));
    memset(t, 0, sizeof(heap_t));
    return t;
}

heap_t* heap_push(heap_t* heap, int value) {
    if (heap == NULL) {
        return NULL;
    }

    heap->size++;

    if (heap->l == NULL) {
        heap->l = create_heap(value);
    }
    
    if (heap->r == NULL) {
        heap->r = create_heap(value);
    }

    if (heap->l->size == heap->r->size) {
        return heap_push(heap->l, value);
    }

}

struct _qvertex {
    TAILQ_ENTRY(_qvertex) q;
    heap_t* val;
};

TAILQ_HEAD(_queue, _qvertex);

void _append_queue(struct _queue* queue, heap_t* heap) {
    struct _qvertex* t = malloc(sizeof(struct _qvertex));
    t->val = heap;
    TAILQ_INSERT_TAIL(queue, t, q);
}

// prints a balanced binary tree
void print_heap(heap_t* heap) {
    struct _queue queue;
    TAILQ_INIT(&queue);

    _append_queue(&queue, heap);

    int count = 1;
    int height = 0;

    while (!TAILQ_EMPTY(&queue)) {
        struct _qvertex* curr = TAILQ_FIRST(&queue);
        TAILQ_REMOVE(&queue, curr, q);

        printf("%d,", curr->val->value);
        if (--count == 0) {
            printf("\n");
            height++;
            count = 1 << height;
            printf("height: %d, count: %d\n", height, count);
        }

        if (curr->val->l) {
            _append_queue(&queue, curr->val->l);
        }
        if (curr->val->r) {
            _append_queue(&queue, curr->val->r);
        }
        free(curr);
    }
}

int main(int argc, char** argv) {
    char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    int size = read(fd, buffer, BUFFER_SIZE);
    buffer[size] = '\0';
    printf("%s\n", buffer);

    heap_t d = {0, 5, NULL, NULL};
    heap_t c = {0, 28, &d, NULL};
    heap_t b = {0, 21, NULL, NULL};
    heap_t a = {0, 234, &c, &b};

    print_heap(&a);
    
    return 0;
}
