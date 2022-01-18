#include <stdbool.h>

typedef struct _list_node _list_node_t;
struct _list_node {
    _list_node_t* next;
    bool val;
};

typedef struct list list_t;
struct list {
    int size;
    _list_node_t* head;
    _list_node_t* tail;
};

list_t* create_list();

void list_push(list_t* l, bool val);