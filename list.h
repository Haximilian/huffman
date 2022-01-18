#include <stdbool.h>

typedef struct list_node list_node_t;
struct list_node {
    list_node_t* next;
    bool val;
};

typedef struct list list_t;
struct list {
    int size;
    list_node_t* head;
    list_node_t* tail;
};

list_t* create_list();

list_t* copy_list();

void list_push(list_t* l, bool val);