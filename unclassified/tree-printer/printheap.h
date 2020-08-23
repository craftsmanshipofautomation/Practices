#pragma once

typedef struct heap_string
{
   int height;
   int span;
   int r, p2, p41, p42;
   char **lines;
   int empty;
} heap_string_t;
void print_heap(int *arr, int size);

void hstr_print(heap_string_t hstr);
void hstr_free(heap_string_t hstr);
heap_string_t hstr_leaf(int *arr, int size, int index);
void fill_with_space(char *arr, int size);

heap_string_t hstr_merge(
   int *arr,
   int size,
   int index,
   heap_string_t left,
   heap_string_t right
);

heap_string_t hstr_string(int *arr, int size, int index);

heap_string_t make_empty();
