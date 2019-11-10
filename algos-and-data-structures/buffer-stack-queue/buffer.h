#ifndef BUFFER_H
#define BUFFER_H
#include<stddef.h>

struct buffer{
    void* data;
    size_t capacity;
    size_t length;
};
typedef struct buffer* buffer_t;

int buffer_create(buffer_t buf, size_t size);
int buffer_realloc(buffer_t buf, size_t new_size);
void buffer_free(buffer_t buf);
#endif
