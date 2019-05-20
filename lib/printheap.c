#include "libc.h"


void hstr_print(heap_string_t hstr)
{
   int i;
   for (i = 0; i < hstr.height; ++i)
      printf("%s\n", hstr.lines[i]);
}

void hstr_free(heap_string_t hstr)
{
   int i;
   for (i = 0; i < hstr.height; ++i)
      free(hstr.lines[i]);
   free(hstr.lines);
}

heap_string_t hstr_leaf(int *arr, int hsize, int index)
{
   heap_string_t hst;
   if (is_leaf(hsize, index))
      {
         hst.height = 1;
         hst.span = number_span(arr[index]) + 1;
         hst.lines = malloc(sizeof(char *) * 1);
         hst.lines[0] = malloc(sizeof(char) * hst.span);
         snprintf(hst.lines[0], hst.span, "%d", arr[index]);
         // the trailing space does not count
         hst.p2 = (hst.span - 1 - 1)/ 2;
         hst.r = hst.p2;
         hst.empty = 0;
      }
   return hst;
}

heap_string_t hstr_string(int *arr, int hsize, int index)
{
   if (index > hsize)
      return make_empty();
   if (is_leaf(hsize, index))
      return hstr_leaf(arr, hsize, index);

   int l = index * 2;
   int r = index * 2 + 1;

   heap_string_t hl = hstr_string(arr, hsize, l);
   heap_string_t hr = hstr_string(arr, hsize, r);
   return hstr_merge(arr, hsize, index, hl, hr);
}


void fill_with_space(char *arr, int hsize)
{
   int i;
   for (i = 0; i < hsize; ++i)
      {
         arr[i] = ' ';
      }
}

heap_string_t hstr_merge(int *arr, int hsize, int index,
                               heap_string_t left,
                               heap_string_t right)
{
   int extra_gap = 0; // make it symmetrical
   heap_string_t p;

   int max_depth = MAX(left.height, right.height);
   p.height = max_depth + 4;

   // |0, l.span-2|
   // |l.span-1|
   // |l.span, l.span + r.span-2 |
   // |l.span + r.span -1 |
   //   (r)xxxxxxxxxxxxxxxxxxxxx
   //                  |(p2)
   //      ----------------------------
   //      |(p41)                   |p(42)
   // ^--------|x| ^extra_gap$   ^--------|x|
   p.p41 = left.p2;
   p.p42 = right.p2 + left.span;
   p.p2 = (p.p41 + p.p42) / 2;
   int p_span = number_span(arr[index]);
   int r = p.p2 - (p_span-1) / 2;
   p.r = r < 0 ? 0 : r;
   p.r += extra_gap;
   // r+p_span-1 is the last, the length is r+p_span, must plus one
   // for a gap
   p.span = MAX(p.r + p_span + 1, left.span + right.span + extra_gap);

   int even_underscore = (p.p42 - p.p41 + 1) % 2 == 0;
   if (even_underscore)
   {
      extra_gap = 1;
      p.p42 += extra_gap;
      p.r   += extra_gap;
      p.p2  += extra_gap;
      p.span+= extra_gap;
   }

   // new lines
   p.lines = malloc(sizeof(char *) * p.height);
   // fill with space
   int i;
   for (i = 0; i < p.height; ++i)
      {
         p.lines[i] = malloc(sizeof(char) * p.span);
         fill_with_space(p.lines[i], p.span);
      }
   // root
   snprintf(p.lines[0] + p.r, p.span, "%d", arr[index]);
   p.lines[0][p.r+p_span] = ' ';
   // p2
   p.lines[1][p.p2] = '|';
   //
   int p42;
   if (right.empty)
      p42 = p.p2 + 1;
   else
      p42 = p.p42 + 1;
   for (i = p.p41; i < p42; ++i)
   {
      p.lines[2][i] = '-';
   }

   // p41/2
   p.lines[3][p.p41] = '|';
   if (!right.empty) p.lines[3][p.p42] = '|';


   int j;
   char *line;
   for (i = 4, j = 0; i < p.height; ++i, ++j)
      {
         line = p.lines[i];
         if (j < left.height)
            {
               copychars(line, left.lines[j], left.span);
               line[left.span-1] = ' ';
            }
         if (j < right.height)
         {
            copychars(line + left.span + extra_gap, right.lines[j], right.span);
            line[left.span + right.span + extra_gap -1] = ' ';
         }
      }

   // release
   hstr_free(left);
   hstr_free(right);

   p.empty = 0;
   return p;

}

void print_heap(int *arr, int hsize)
{
   heap_string_t final = hstr_string(arr, hsize, 1);
   int i;
   char *line;
   for (i = 0; i < final.height; ++i)
   {
      line = final.lines[i];
      line[final.span-1] = '\0';
      printf("%s\n", line);
   }
   hstr_free(final);
}

heap_string_t make_empty()
{
   heap_string_t h;
   memset(&h, 0, sizeof(heap_string_t));
   h.empty = 1;
   return h;
}