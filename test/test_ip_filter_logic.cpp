#include <iostream>
#include <sstream>
#include <utility>

#include "gtest/gtest.h"

#include "../ip_filter_logic.h"

using namespace otus_cpp::unit1::task2;

TEST(test_ip_filter_logic, reportAll_sortWasNotCalled_exThrown) {
  // arrange
  Ip_filter_logic<Ip4_dto> fl;

  // act & assert
  try {
    fl.report_all();
    FAIL() << "Expected:: std::logic_error";
  } catch (std::logic_error const& err) {
    EXPECT_STREQ("Invalid state: sort_reversed_lex() was not called yet!",
                 err.what());
  }
}

TEST(test_ip_filter_logic,
     add_singleAddress_reportAllContainsAddedAndFormatted) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  const Ip4_dto& input{1, 2, 3, 4};

  // act
  fl.add(std::move(input));
  fl.sort_reversed_lex();
  fl.report_all();

  // assert
  ASSERT_TRUE(oss);
  ASSERT_EQ("1.2.3.4\n", oss.str());
}

TEST(test_ip_filter_logic,
     sort_alreadyAddedManyAddresses_reportAllContainsSortedAndFormatted) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{1, 1, 1, 1}, {1, 2, 1, 1}, {1, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }
  const std::string expected = "1.10.1.1\n1.2.1.1\n1.1.1.1\n";

  // act
  fl.sort_reversed_lex();
  fl.report_all();

  // assert
  ASSERT_TRUE(oss);
  ASSERT_EQ(expected, oss.str());
}

// report_first_eq_one
TEST(test_ip_filter_logic,
     report_first_eq_one__alreadyAddedAddressesWithoutFirstOne__emptyReport) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{0, 1, 1, 1}, {0, 2, 1, 1}, {0, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }

  // act
  fl.sort_reversed_lex();
  fl.report_first_eq_one();

  // assert
  ASSERT_TRUE(oss.str().empty());
}

TEST(
    test_ip_filter_logic,
    report_first_eq_one__alreadyAddedAddressesWithFirstOne__sortedSubsetContainingFirstOneOnly) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{0, 1, 1, 1}, {0, 2, 1, 1}, {0, 10, 1, 1},
                             {1, 1, 1, 1}, {1, 2, 1, 1}, {1, 10, 1, 1},
                             {2, 1, 1, 1}, {2, 2, 1, 1}, {2, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }
  const std::string expected = "1.10.1.1\n1.2.1.1\n1.1.1.1\n";

  // act
  fl.sort_reversed_lex();
  fl.report_first_eq_one();

  // assert
  ASSERT_TRUE(oss);
  ASSERT_EQ(expected, oss.str());
}

// report_first_46_second_70
TEST(
    test_ip_filter_logic,
    report_first_46_second_70__alreadyAddedAddressesWithout46_70__emptyReport) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{0, 1, 1, 1}, {0, 2, 1, 1}, {0, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }

  // act
  fl.sort_reversed_lex();
  fl.report_first_46_second_70();

  // assert
  ASSERT_TRUE(oss.str().empty());
}

TEST(
    test_ip_filter_logic,
    report_first_46_second_70__alreadyAddedAddressesWithCriteria__sortedSubsetContaining46_70) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{0, 1, 1, 1},   {0, 2, 1, 1},   {0, 10, 1, 1},
                             {46, 70, 1, 1}, {46, 70, 2, 1}, {46, 70, 10, 1},
                             {2, 1, 1, 1},   {2, 2, 1, 1},   {2, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }
  const std::string expected = "46.70.10.1\n46.70.2.1\n46.70.1.1\n";

  // act
  fl.sort_reversed_lex();
  fl.report_first_46_second_70();

  // assert
  ASSERT_TRUE(oss);
  ASSERT_EQ(expected, oss.str());
}

// report_any_eq_46
TEST(test_ip_filter_logic,
     report_any_eq_46__alreadyAddedAddressesWithoutAny46__emptyReport) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{0, 1, 1, 1}, {0, 2, 1, 1}, {0, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }

  // act
  fl.sort_reversed_lex();
  fl.report_any_eq_46();

  // assert
  ASSERT_TRUE(oss.str().empty());
}

TEST(
    test_ip_filter_logic,
    report_any_eq_46__alreadyAddedAddressesWithCriteria__sortedSubsetContaining46) {
  // arrange
  std::ostringstream oss;
  Ip_filter_logic<Ip4_dto> fl(oss);
  std::vector<Ip4_dto> input{{0, 1, 1, 1},
                             {0, 2, 1, 1},
                             {0, 10, 1, 1},
                             // items containing 46
                             {46, 1, 1, 1},
                             {1, 46, 2, 1},
                             {10, 10, 46, 1},
                             {1, 70, 1, 46},
                             // rest
                             {2, 1, 1, 1},
                             {2, 2, 1, 1},
                             {2, 10, 1, 1}};
  for (const auto& a : input) {
    fl.add(std::move(a));
  }
  const std::string expected = "46.1.1.1\n10.10.46.1\n1.70.1.46\n1.46.2.1\n";

  // act
  fl.sort_reversed_lex();
  fl.report_any_eq_46();

  // assert
  ASSERT_TRUE(oss);
  ASSERT_EQ(expected, oss.str());
}
