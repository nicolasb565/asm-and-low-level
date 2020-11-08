#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>

enum hashtable_op_result {HASH_SUCCESS, HASH_FAILURE, HASH_NOT_IN_TABLE, HASH_ALREADY_IN_TABLE, HASH_ALLOC_FAILURE};

struct hashtable_element{
    uint64_t key;
    void* data;
    struct hashtable_element* next;
};
typedef struct hashtable_element* hashtable_element_t;

enum hashtable_op_result hashtable_element_insert(hashtable_element_t* element, uint64_t key, void* data);
enum hashtable_op_result hashtable_element_remove(hashtable_element_t* element, uint64_t key);
void* hashtable_element_get(hashtable_element_t element, uint64_t key);
void hashtable_element_delete(hashtable_element_t element);

struct hashtable{
    struct hashtable_element* elements[UINT8_MAX + 1];
};
typedef struct hashtable* hashtable_t;

hashtable_t hashtable_create(void);
void hashtable_delete(hashtable_t);
enum hashtable_op_result hashtable_insert(hashtable_t table, uint64_t key, void* data);
enum hashtable_op_result hashtable_remove(hashtable_t table, uint64_t key);
void* hashtable_get(hashtable_t table, uint64_t key);

#endif
