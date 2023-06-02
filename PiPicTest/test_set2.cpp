
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(pipic_test_suite, pipic_test_set2) {
  int ret = 8;

  EXPECT_EQ(ret, 8);
  ASSERT_THAT(0, Eq(0));
}
