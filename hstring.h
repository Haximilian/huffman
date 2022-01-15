#ifndef HSTRING
#define HSTRING

typedef struct hstring hstring_t;
struct hstring {
    int size;
    char str[0];
};

#endif