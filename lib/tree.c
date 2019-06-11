#include "libc.h"

binary_tree* binary_tree_node_allocate(int value)
{
   binary_tree* node = malloc(sizeof(binary_tree));
   node->value = value;
   node->left = NULL;
   node->right = NULL;
   return node;
}

binary_tree* binary_tree_create(int *arr, int size)
{
   if (size == 0)
      return NULL;
   if (size == 1)
      return binary_tree_node_allocate(arr[0]);
   int i;
   binary_tree * root, *curr;
   for (i = 0; i < size; ++i)
   {
      curr = binary_tree_node_allocate(arr[i]);
   }      
   return NULL;
}


void binary_tree_destroy(binary_tree** t)
{
   
}