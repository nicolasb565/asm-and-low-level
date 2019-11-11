#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "queue.h"

int queue_create(queue_t queue_, size_t nbr_of_elements, size_t element_size){
    queue_->newest_item = NULL; /*will cause push to wrap around to the beginning of the buffer*/
    queue_->oldest_item = NULL; /*will cause pop to wrap around to the beginning of the buffer*/
    queue_->size = nbr_of_elements;
    queue_->element_size = element_size;
    queue_->buf = malloc(nbr_of_elements * element_size);
    return queue_->buf != NULL;
}

void* queue_pop(queue_t queue_){
    assert(queue_ != NULL && queue_->buf != NULL);
    void* data;
    if(queue_->oldest_item == NULL || queue_->oldest_item >= queue_->buf + queue_->size * queue_->element_size){
        data = queue_->buf;
        queue_->oldest_item = queue_->buf + queue_->element_size;
    }
    else{
        data = queue_->oldest_item;
        queue_->oldest_item += queue_->element_size;
    }
    return data;
}

void queue_push(queue_t queue_, const void* data){
    assert(queue_ != NULL && queue_->buf != NULL);
    if(queue_->newest_item == NULL || queue_->newest_item + queue_->element_size >= queue_->buf + queue_->size * queue_->element_size){
        queue_->newest_item = queue_->buf;
        memcpy(queue_->newest_item, data, queue_->element_size);
    }
    else{
        queue_->newest_item += queue_->element_size;
        memcpy(queue_->newest_item, data, queue_->element_size);
    }
}

void queue_free(queue_t queue_){
    free(queue_->buf);
}

int main(){
    struct queue my_queue;
    queue_create(&my_queue, 256, sizeof(int));
    int* src = malloc(256 * sizeof(int));
    int i;
    int j;
    int values_are_valid = 1;
    for(j = 0; j < 4; j++){ /*make sure we wrap around 3 times...*/
        for(i = 0; i<256; i++){
            src[i] = i;
            queue_push(&my_queue, &i);
        }
        
        for(i = 0; i<256; i++){
            int value_from_queue = *(int*)queue_pop(&my_queue);
            if( value_from_queue != src[i]){
                printf("error, %i != %i\n", value_from_queue, i);
                values_are_valid = 0;
            }
        }
    }
    
    if(values_are_valid){
        printf("all values are valid!!!\n");
    }
    
    queue_free(&my_queue);
    free(src);
    
    return 0;
}
