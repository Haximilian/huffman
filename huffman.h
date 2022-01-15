typedef enum huffman_type huffman_type_t;
enum huffman_type {
    external = 0, 
    internal
};

typedef struct huffman huffman_t;
struct huffman {
    int freq;

    huffman_type_t type; 
    union {
        struct {
            huffman_t* l;
            huffman_t* r;
        } child;
        char ch;
    } val;
};
