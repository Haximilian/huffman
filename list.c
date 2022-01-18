#include "list.h"

#include <stdlib.h>

list_t* create_list() {
    list_t* t = malloc(sizeof(list_t));

    t->size = 0;
    t->head = 0;
    t->tail = 0;

    return(t);
}

void list_push(list_t* l, bool val) {
    _list_node_t* t = malloc(sizeof(_list_node_t));
    t->next = 0;
    t->val = 0;

    if (l->size++) {
        l->tail->next = t;
    } else {
        l->head = t;
    }

    l->tail = t;
}