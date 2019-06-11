#ifndef PRACTICES_LIBCXX_H
#define PRACTICES_LIBCXX_H

#include "log.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <bits/stdc++.h>
#include <gtest/gtest.h>


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

#include "printer.hpp"
#include "yaalgorithms.hpp"
#include "gtest.hpp"
#include "string-matching.hpp"

#endif