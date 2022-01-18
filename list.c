#include "list.h"

#include <stdlib.h>
#include <string.h>

list_t* create_list() {
    list_t* t = malloc(sizeof(list_t));
    memset(t, 0, sizeof(list_t));

    return(t);
}

list_t* copy_list(list_t* l) {
    list_t* to_return = create_list();

    for (list_node_t* curr = l->head; curr != NULL; curr = curr->next) {
        list_push(to_return, curr->val);
    }

    return(to_return);
}

void list_push(list_t* l, bool val) {
    list_node_t* t = malloc(sizeof(list_node_t));
    t->next = NULL;
    t->val = val;

    if (l->size++) {
        l->tail->next = t;
    } else {
        l->head = t;
    }

    l->tail = t;
}