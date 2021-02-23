#include <sstream>

#include "gtest/gtest.h"

#include "acm1877.h"

// https://acm.timus.ru/problem.aspx?space=1&num=1877
//acceptance:
// https://acm.timus.ru/status.aspx?space=1&num=1877&author=312959
TEST(test_acm1877, task_1877_knownInput_expectedResult) {
  // arrange
  int input1[] = {1, 0};
  bool expected_result_1 = false;

  int input2[] = {2, 1};
  bool expected_result_2 = true;

  // act & assert
  ASSERT_EQ(expected_result_1, task_1877(input1[0], input1[1]));
  ASSERT_EQ(expected_result_2, task_1877(input2[0], input2[1]));
}

TEST(test_acm1877, task_1877_io_wrapper__knownInput_expectedResult) {
  // arrange
  std::istringstream in1{"0001\n0000"};
  std::string expected_out1{"no\n"};
  std::ostringstream actual_out1;

  std::istringstream in2{"0002\n0001"};
  std::string expected_out2{"yes\n"};
  std::ostringstream actual_out2;

  // act
  task_1877_io_wrapper(in1, actual_out1);
  task_1877_io_wrapper(in2, actual_out2);

  // assert
  ASSERT_EQ(expected_out1, actual_out1.str());
  ASSERT_EQ(expected_out2, actual_out2.str());
}
