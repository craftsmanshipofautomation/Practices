#ifndef PRACTICES_LIBCXX_H
#define PRACTICES_LIBCXX_H

#include "log.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include <fstream>
#include <queue>
#include <stack>

using std::vector;
using std::list;

vector<vector<int>> PermuteR(vector<int> nums, int N);
vector<vector<int>> Permute(vector<int> nums, int N);
list<list<int>> PermuteI(list<int> nums, int N);
vector<vector<int>> LexicographicalPermutatation(vector<int> nums);
vector<vector<int>> Combination(vector<int> nums, int k);
bool NextPermutation(vector<int> &vec);
bool NextPermutation(vector<int> &vec, int k);
bool NextCombination(vector<int> &vec, int N);

template<class P>
void ya_rotate(P&& first, P&& first2, P&& last);
template<class P>
void disjoint_rotate(P begin1, P end1, P begin2, P end2);

template<typename T>
void print(const T& t, bool newline = true);
template<typename T>
void print(const T& t, int N, bool newline = true);


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* CreateListNodeFromVector(vector<int> nums);
void PrintListNode(ListNode*);
void CleanListNode(ListNode*);

// poisonously slow but convinient
#include "printer.hpp"
#include "yaalgorithms.hpp"
#include "gtest.hpp"
#include "string-matching.hpp"
#include "encoding.h"
#include "tree.hpp"
#include "exceptions.h"
#include "csapp.h"
#include "socket.h"
#include "tcp.h"

#include "graph.h"


using std::swap;

#endif