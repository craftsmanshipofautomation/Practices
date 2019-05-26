#include "libcxx.h"
using namespace std;

// https://sites.google.com/site/hannuhelminen/next_combination
// the implementations is a little different, may be easier to understand
template <typename P>
bool NextCombination(P &begin, P &mid, P &end)
{
   if (begin == end || begin + 1 == end)
      return false;

   auto head_pos = mid;
   auto tail_pos = end;
   --head_pos;
   --tail_pos;

   // ------| |---------| |--------------------| |---------
   //        hp         mid                    tp
   // move until *head_pos < *tail_pos
   while (head_pos != begin && !(*head_pos < *tail_pos))
      --head_pos;
   // reach the last combination
   if (head_pos == begin && !(*head_pos < *tail_pos))
      return false;

   // if there is a valid head_pos then there is always
   // a valid tail_pos, at least head_pos < *(end - 1)
   while (!(tail_pos < mid) && *tail_pos > *head_pos)
      --tail_pos;
   ++tail_pos;

   iter_swap(head_pos, tail_pos);
   disjoint_rotate(head_pos + 1, mid, tail_pos + 1, end);

   return true;
}

bool NextCombination(vector<int> &vec, int N)
{
   auto b = vec.begin();
   auto m = b + N;
   auto e = vec.end();
   return NextCombination(b, m, e);
}

/*
刷新的机制
将输入分为 6 段
A x A' | B y B'
初次交换后
A y A' | B x B'
更新 x 的时间点是 A' 达到最大组合的时候
B‘ > y, 当 x 被换成 y 的时候，由于 | 的左边必须是升序，所以 y 的右边不能小于 y
所以不能是 B
不能是 A', 所以只能是 B'

所以可能是 A’与 B‘ 之间的交换，仅当它们长度一样
如果len(A') < len(B'), 则取 B‘的一个 prefix放在原 A' 位置
将 B’ 的一个 suffix + A‘ 放在原 B' 位置
如果 len(A') > len(B'), 将 B‘ 和 A’ 的 prefix 放在原 A’ 位置
将 A‘ 的 suffix 放在原 B’ 位置
*/