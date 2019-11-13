#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tree.h"

int main(){
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    binary_tree<int, 2> tree;
    binary_tree_insert(tree, a);
    binary_tree_insert(tree, b);
    binary_tree_insert(tree, c);
    binary_tree_insert(tree, d);
    return 0;
}
