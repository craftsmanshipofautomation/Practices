/*
given a group of closed intervals
find an interval that is overlapped by most intervals...

for example
----|------|----------
    a      b 
---|----------|
   c          d
-----|---|-------------
     e   f
     
the result is [e, f]
*/

#include "libc.h"


typedef struct TIME_
{
   int time;
   int is_in;
} TIME;

void generate_random_interval(int *lower, int* upper)
{
   *lower = rand() % 50;
   *upper = *lower + rand() % 50 + 3;
}

void generate_multiple_intervals(int* lw_arr, int *up_arr, int size)
{
   int i, j;
   int lw, up;
   for (i = 0; i < size; ++i)
   {
      generate_random_interval(&lw, &up);
      //printf("[%d, %d]\n", lw, up);
      for(j = 0; j < lw-1; ++j)
         printf("-");
      printf("%d", lw);
      for(j = lw+1; j < up-1; ++j)
         printf("-");
      printf("%d", up);
      for(j = up+1; j < 100; ++j)
         printf("-");
      printf("\n");
      lw_arr[i] = lw;
      up_arr[i] = up;
   }
}

void create_time_array(TIME *arr, int *lw_arr, int *up_arr, int size)
{
   int i;
   for (i = 0; i < size; ++i)
   {
      arr->time = lw_arr[i];
      arr->is_in = 1;
      ++arr;
      arr->time = up_arr[i];
      arr->is_in = 0;
      ++arr;
   }
}

int less_than(TIME *t1, TIME *t2)
{
   if (t1->time < t2->time)
      return 1;
   else if (t1->time == t2->time)
   {
      if (t1->is_in < t2->is_in)
         return 1;
   }
   return 0;
}

void TIME_swap(TIME* t1, TIME *t2)
{
   swap(&(t1->time), &(t2->time));
   swap(&(t1->is_in), &(t2->is_in));            
}

int TIME_partition(TIME *arr, int start, int end)
{
   TIME *pivot = arr + end;
   int i = start-1, j = start;
   while (j < end)
   {
      if (less_than(arr + j, pivot))
      {
         ++i;
         TIME_swap(arr + j, arr + i);
      }
      ++j;
   }
   TIME_swap(arr + end, arr + i + 1);
   return i + 1;
}

void TIME_quicksort_r(TIME *arr, int start, int end)
{
   int p;
   while (start < end)
   {
      p = TIME_partition(arr, start, end);
      TIME_quicksort_r(arr, start, p - 1);
      start = p + 1;
   }
}

void TIME_quicksort(TIME *arr, int size)
{
   TIME_quicksort_r(arr, 0, size - 1);
}

void TIME_ARRAY_DUMP(TIME *arr, int size)
{
   int i;
   for (i = 0; i < size; ++i)
   {
      printf("%d[%d], ", arr[i].time, arr[i].is_in);
   } 
   printf("\n");
}

// At the moment, it only reture the first occurence of maximum overlapped area
// because there is no vector in C!
void traverse(TIME *arr, int size)
{
   int i, level = 0, max_level = 0, entrance, exit;
   for (i = 0; i < size; ++i)
   {
      if (arr[i].is_in)
      {
         ++level;
         if (level > max_level)
            max_level = level;
            entrance = i;
            for (exit = entrance+1; ;++exit)
            {
               if (arr[exit].is_in == 0)
                  break;
            }
      }
      else
         --level;
   }
   printf("the most overlapped range of time is [%d, %d], level: %d\n", 
      arr[entrance].time, arr[exit].time, max_level);
}

int main()
{
   static int lw[10];
   static int up[10];
   static TIME arr[20];      
   srand (time(NULL));
   generate_multiple_intervals(lw, up, 10);
   create_time_array(arr, lw, up, 10);
   TIME_quicksort(arr, 20);
   traverse(arr, 20);
   
}