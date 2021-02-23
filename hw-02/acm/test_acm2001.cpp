#include <sstream>

#include "gtest/gtest.h"

#include "acm2001.h"

// https://acm.timus.ru/problem.aspx?space=1&num=2001
// acceptance:
// https://acm.timus.ru/status.aspx?space=1&num=2001&author=312959
TEST(test_acm2001, task_2001_knownInput_expectedResult) {
  // arrange
  std::vector<int> a_1 = {1, 2, 0};
  std::vector<int> b_1 = {2, 1, 3};
  int expected_a = 1;
  int expected_b = 1;
  int actual_a, actual_b;

  // act
  task_2001(a_1, b_1, actual_a, actual_b);

  // assert
  ASSERT_EQ(expected_a, actual_a);
  ASSERT_EQ(expected_b, actual_b);
}

TEST(test_acm2001, task_2001_io_wrapper__knownInput_expectedResult) {
  // arrange
  std::istringstream in1{"1 2\n2 1\n0 3\n"};
  std::string expected_out1{"1 1\n"};
  std::ostringstream actual_out1;

  // act
  task_2001_io_wrapper(in1, actual_out1);

  // assert
  ASSERT_EQ(expected_out1, actual_out1.str());
}
