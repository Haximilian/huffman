#include "huffman.h"
#include "string.h"
#include "list.h"

#define ASCII_SIZE 0x7F
#define HUFFMAN_TREE_SIZE (2 * ASCII_SIZE - 1)

huffman_t* create_ftable();

void count_chars(huffman_t* ftable, string_t str);

huffman_t* build_tree(huffman_t* ftable);

list_t** create_etable(huffman_t* ftable, huffman_t* root);

void serialize(huffman_t* table, size_t size);

// todo: deallocate tree including ftable
