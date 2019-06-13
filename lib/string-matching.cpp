#include "libcxx.h"


vector<size_t> native_pattern_search(const std::string& text, const std::string& pat)
{
   size_t i = 0;
   size_t tsize = text.size();
   size_t psize = pat.size();
   vector<size_t> ret;
   for (i = 0; i < tsize - psize + 1; ++i)
   {
      if (0 == text.compare(i, psize, pat))
         ret.push_back(i);
   }
   return ret;
}

vector<int> compute_kmp_pi(const std::string& pat)
{
   vector<int> pi(pat.size(), 0);
   pi[0] = 0; // one element sub-string produces nothing
   size_t k = 0; // k is the length of overlapped prefix and suffix,
              // the element right next to that prefix happens to be k
   for (size_t q = 1; q < pat.size(); ++q)
   {
      while (k > 0 && pat[q] != pat[k])
      {
         k = pi[k-1];
      }
      if (pat[q] == pat[k])
         ++k;
      pi[q] = k;
   }
   return pi;
}


vector<size_t> kmp_search(const std::string& text, const std::string& pat)
{
   vector<size_t> ret;
   vector<int> pi = compute_kmp_pi(pat);
   size_t curr, k = 0, t, p;
   bool is_matched;   
   for (curr = 0; curr < text.size();)
   {
      is_matched = true;
      for (; k < pat.size(); ++k, ++curr)
      {
         if (!(curr < text.size()) || text[curr] != pat[k])
         {
            is_matched = false;
            break;
         }
      }
      if (is_matched)
      {
         ret.push_back(curr - pat.size());
      }
      k = pi[k-1];
      curr -= k;         
   }
   return ret;
}