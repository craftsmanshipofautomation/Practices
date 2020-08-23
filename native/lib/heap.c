#include "libc.h"


int heap_height(int size)
{
   return log2(size) + 1;
}

int left_child(int i)
{
   return 2 * i;
}
int right_child(int i)
{
   return 2 * i + 1;
}

void max_heapify(int *arr, int size, int index)
{ 
   int lid = left_child(index);
   int rid = right_child(index);

   int largest; // record the largest index
   largest = index;
   if (lid <= size && arr[lid] > arr[index])
      largest = lid;
   if (rid <= size && arr[rid] > arr[largest])
      largest = rid;
   if (largest != index)
   {
      swap(&arr[largest], &arr[index]);
      max_heapify(arr, size, largest);
   }
}

void build_heap(int *arr, int size)
{
   int i;
   for (i = size /2 ; i >= 1; --i)
   {
      printf("------------ BEGIN ----------------\n");
      print_heap(arr, 10);      
      max_heapify(arr, size, i);
      print_heap(arr, 10);      
      printf("------------ END ----------------\n");      
   }
}


int is_leaf(int size, int index)
{
   if (index > size / 2)
   {
      return 1;
   }
   return 0;
}

