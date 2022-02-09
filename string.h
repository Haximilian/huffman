#ifndef STRING
#define STRING

#include <stdlib.h>

typedef char* string_t;

typedef struct string_metadata string_metadata_t;
struct string_metadata {
    size_t size;
    char str[0];
};

string_t create_string(size_t size);

size_t get_size(string_t);

void destroy_string(string_t s);

#endif