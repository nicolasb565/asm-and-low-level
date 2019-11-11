#ifndef STACK_H
#define STACK_H
#include "buffer.h"

struct stack{
    struct buffer buf;
    void* top;
    size_t element_size;
};
typedef struct stack* stack_t;

int stack_create(stack_t stack_, size_t element_size);
void* stack_pop(stack_t stack_);
int stack_push(stack_t stack_, const void* data);
void stack_free(stack_t stack_);

#endif
