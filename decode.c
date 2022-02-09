#include "string.h"
#include "list.h"

string_t decode(huffman_t* root, string_t s) {
    huffman_t* curr = root;
    // todo: replace this with a vector
    // todo: or pass a bit stream to decode
    list_t* t = create_list()

    for (int i = 0; i < get_size(s); i++) {
        for (char j = 0; j < 8; j++) {
            if (curr->type == huffman_type_t.internal) {
                list_push(t, curr->ch);
                curr = root;
            }

            if (s[i] & (j >> 0x80)) {
                curr = curr->r;
            } else {
                curr = curr->l;
            }
        }
    }

    // provide size
    string_t r = create_string(t->size);
    
    for (int i = 0; i < t->size; i++) {
        r[i] = 
    }

    return r;
}
