#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "buffer.h"

int buffer_create(buffer_t buf, size_t size){
    buf->data = malloc(size);
    if(buf->data != NULL){
        buf->capacity = size;
        buf->length = 0;
        return 1; 
    }
    /*make it clear that allocation failed*/
    buf->data = NULL;
    buf->capacity = 0;
    buf->length = 0;
    return 0;
}

int buffer_realloc(buffer_t buf, size_t new_size){
    assert(buf->data != NULL);
    if(new_size < buf->length) { return 0; } /*will not shrink if memory is in use*/
    void* new_data = realloc(buf->data, new_size);
    if(new_data != NULL){
        buf->data = new_data;
        buf->capacity = new_size;
        return 1;
    }
    return 0;
}

void buffer_free(buffer_t buf){
    buf->capacity = 0;
    buf->length = 0;
    free(buf->data);
    buf->data = NULL;
}

__attribute__((weak)) int main(){
    int status;
    void* data;
    struct buffer buf;
    status = buffer_create(&buf, 1024);
    if(status == 1 && buf.data != NULL && buf.capacity == 1024 && buf.length == 0){
        printf("buffer creation success!!!\n");
    }
    else{
        printf("buffer creation failure!!!\n");
    }
    
    status = buffer_realloc(&buf, 2048);
    data = buf.data;
    if(status == 1 && buf.data != NULL && buf.capacity == 2048 && buf.length == 0){
        printf("buffer realloc success!!!\n");
    }
    else{
        printf("buffer realloc failure!!!\n");
    }
    
    buf.length = 1024;
    status = buffer_realloc(&buf, 512);
    if(status == 0 && buf.data == data && buf.capacity == 2048 && buf.length == 1024){
        printf("buffer realloc has refused invalid request where realloc would create a buffer to small for the data already contained!!!\n");
    }
    else{
        printf("buffer realloc has accepted invalid request, error!!!\n");
    }
    
    status = buffer_realloc(&buf, SIZE_MAX); /*no way this allocation will work*/
    if(status == 0 && buf.data == data && buf.capacity == 2048 && buf.length == 1024){
        printf("buffer realloc sucessfully dealed with a request where there is insufficient memory!!!\n");
    }
    else{
        printf("this should not work!!!\n");
    }
    
    buffer_free(&buf);
    if(buf.data == NULL && buf.capacity == 0 && buf.length == 0){
        printf("buffer free worked!!!\n");
    }
    else{
        printf("buffer free did not work!!!\n");
    }
    
    return 0;
}
