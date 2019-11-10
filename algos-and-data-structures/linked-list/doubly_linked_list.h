#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

struct list_node{
    void* data;
    struct list_node* prev;
    struct list_node* next;
};

typedef struct list_node* list_node_t;

void linked_list_append(list_node_t* head, void* data);
void linked_list_insert(list_node_t* head, int index, void* data);
void linked_list_remove(list_node_t* head, int index);
void linked_list_delete(list_node_t* head);

#endif
