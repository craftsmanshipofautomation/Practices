#ifndef PRACTICES_LIBC_H
#define PRACTICES_LIBC_H

#include "log.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tgmath.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

void merge_sort(int *arr, int size);
void bubble_sort(int *arr, int size);
void heap_sort(int *arr, int size);
void insert_sort(int *arr, int size);
void heap_sort(int *arr, int size);
void print_heap(int *arr, int size);
void quicksort(int *arr, int size);
void select_sort(int *arr, int size);

void swap(int *, int *);
void swapc(char *, char *);
void arrncpy(int *dest, int *src, int size);
void copychars(char *dest, char *src, int size);
int number_span(int n);


typedef struct heap_string
{
   int height;
   int span;
   int r, p2, p41, p42;
   int empty;   
   char **lines;
} heap_string_t;
void hstr_print(heap_string_t hstr);
void hstr_free(heap_string_t hstr);
heap_string_t hstr_leaf(int *arr, int size, int index);
void fill_with_space(char *arr, int size);
heap_string_t hstr_merge(
    int *arr,
    int size,
    int index,
    heap_string_t left,
    heap_string_t right);
heap_string_t hstr_string(int *arr, int size, int index);
heap_string_t make_empty();
int heap_height(int size);
void max_heapify(int *arr, int size, int index);
void build_heap(int *arr, int size);
int left_child(int i);
int right_child(int i);
int is_leaf(int size, int index);





#endif