#include "decode.h"

#include "list.h"

string_t decode(huffman_t* ftable, huffman_t* root, string_t s) {
    huffman_t* curr = root;
    // todo: replace this with a vector
    // todo: or pass a bit stream to decode
    list_t* t = create_list();

    for (int i = 0; i < get_size(s); i++) {
        for (char j = 0; j < 8; j++) {
            if (curr->type == external) {
                list_push(t, curr->ch);
                curr = root;
            }

            if (s[i] & (0x80 >> j)) {
                curr = &ftable[curr->r];
            } else {
                curr = &ftable[curr->l];
            }
        }
    }

    // provide size
    string_t r = create_string(t->size);
    list_node_t* ch = t->head;
    for (int i = 0; i < t->size; i++) {
        r[i] = ch->val;
        ch = ch->next;
    }

    return r;
}
