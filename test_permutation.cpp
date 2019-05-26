#include "libcxx.h"
using namespace std;

void print(vector<vector<int>> &vec)
{
   for (auto &i : vec)
   {
      for (auto &j : i)
      {
         cout << j << " ";
      }
      cout << endl;
   }
}

void print(vector<int> &vec)
{
   for (auto &i : vec)
   {
         cout << i << " ";
   }
   cout << endl;   
}

int main()
{
   //vector<int> vec{1, 2, 3};
   //auto r = PermuteR(vec, 2);
   //print(r);
   
   vector<int> vec{1, 2, 3, 4};
   //auto r = Permute(vec, 3);
   //print(r);
   auto r = LexicographicalPermutatation(vec);
   print(r);
   
   
   
}