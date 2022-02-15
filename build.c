#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "string.h"
#include "build.h"
#include "heap.h"

huffman_t* create_ftable() {
    huffman_t* ftable = malloc((2 * ASCII_SIZE - 1) * sizeof(huffman_t));
    
    for (char i = 0; i < ASCII_SIZE; i++) {
        ftable[i].freq = 0;
        ftable[i].type = external;
        ftable[i].ch = i;
    }

    return(ftable);
}

void count_chars(huffman_t* ftable, string_t s) {
    for (int i = 0; i < get_size(s); i++) {
        ftable[s[i]].freq++;
    }
}

huffman_t* build_tree(huffman_t* ftable) {
    heap_t* heap = create_heap(ASCII_SIZE);

    for (int i = 0; i < ASCII_SIZE; i++) {
        heap_push(heap, (element_t*) &ftable[i]);
    }

    huffman_t* first;
    huffman_t* second;
    for (int i = 0; i < ASCII_SIZE - 1; i++) {
        if (!heap_pop(heap, (element_t**) &first)) {
            exit(EXIT_FAILURE);
        }

        if (!heap_pop(heap, (element_t**) &second)) {
            exit(EXIT_FAILURE);
        }

        huffman_t* root = &ftable[ASCII_SIZE + i];

        root->freq = first->freq + second->freq;
        root->type = internal;
        root->l = first - ftable;
        root->r = second - ftable;

        heap_push(heap, (element_t*) root);
    }

    huffman_t* to_return;
    if (!heap_pop(heap, (element_t**) &to_return)) {
        exit(EXIT_FAILURE);
    }

    assert(heap->size == 0);

    return(to_return);
}

void _build_etable(huffman_t* ftable, huffman_t* root, list_t** etable, list_t* curr) {
    if (root->type == external) {
        etable[root->ch] = curr;
    } else if (root->type == internal) {
        list_t* l = copy_list(curr);
        list_push(l, false);

        list_t* r = copy_list(curr);
        list_push(r, true);

        _build_etable(ftable, &ftable[root->l], etable, l);
        _build_etable(ftable, &ftable[root->r], etable, r);
    }
}

list_t** create_etable(huffman_t* ftable, huffman_t* root) {
    list_t** etable = malloc(ASCII_SIZE * sizeof(list_t*));

    list_t* e = create_list();

    _build_etable(ftable, root, etable, e);

    return(etable);
}
