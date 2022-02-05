#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "string.h"

typedef struct bit_buffer bit_buffer_t;
struct bit_buffer {
    char curr;
    char ch;
    list_t* buffer;
};

bit_buffer_t* create_bit_buffer();

void bit_buffer_append(bit_buffer_t* buffer, list_t* bits);

string_t to_string(bit_buffer_t* buffer);