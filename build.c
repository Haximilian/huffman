#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "build.h"
#include "heap.h"

huffman_t* create_ftable() {
    huffman_t* ftable = malloc(ASCII_SIZE * sizeof(huffman_t));
    
    for (char i = 0; i < ASCII_SIZE; i++) {
        ftable[i].freq = 0;
        ftable[i].type = external;
        ftable[i].ch = i;
    }

    return(ftable);
}

void count_chars(huffman_t* ftable, hstring_t* str) {
    for (int i = 0; i < str->size; i++) {
        ftable[str->str[i]].freq++;
    }
}

huffman_t* build_tree(huffman_t* ftable) {
    heap_t* heap = create_heap(ASCII_SIZE);

    for (char i = 0; i < ASCII_SIZE; i++) {
        heap_push(heap, (element_t*) &ftable[i]);
    }

    huffman_t* first;
    huffman_t* second;
    while (true) {
        if (!heap_pop(heap, (element_t**) &first)) {
            printf("build tree panic\n");
            exit(EXIT_FAILURE);
        }

        if (!heap_pop(heap, (element_t**) &second)) {
            break;
        }

        huffman_t* root = malloc(sizeof(huffman_t));

        root->freq = first->freq + second->freq;
        root->type = internal;
        root->l = first;
        root->r = second;

        heap_push(heap, (element_t*) root);
    }

    return(first);
}

void _build_etable(huffman_t* root, list_t** etable, list_t* curr) {
    if (root->type == external) {
        etable[root->ch] = curr;
    } else if (root->type == internal) {
        list_t* l = copy_list(curr);
        list_push(l, false);

        list_t* r = copy_list(curr);
        list_push(r, true);

        _build_etable(root->l, etable, l);
        _build_etable(root->r, etable, r);
    }
}

list_t** create_etable(huffman_t* root) {
    list_t** etable = malloc(ASCII_SIZE * sizeof(list_t*));

    list_t* e = create_list();

    _build_etable(root, etable, e);

    return(etable);
}