#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"

enum hashtable_op_result hashtable_element_insert(hashtable_element_t* element, uint64_t key, void* data){
    if(*element == NULL){
        *element = malloc(sizeof(struct hashtable_element));
        if(*element == NULL)
            return HASH_ALLOC_FAILURE;
        (*element)->key = key;
        (*element)->data = data;
        (*element)->next = NULL;
        return HASH_SUCCESS;
    }
    
    //handle collision
    hashtable_element_t* next = &((*element)->next);
    while(*next != NULL){
        if((*next)->key == key)
            return HASH_ALREADY_IN_TABLE;
        next = &((*next)->next);
    }
    *next =  malloc(sizeof(struct hashtable_element));
    if(*next == NULL){
        return HASH_ALLOC_FAILURE;
    }
    (*next)->key = key;
    (*next)->data = data;
    (*next)->next = NULL;
    
    return HASH_SUCCESS;
}

enum hashtable_op_result hashtable_element_remove(hashtable_element_t* element, uint64_t key){
    if(*element == NULL){
        return HASH_NOT_IN_TABLE;
    }
    
    hashtable_element_t prev = NULL;
    hashtable_element_t cur = *element;
    while(cur != NULL){
        if(cur->key == key){
            if(prev != NULL){
                prev->next = cur->next; //case where we remove a link after the beginning
            }
            else if(cur->next != NULL){
                *element = cur->next; //case where we remove the link at beginning
            }
            free(cur->data);
            free(cur);
            return HASH_SUCCESS;
        }
        prev = cur;
        cur = cur->next;
    }
    return HASH_NOT_IN_TABLE;
}

void* hashtable_element_get(hashtable_element_t element, uint64_t key){
    if(element == NULL){
        return NULL;
    }
    
    hashtable_element_t cur = element;
    while(cur != NULL){
        if(cur->key == key){
            return cur->data;
        }
        cur = cur->next;
    }
    return NULL;
}

void hashtable_element_delete(hashtable_element_t element){
    hashtable_element_t prev = NULL;
    hashtable_element_t cur = element;
    while(cur != NULL){
        prev = cur;
        cur = cur->next;
        free(prev->data);
        free(prev);
    }
}

hashtable_t hashtable_create(void){
    return malloc(sizeof(struct hashtable));
}

void hashtable_delete(hashtable_t table){
    int i;
    for(i = 0; i <= UINT8_MAX; ++i){
        hashtable_element_delete(table->elements[i]);
    }
    free(table);
}

enum hashtable_op_result hashtable_insert(hashtable_t table, uint64_t key, void* data){
    uint8_t hash = key & 0xff;
    return hashtable_element_insert(&(table->elements[hash]), key, data);
}

enum hashtable_op_result hashtable_remove(hashtable_t table, uint64_t key){
    uint8_t hash = key & 0xff;
    return hashtable_element_remove(&(table->elements[hash]), key);
}

void* hashtable_get(hashtable_t table, uint64_t key){
    uint8_t hash = key & 0xff;
    return hashtable_element_get(table->elements[hash], key);
}

int main(){
    hashtable_t table = hashtable_create();
    int* i = malloc(sizeof(int));
    *i = 12345;
    int* j = malloc(sizeof(int));
    *j = 54321;
    hashtable_insert(table, 0x00000000, i);
    hashtable_insert(table, 0x00000001, j);
    
    printf("i(12345) from hashtable %d\n", *(int*)hashtable_get(table, 0x00000000));
    printf("j(54321) from hashtable %d\n", *(int*)hashtable_get(table, 0x00000001));
    
    int* k = malloc(sizeof(int));
    *k = 11111;
    int* l = malloc(sizeof(int));
    *l = 22222;
    hashtable_insert(table, 0xffffff00, k);
    hashtable_insert(table, 0xffffff01, l);
    
    printf("after insert of k and l causing collisions with i and j...\n");
    printf("i(12345) from hashtable %d\n", *(int*)hashtable_get(table, 0x00000000));
    printf("j(54321) from hashtable %d\n", *(int*)hashtable_get(table, 0x00000001));
    printf("k(11111) from hashtable %d\n", *(int*)hashtable_get(table, 0xffffff00));
    printf("l(22222) from hashtable %d\n", *(int*)hashtable_get(table, 0xffffff01));
    
    printf("removing k and j...\n");
    hashtable_remove(table, 0xffffff00);
    hashtable_remove(table, 0x00000001);
    if(hashtable_get(table, 0xffffff00) != NULL || hashtable_get(table, 0x00000001) != NULL){
        printf("k and j should have been removed!!!\n");
    }
    
    printf("i(12345) from hashtable %d\n", *(int*)hashtable_get(table, 0x00000000));
    printf("l(22222) from hashtable %d\n", *(int*)hashtable_get(table, 0xffffff01));
    
    //run valgrind to check we do not leak!!!
    //valgrind --leak-check=full ./hashtable
    hashtable_delete(table);
    
    return 0;
}
