#include "bit-buffer.h"

#include <stdlib.h>

bit_buffer_t* create_bit_buffer() {
    bit_buffer_t* t = malloc(sizeof(bit_buffer_t));
    t->curr = 0;
    t->ch = 0;
    t->buffer = create_list();

    return(t);
}

void bit_buffer_append(bit_buffer_t* buffer, list_t* bits) {
    list_node_t* curr = bits->head;
    for (;;) {
        for (; buffer->curr < 8; buffer->curr++) {
            if (curr == NULL) {
                return;
            }
            buffer->ch |= (curr->val << (7 - buffer->curr));
            curr = curr->next;
        }
        list_push(buffer->buffer, buffer->ch);
        buffer->curr = 0;
        buffer->ch = 0;
    }
}

hstring_t* to_string(bit_buffer_t* buffer) {
    int extra = 0;
    if (buffer->curr > 0) {
        extra = 1;
    }

    hstring_t* t = malloc(sizeof(hstring_t) + buffer->buffer->size + extra);
    t->size = buffer->buffer->size;
    int i = 0;
    for (list_node_t* curr = buffer->buffer->head; curr; curr = curr->next) {
        t->str[i++] = curr->val;
    }
    if (extra) {
        t->str[buffer->buffer->size] = buffer->ch;
    }

    return(t);
}