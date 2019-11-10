#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "linked_list.h"

static void print_list(list_node_t head){
    list_node_t p;
    for(p = head; p != NULL; p = p->next){
        printf("%i -> ", *(int*)p->data);
    }
    printf("end \n");
}

void linked_list_append(list_node_t node, void* data){
    if(node == NULL){ return; }
    list_node_t new_tail = malloc(sizeof(struct list_node));
    if(new_tail){
        new_tail->next = NULL;
        new_tail->data = data;
    }
    
    list_node_t prev = NULL;
    list_node_t cur = node;
    while(cur != NULL){
        prev = cur;
        cur = cur->next;
    }
    if(prev != NULL){
        prev->next = new_tail;
    }
}

void linked_list_insert(list_node_t* head, int index, void* data){
    list_node_t new_node = malloc(sizeof(struct list_node));
    if(new_node != NULL){
        new_node->data = data;
        if(index <= 0){
            new_node->next = *head;
            *head = new_node;
        }
        else{
            list_node_t prev = NULL;
            list_node_t cur = *head;
            int i = 0;
            for(; cur!= NULL && i <= index; i++){
                prev = cur;
                cur = cur->next;
            }
            prev->next = new_node;
            if(cur != NULL){
                new_node->next = cur;
            }
        }
    }
}

void linked_list_remove(list_node_t* head, int index){
    /*TODO*/
}

void linked_list_delete(list_node_t* head){
    list_node_t cur = *head;
    list_node_t prev = NULL;
    while(cur != NULL){
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    *head = NULL;
}

int main(void){
    int a = -1;
    int b = 0;
    int c = 1;
    int d = 2;
    int e = 1111;
    
    list_node_t list = NULL;
    linked_list_insert(&list, 0, &b);
    linked_list_insert(&list, -1, &a);
    linked_list_insert(&list, 2, &c);
    linked_list_insert(&list, 3, &c);
    linked_list_insert(&list, 4, &d);
    linked_list_insert(&list, 1000, &d);
    linked_list_append(list, &e);
    print_list(list);
    
    linked_list_delete(&list);
    assert(list == NULL);
    return 0;
}
