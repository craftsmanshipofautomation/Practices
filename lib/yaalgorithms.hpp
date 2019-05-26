template<class P>
void ya_rotate(P&& first, P&& first2, P&& last)
{
   using std::iter_swap;
   if (first == first2) return;
   if (first2 == last) return;
   
   
   auto next_read = first;
   auto read = first2;
   auto write = first;
   while (read != last)
   {
      if (write == next_read)
         next_read = read;
      lzlog(*write, d);
      lzlog(*read, d);      
      iter_swap(write++, read++);
   }
  ya_rotate(write, next_read, last);
}


template<class P>
void disjoint_rotate(P begin1, P end1, P begin2, P end2)
{
   if (begin1 == end1 || begin2 == end2)
      return;

   auto size1 = end1 - begin1;
   auto size2 = end2 - begin2;   

   if (size1 == size2)
   {
      if (size1 == 1)
         iter_swap(begin1, begin2);
      else
         swap_ranges(begin1, end1, begin2);
      return;
   }
   using std::rotate;
   rotate(end1, begin2, end2);
   rotate(begin1, end1, end1 + size2);
   rotate(end1, end1+size2, end2);
}
