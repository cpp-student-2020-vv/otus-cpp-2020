#include <sstream>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

#include "../ip_input_adapter.h"

using namespace otus_cpp::unit1::task2;

TEST(test_ip_input_adapter, validate_line__invalidLine__exThrown) {
  // arrange
  const std::string input_invalid_line = "foo\tfoo2\tfoo3\t\n";

  // act && assert
  try {
    Ip_input_adapter::validate_line(input_invalid_line);
    FAIL() << "Expected:: std::logic_error";
  } catch (std::logic_error const& err) {
    EXPECT_STREQ(
        "invalid argument: Input string [foo\tfoo2\tfoo3\t\n] does not match "
        "regex!",
        err.what());
  }
}

TEST(test_ip_input_adapter, validate_line__emptyLine__exThrown) {
  // arrange
  const std::string input_empty_line;

  // act && assert
  try {
    Ip_input_adapter::validate_line(input_empty_line);
    FAIL() << "Expected:: std::logic_error";
  } catch (std::logic_error const& err) {
    EXPECT_STREQ("invalid argument: Input string is empty!", err.what());
  }
}

TEST(test_ip_input_adapter, validate_line__validLine__noEx) {
  // arrange
  const std::string input_valid_line = "127.0.0.1\tfoo\tfoo2";

  // act && assert
  EXPECT_NO_THROW({ Ip_input_adapter::validate_line(input_valid_line); });
}

// validate_address_str
TEST(test_ip_input_adapter, validate_address_str__invalidAddr__exThrown) {
  // arrange
  const std::string input_invalid_addr = "10.20.";

  // act && assert
  try {
    Ip_input_adapter::validate_address_str(input_invalid_addr);
    FAIL() << "Expected:: std::logic_error";
  } catch (std::logic_error const& err) {
    EXPECT_STREQ(
        "invalid argument: Address string [10.20.] does not match regex!",
        err.what());
  }
}

TEST(test_ip_input_adapter, validate_address_str__validAddr__noEx) {
  // arrange
  const std::string input_valid_line = "127.0.0.1";

  // act && assert
  EXPECT_NO_THROW(
      { Ip_input_adapter::validate_address_str(input_valid_line); });
}

// get_next_str_address
TEST(test_ip_input_adapter,
     get_next_str_address__validInputLine__extractedExpectedAddr) {
  // arrange
  const std::string input_valid_line = "127.0.0.1\tfoo\tfoo2\n";
  std::istringstream iss(input_valid_line);
  Ip_input_adapter ia(iss);
  const std::string expected_addr = "127.0.0.1";

  // act
  std::string actual_addr;
  bool is_success = ia.get_next_str_address(actual_addr);

  // assert
  ASSERT_EQ(expected_addr, actual_addr);
  ASSERT_FALSE(ia.get_next_str_address(actual_addr));
  ASSERT_TRUE(ia.eof());
}
