#include <sstream>

#include "gtest/gtest.h"

#include "acm1787.h"

// https://acm.timus.ru/problem.aspx?space=1&num=1787
//acceptance:
// https://acm.timus.ru/status.aspx?space=1&num=1787&author=312959
TEST(test_acm1787, task_1787_knownInput_expectedResult) {
  // arrange
  int tpm_1 = 5;
  int minutes_count_1 = 3;
  std::vector<int> arrivals_1 = {6, 7, 2};
  int expected_queue_size_1 = 0;

  int tpm_2 = 5;
  int minutes_count_2 = 3;
  std::vector<int> arrivals_2 = {20, 0, 0};
  int expected_queue_size_2 = 5;

  // act & assert
  ASSERT_EQ(expected_queue_size_1, task_1787(tpm_1, minutes_count_1, arrivals_1));
  ASSERT_EQ(expected_queue_size_2, task_1787(tpm_2, minutes_count_2, arrivals_2));
}

TEST(test_acm1787, task_1787_io_wrapper__knownInput_expectedResult) {
  // arrange
  std::istringstream in1{"5 3\n6 7 2\n"};
  std::string expected_out1{"0\n"};
  std::ostringstream actual_out1;

  std::istringstream in2{"5 3\n20 0 0"};
  std::string expected_out2{"5\n"};
  std::ostringstream actual_out2;

  // act
  task_1787_io_wrapper(in1, actual_out1);
  task_1787_io_wrapper(in2, actual_out2);

  // assert
  ASSERT_EQ(expected_out1, actual_out1.str());
  ASSERT_EQ(expected_out2, actual_out2.str());
}
