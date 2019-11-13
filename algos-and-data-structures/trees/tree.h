#ifndef TREE_H
#define TREE_H

#include<array>
#include<new>

template<typename T, int N>
struct binary_tree_node{
    binary_tree_node(){
        data = nullptr;
        for(auto& child: childs){
            child = nullptr;
        }
    }
    T* data;
    std::array<binary_tree_node<T, N>*, N> childs;
};

template<typename T, int N>
struct binary_tree{
    binary_tree(){
        depth = 0;
    }
    binary_tree_node<T, N> root_node;
    int depth;
};

template<typename T, int N>
binary_tree_node<T, N>* binary_tree_insert_internal(binary_tree_node<T, N>& node, T& data, int remaining_depth){
    if(node.data == nullptr){
        node.data = &data;
        return &node;
    }
    else if(remaining_depth < 1){ 
        return nullptr; 
    }
    else{
        for(auto& child: node.childs){
            if(child == nullptr){
                if(child = new binary_tree_node<T, N>){
                    child->data = &data;
                }
                return child;
            }
        }
        
        /*no nullptr in childs, do recursive calls*/
        for(auto& child: node.childs){
            binary_tree_node<T, N>* new_node;
            if(new_node = binary_tree_insert_internal(*child, data, remaining_depth - 1)){
                return new_node;
            }
        }
        
        /*will need to increase depth of the tree*/
        return nullptr;
    }
}

template<typename T, int N>
binary_tree_node<T, N>* binary_tree_insert(binary_tree<T, N>& root, T& data){
    binary_tree_node<T, N>* new_node;
    if(new_node = binary_tree_insert_internal(root.root_node, data, root.depth)){
        return new_node;
    }
    else{
        root.depth+=1;
        new_node = binary_tree_insert_internal(root.root_node, data, root.depth);
        if(new_node == nullptr){
            root.depth-=1; //probably failed because operator new returned nullptr because we dont have enough memory...
        }
        return new_node;
    }
}
#endif
