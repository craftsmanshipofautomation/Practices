#include "libcxx.h"

TEST_BEGIN

template<typename T>
void F(T&& t)
{
   lzlog(1, d);
}


TEST(DSFS, template_universal_type)
{
   F(1+1);
}

TEST(DSFS, vec_comp3)
{
   vector<int> v1{1, 2, 3, 4, 5};
   vector<int> v2{1, 2, 3, 4, 5};
   expect_eq(v1, v2);
}

TEST(DSFS, vec_comp)
{
   vector<int> v1{1, 2, 3, 4, 5};
   vector<int> v2{1, 2, 3, 4, 6};
   expect_eq(v1, v2);
}


TEST_END