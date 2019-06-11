#include "libcxx.h"

using namespace std;

TEST_BEGIN

TEST(STRING_MATCHING, 1)
{
   string text = "abababab";
   string pat = "ab";
   auto vec = native_pattern_search(text, pat);
   vector<size_t> answer{0, 2, 4, 6};
   expect_eq(vec, answer);
}

TEST(STRING_MATCHING, 2)
{
   string text = "aaabbaa";
   string pat = "bb";
   auto vec = native_pattern_search(text, pat);
   vector<size_t> answer{3};
   expect_eq(vec, answer);
}

TEST(STRING_MATCHING, 3)
{
   string pattern = "ababaca";
   vector<int> expected{0, 0, 1, 2, 3, 0, 1};
   auto r = compute_kmp_pi(pattern);
   expect_eq(expected, r);
}

TEST(STRING_MATCHING, 4)
{
   string text = "abababab";
   string pat = "ab";
   auto r = kmp_search(text, pat);
   vector<size_t> expected{0, 2, 4, 6};
   expect_eq(r, expected);
}

TEST(STRING_MATCHING, 5)
{
   string text = "abababab";
   string pat = "aba";
   auto r = kmp_search(text, pat);
   vector<size_t> expected{0, 2, 4};
   expect_eq(r, expected);
}

TEST_END