#pragma once

typedef struct binary_tree_
{
   int value;
   struct binary_tree_ * left;
   struct binary_tree_ * right;   
} binary_tree;

binary_tree* binary_tree_node_allocate(int value);
binary_tree* binary_tree_create(int *arr, int size);
void binary_tree_destroy(binary_tree**);


