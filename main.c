#include "build.h"
#include "hstring.h"
#include "bit-buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define CHAR_SIZE 128

hstring_t* file_to_string(char* filename) {
    struct stat s;
    
    int descriptor = open(filename, O_RDONLY);

    fstat(descriptor, &s);

    hstring_t* to_return = malloc(sizeof(hstring_t) + s.st_size + 1);

    to_return->str[s.st_size] = '\0';

    to_return->size = read(descriptor, &(to_return->str), s.st_size);

    return(to_return);
}

int main(int argc, char** argv) {
    char* filename = argv[1];

    hstring_t* str = file_to_string(filename);

    huffman_t* ftable = create_ftable();
    count_chars(ftable, str);

    huffman_t* tree = build_tree(ftable);
 
    list_t** etable = create_etable(tree);

    free(ftable);

    bit_buffer_t* buffer = create_bit_buffer();

    for (int i = 0; i < str->size; i++) {
        bit_buffer_append(buffer, etable[str->str[i]]);
    }

    free(str);

    char* out = argv[2];

    int outfd = open(out, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG);

    hstring_t* result = to_string(buffer);

    write(outfd, result->str, result->size);

    return(0);
}