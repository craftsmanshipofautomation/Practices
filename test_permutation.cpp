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

int main()
{
   vector<int> vec{1, 2, 3, 4, 5};
   auto r = permute1(vec, 5);
   print(r);
}