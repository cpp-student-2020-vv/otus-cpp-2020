#include "lib.h"

#include "gtest/gtest.h"

#include <sstream>

using namespace otus_cpp::unit1::task1;

TEST(test_version, test_valid_version) { ASSERT_TRUE(version() > 0); }

TEST(test_version, test_valid_greet) {
  // arrange
  int currentVersion = version();
  const std::string expectedOutput =
      "Version: " + std::to_string(currentVersion) + "\nHello, World!\n";
  std::ostringstream oss;

  // act
  otus_cpp::unit1::task1::greet_with_version(oss);

  // assert
  auto actualOutput = oss.str();
  ASSERT_EQ(expectedOutput, actualOutput);
}
