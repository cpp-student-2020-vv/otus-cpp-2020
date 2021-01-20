#include "gtest/gtest.h"

#include "../ip_filter_controller.h"

using namespace otus_cpp::unit1::task2;

TEST(test_ip_filter_controller, run_validInput_allReportsAsExpected) {
  // arrange
  const std::string input_lines =
      // report_first_eq_one
      "0.1.1.1\tfoo\tfoo2\n"
      "0.2.1.1\tfoo\tfoo2\n"
      "0.10.1.1\tfoo\tfoo2\n"
      "1.1.1.1\tfoo\tfoo2\n"
      "1.2.1.1\tfoo\tfoo2\n"
      "1.10.1.1\tfoo\tfoo2\n"
      "2.1.1.1\tfoo\tfoo2\n"
      "2.2.1.1\tfoo\tfoo2\n"
      "2.10.1.1\tfoo\tfoo2\n"
      // report_first_46_second_70
      "46.70.1.1\tfoo\tfoo2\n"
      "46.70.2.1\tfoo\tfoo2\n"
      "46.70.10.1\tfoo\tfoo2\n"
      // report_any_eq_46
      "46.1.1.1\tfoo\tfoo2\n"
      "1.46.2.1\tfoo\tfoo2\n"
      "10.10.46.1\tfoo\tfoo2\n"
      "1.70.1.46\tfoo\tfoo2\n";
  const std::string expected_reports =
      // report_all
      "46.70.10.1\n"
      "46.70.2.1\n"
      "46.70.1.1\n"
      "46.1.1.1\n"
      "10.10.46.1\n"
      "2.10.1.1\n"
      "2.2.1.1\n"
      "2.1.1.1\n"
      "1.70.1.46\n"
      "1.46.2.1\n"
      "1.10.1.1\n"
      "1.2.1.1\n"
      "1.1.1.1\n"
      "0.10.1.1\n"
      "0.2.1.1\n"
      "0.1.1.1\n"
      // report_first_eq_one
      "1.70.1.46\n"
      "1.46.2.1\n"
      "1.10.1.1\n"
      "1.2.1.1\n"
      "1.1.1.1\n"
      // report_first_46_second_70
      "46.70.10.1\n"
      "46.70.2.1\n"
      "46.70.1.1\n"
      // report_any_eq_46
      "46.70.10.1\n"
      "46.70.2.1\n"
      "46.70.1.1\n"
      "46.1.1.1\n"
      "10.10.46.1\n"
      "1.70.1.46\n"
      "1.46.2.1\n";

  std::istringstream iss(input_lines);
  auto pInput = std::make_unique<Ip_input_adapter>(iss);

  std::ostringstream oss;
  auto pLogic = std::make_unique<Ip_filter_logic<Ip4_dto>>(oss);

  auto c = std::make_unique<Ip_filter_controller>(std::move(pInput),
                                                  std::move(pLogic));

  // act
  c->run();

  // assert
  ASSERT_EQ(expected_reports, oss.str());
}
