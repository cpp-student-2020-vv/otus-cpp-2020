#include <sstream>

#include "gtest/gtest.h"

#include "acm1409.h"

//ACM passed result:
//https://acm.timus.ru/status.aspx?space=1&num=1409&author=312959

TEST(test_acm1409, task_1409_knownInput_expectedResult) {
  int res1, res2;
  task_1409(4, 7, res1, res2);
  ASSERT_EQ(6, res1);
  ASSERT_EQ(3, res2);
}

TEST(test_acm1409, task_1409_io_wrapper__knownInput_expectedResult) {
  int res1, res2;
  std::istringstream in{"4 7"};
  std::ostringstream expected_stream;
  std::string expected_out{"6 3\n"};
  std::ostringstream actual_out;

  task_1409_io_wrapper(in, actual_out);

  ASSERT_EQ(expected_out, actual_out.str());
}
