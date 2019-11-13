#ifndef BINARY_TREE_H
#define BINARY_TREE_H
struct binary_tree_node{
    void* data;
    struct binary_tree_node* left;
    struct binary_tree_node* right;
};
typedef struct binary_tree_node* binary_tree_node_t;

struct binary_tree{
    struct binary_tree_node root_node;
    int depth;
};
typedef struct binary_tree* binary_tree_t;

void binary_tree_create(binary_tree_t root);
binary_tree_node_t binary_tree_insert(binary_tree_t root, void* data);
#endif
