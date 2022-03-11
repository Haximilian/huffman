#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h> 
#include <sys/stat.h>

#include "decode.h"
#include "huffman.h"
#include "build.h"
#include "string.h"

int main(int argc, char** argv) {
    char* source = argv[1];

    huffman_t* tree = malloc(HUFFMAN_TREE_SIZE * sizeof(huffman_t));

    struct stat s;

    int fd_source = open(source, O_RDONLY);

    fstat(fd_source, &s);

    read(fd_source, tree, HUFFMAN_TREE_SIZE * sizeof(huffman_t));

    // unmarshal
    for (int i = 0; i < HUFFMAN_TREE_SIZE; i++) {
        tree[i].freq = ntohl(tree[i].freq);
        tree[i].type = ntohl(tree[i].type);
        tree[i].l = ntohl(tree[i].l);
        tree[i].r = ntohl(tree[i].r);
    }

    huffman_t *root = &tree[HUFFMAN_TREE_SIZE -1];

    size_t remainder = s.st_size - HUFFMAN_TREE_SIZE * sizeof(huffman_t);

    string_t to_inflate = create_string(remainder);
    
    // todo: check return value to see if remainder bytes was read
    read(fd_source, (char*) to_inflate, remainder);

    string_t result =decode(tree, root,to_inflate);

    printf("%.*s", get_size(result), result);

    return 0;
}
