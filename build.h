#include "huffman.h"
#include "string.h"
#include "list.h"

#define ASCII_SIZE 0x7F

huffman_t* create_ftable();

void count_chars(huffman_t* ftable, string_t str);

huffman_t* build_tree(huffman_t* ftable);

list_t** create_etable(huffman_t* root);



// todo: deallocate tree including ftable