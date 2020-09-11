#include "libcxx.h"
#include "tree.hpp"

TEST_BEGIN

using namespace std;

TEST(TREE, 1)
{
    Tree<int, BinaryTreeNode<int>> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(12);
    tree.insert(6);    
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(18);
    tree.insert(11);    
    tree.insert(4);        
    cout << tree.to_string();

/*
  5 --[r]-- 10 --[r]-- 12 --[r]-- 18
                          --[l]-- 11
               --[l]--  6
    --[l]--  2 --[r]--  3 --[r]--  4
               --[l]--  1
*/

}



TEST_END