#include <stdlib.h>

#include "string.h"

string_t create_string(size_t size) {
    string_metadata_t *s = malloc(sizeof(string_metadata_t) + size);

    s->size = size;

    return(s->str);
}

size_t get_size(string_t s) {
    size_t size = *((size_t*) ((char*) s - sizeof(size_t)));

    return(size);
}

void destroy_string(string_t s) {
    free((char*) s - sizeof(size_t));
}