#include "ftf.h"
#include <vector>


MOCK_BEGIN

class Turtle
{
 public:
   virtual ~Turtle() {}
   virtual void Eat() = 0;
};

class MockTurtle : public Turtle
{
 public:
   MOCK_METHOD0(Eat, void());
};

TEST(M, m1)
{
   MockTurtle mt;
   EXPECT_CALL(mt, Eat()).Times(::testing::AtLeast(0));
}

TEST(M, compare_vector)
{
    std::vector<int> v{1, 2, 3};
    ASSERT_THAT(v, ::testing::ElementsAre(1, 2, 3));
}

MOCK_END