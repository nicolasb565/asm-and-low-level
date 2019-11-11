#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

int stack_create(stack_t stack_, size_t element_size){
    stack_->element_size = element_size;
    buffer_create(&stack_->buf, 256 * element_size);
    stack_->top = stack_->buf.data - element_size; /*stack is empty, so 1 element before 1st element*/
    return stack_->buf.data != NULL;
}

void* stack_pop(stack_t stack_){
    void* value;
    if(stack_->top >= stack_->buf.data){
        value = stack_->top;
        stack_->top -= stack_->element_size;
    }
    return value;
}

int stack_push(stack_t stack_, const void* data){
    if(stack_->top + stack_->element_size < stack_->buf.data + stack_->buf.capacity){
        stack_->top += stack_->element_size;
        memcpy(stack_->top, data, stack_->element_size);
    }
    else{
        /*must do buffer_realloc because push would overflow*/
        size_t offset = stack_->top - stack_->buf.data + stack_->element_size;
        if(buffer_realloc(&stack_->buf, stack_->buf.capacity + 256)){
            stack_->top = stack_->buf.data + offset;
            memcpy(stack_->top, data, stack_->element_size);
        }
        else{
            return 0; /*could not push because buffer_realloc failed (insufficient memory???)*/
        }
    }
    return 1;
}

void stack_free(stack_t stack_){
    buffer_free(&stack_->buf);
}

int main(){
    struct stack my_stack;
    stack_create(&my_stack, sizeof(int));
    int* src = malloc(1024 * sizeof(int));
    int i;
    for(i = 0; i<1024; i++){
        src[i] = i;
        stack_push(&my_stack, &i);
    }
    
    int values_are_valid = 1;
    for(i = 1023; i >= 0; i--){
        int value_from_stack = *(int*)stack_pop(&my_stack);
        if( value_from_stack != src[i]){
            printf("error, %i != %i\n", value_from_stack, i);
            values_are_valid = 0;
        }
    }
    
    if(values_are_valid){
        printf("all values are valid!!!\n");
    }
    
    stack_free(&my_stack);
    free(src);
    
    return 0;
}
