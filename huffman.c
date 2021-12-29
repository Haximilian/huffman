#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <sys/queue.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

typedef struct heap heap_t;
struct heap {
    int value;
    heap_t* l;
    heap_t* r;
};

typedef struct box box_t;
struct box {
    size_t size;
    heap_t* root;
};

// (0, -1), (1, 0), (2, 1), (3, 1), ...
size_t size_to_height(size_t size) {
    int h = -1;
    while (size > 0) {
        size = size >> 1;
        h++;
    }
    return h;
}

heap_t* create_heap(int value) {
    heap_t* t = malloc(sizeof(heap_t));
    memset(t, 0, sizeof(heap_t));
    t->value = value;
    return t;
}

heap_t** to_insert(box_t* box) {
    if (box->root == NULL) {
        return &(box->root);
    }

    heap_t* curr = box->root;

    // n is equal to or greater than 2
    size_t n = box->size + 1;
    size_t h = size_to_height(n);

    for (; h > 1; h--) {
        int r = (0x1 << (h - 1)) & n;
        if (r) {
            curr = curr->r;
        } else {
            curr = curr->l;
        }
    }

    if (n & 0x1) {
        return &(curr->r);
    } else {
        return &(curr->l);
    }
}


void insert_value(box_t* box, int value) {
    *to_insert(box) = create_heap(value);
    box->size++;
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

    box_t box = {0, NULL};

    insert_value(&box, 1);
    insert_value(&box, 2);
    insert_value(&box, 3);
    insert_value(&box, 4);
    insert_value(&box, 5);
    insert_value(&box, 6);
    insert_value(&box, 7);
    insert_value(&box, 8);
    insert_value(&box, 9);
    insert_value(&box, 10);
    insert_value(&box, 11);

    print_heap(box.root);
    
    return 0;
}
