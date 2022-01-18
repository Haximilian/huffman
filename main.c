#include "build.h"
#include "hstring.h"

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
    free(str);

    huffman_t* tree = build_tree(ftable);

    list_t** etable = create_etable(tree);

    free(ftable);

    for (char i = 0; i < ASCII_SIZE; i++) {
        list_node_t* curr = etable[i]->head;
        printf("%c: ", i);
        for (; curr; curr = curr->next) {
            if (curr->val) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

    return(0);
}