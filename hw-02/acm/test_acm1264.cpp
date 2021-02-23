#include <sstream>

#include "gtest/gtest.h"

#include "acm1264.h"

// https://acm.timus.ru/problem.aspx?space=1&num=1877
// acceptance:
//  https://acm.timus.ru/status.aspx?space=1&num=1264&author=312959
TEST(test_acm1264, task_1264_knownInput_expectedResult) {
  // arrange
  int array_size_N = 3;
  int fn_range_M = 1;
  int expected_line_count = 6;

  // act & assert
  ASSERT_EQ(expected_line_count, task_1264(array_size_N, fn_range_M));
}

TEST(test_acm1264, task_1264_io_wrapper__knownInput_expectedResult) {
  // arrange
  std::istringstream in1{"3 1\n"};
  std::string expected_out1{"6\n"};
  std::ostringstream actual_out1;

  // act
  task_1264_io_wrapper(in1, actual_out1);

  // assert
  ASSERT_EQ(expected_out1, actual_out1.str());
}
