#include <stdio.h>
#include <stdlib.h>

typedef enum OPERATION { ADD, MINUS, DIV, MUL, OPERATION_NUM } OPERATION_t;
char OPEARTION_MAP[4] = {'+', '-', '/', '*'};

int by_operation(int curr, int factor, int operation, int *next) {
   // if factor * next = curr, next = curr / factor;
   if (operation == MUL) {
      if (factor == 0)
         return 0;
      if (curr % factor)
         return 0;
      if (factor > curr)
         return 0;
      *next = curr / factor;
      return 1;
   }
   // if factor + next = curr; next = curr - factor
   if (operation == ADD) {
      *next = curr - factor;
      return 1;
   }
   // if factor / next = curr; next = factor / curr
   if (operation == DIV) {
      if (curr == 0)
         return 0;
      if (factor % curr)
         return 0;
      *next = factor / curr;
      return 1;
   }
   // if factor - next = curr; next = factor - curr;
   if (operation == MINUS) {
      *next = factor - curr;
      return 1;
   }
}

void swap(int *a, int *b) {
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;
}

void print_result(int *arr, int size, int *record) {
   int i, op;
   int close = 0;
   for (i = 0; i < size - 1; ++i) {
      op = record[i];
      printf("%d %c ", arr[i], OPEARTION_MAP[op]);
      printf("( ");
      ++close;
   }
   printf("%d ", arr[i]);
   for (i = 0; i < close; ++i) {
      printf(") ");
   }
   printf("\n");
}

void backtrace(int *arr, int size, int offset, int expected, int *record) {
   int i, j, next_expected;
   if (offset == size - 1) {
      if (expected == arr[offset]) {
         print_result(arr, size, record);
      }
      return;
   }
   for (i = offset; i < size; ++i) {
      swap(arr + offset, arr + i);
      for (j = ADD; j < OPERATION_NUM; ++j) {
         if (by_operation(expected, arr[offset], j, &next_expected)) {
            record[offset] = j;
            backtrace(arr, size, offset + 1, next_expected, record);
         }
      }
      swap(arr + offset, arr + i);
   }
}

void calculate(int *arr, int size, int expected) {
   int record[size - 1];
   printf("expect %d\n", expected);
   backtrace(arr, size, 0, expected, record);
}

int main(int argc, char **argv) {
   int expected = atoi(argv[1]);
   int size = atoi(argv[2]);
#define BEGIN 3
   if (argc != BEGIN + size)
      exit(-1);
   int arr[size];
   int i;
   for (i = BEGIN; i < argc; ++i) {
      arr[i - BEGIN] = atoi(argv[i]);
   }
   calculate(arr, size, expected);
   return 0;
}