#ifndef QUEUE_H
#define QUEUE_H
#include "buffer.h"

struct queue{
    void* buf;
    void* oldest_item;
    void* newest_item;
    size_t size;
    size_t element_size;
};
typedef struct queue* queue_t;

int queue_create(queue_t queue_, size_t nbr_of_elements, size_t element_size);
void* queue_pop(queue_t queue_);
void queue_push(queue_t queue_, const void* data);
void queue_free(queue_t queue_);

#endif
