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
   
   //vector<int> vec{1, 2, 3, 4};
   //auto r = Permute(vec, 3);
   //print(r);
   //auto r = LexicographicalPermutatation(vec);
   //print(r);
   
   vector<int> vec{0, 1, 2, 3, 4};
   do
   {
      print(vec, 3);
   }
   while(NextPermutation(vec, 3));
   
   
   
}

/*
0 1 2 
0 1 3 
0 1 4 
0 2 1 
0 2 3 
0 2 4 
0 3 1 
0 3 2 
0 3 4 
0 4 1 
0 4 2 
0 4 3 
1 0 2 
1 0 3 
1 0 4 
1 2 0 
1 2 3 
1 2 4 
1 3 0 
1 3 2 
1 3 4 
1 4 0 
1 4 2 
1 4 3 
2 0 1 
2 0 3 
2 0 4 
2 1 0 
2 1 3 
2 1 4 
2 3 0 
2 3 1 
2 3 4 
2 4 0 
2 4 1 
2 4 3 
3 0 1 
3 0 2 
3 0 4 
3 1 0 
3 1 2 
3 1 4 
3 2 0 
3 2 1 
3 2 4 
3 4 0 
3 4 1 
3 4 2 
4 0 1 
4 0 2 
4 0 3 
4 1 0 
4 1 2 
4 1 3 
4 2 0 
4 2 1 
4 2 3 
4 3 0 
4 3 1 
4 3 2
*/