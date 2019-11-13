#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "binary_tree.h"

static binary_tree_node_t binary_tree_insert_internal(binary_tree_node_t node, void* data, int remaining_depth){
    assert(node != NULL);
    if(node->data == NULL){
        node->data = data;
        return node;
    }
    else if(remaining_depth < 1){ 
        return NULL; 
    }
    else if(node->left == NULL){
        if(node->left = malloc(sizeof(struct binary_tree_node))){
            node->left->data = data;
            node->left->left = NULL;
            node->left->right = NULL;
        }
        return node->left;
    }
    else if(node->right == NULL){
        if(node->right = malloc(sizeof(struct binary_tree_node))){
            node->right->data = data;
            node->right->left = NULL;
            node->right->right = NULL;
        }
        return node->right;
    }
    else{
        binary_tree_node_t new_node;
        if(new_node = binary_tree_insert_internal(node->left, data, remaining_depth - 1)){
            return new_node;
        }
        else if(new_node = binary_tree_insert_internal(node->right, data, remaining_depth - 1)){
            return new_node;
        }
        else{
            return NULL;
        }
    }
}

void binary_tree_create(binary_tree_t root){
    assert(root != NULL);
    root->root_node.data = NULL;
    root->root_node.left = NULL;
    root->root_node.right = NULL;
    root->depth = 0;
}

binary_tree_node_t binary_tree_insert(binary_tree_t root, void* data){
    assert(root != NULL);
    binary_tree_node_t new_node;
    if(new_node = binary_tree_insert_internal(&root->root_node, data, root->depth)){
        return new_node;
    }
    else{
        root->depth+=1;
        new_node = binary_tree_insert_internal(&root->root_node, data, root->depth);
        return new_node;
    }
}

int main(){
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    struct binary_tree root;
    binary_tree_create(&root);
    binary_tree_insert(&root, &a);
    binary_tree_insert(&root, &b);
    binary_tree_insert(&root, &c);
    binary_tree_insert(&root, &d);
    return 0;
}
