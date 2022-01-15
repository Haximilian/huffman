#include "build.h"
#include "hstring.h"

#include <stdio.h>
#include <stdlib.h>
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
    free(str);

    build_tree(ftable);

    free(ftable);

    return(0);
}
