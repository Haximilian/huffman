#include "build.h"
#include "string.h"
#include "bit-buffer.h"

#include "decode.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

string_t file_to_string(char* filename) {
    struct stat s;
    
    int descriptor = open(filename, O_RDONLY);

    fstat(descriptor, &s);

    string_t to_return = create_string(s.st_size);

    size_t bytes = read(descriptor, to_return, s.st_size);
    if (bytes != s.st_size) {
        // todo: error handling
        return NULL;
    }

    return(to_return);
}

int main(int argc, char** argv) {
    char* filename = argv[1];

    string_t str = file_to_string(filename);

    huffman_t* ftable = create_ftable();
    count_chars(ftable, str);

    huffman_t* tree = build_tree(ftable);
 
    list_t** etable = create_etable(ftable, tree);

    bit_buffer_t* buffer = create_bit_buffer();

    for (size_t i = 0; i < get_size(str); i++) {
        bit_buffer_append(buffer, etable[(unsigned char) str[i]]);
    }

    destroy_string(str);

    char* out = argv[2];

    int outfd = open(out, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG);

    serialize(ftable, HUFFMAN_TREE_SIZE);
    write(outfd, ftable, HUFFMAN_TREE_SIZE * sizeof(huffman_t));

    string_t result = to_string(buffer);

    write(outfd, result, get_size(result));

    free(ftable);

    destroy_string(result);

    return(0);
}
