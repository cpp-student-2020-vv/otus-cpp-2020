#include "gtest/gtest.h"

#include "../math/factorial.hpp"

using namespace otus_cpp::hw02::math;

/**
 * @brief container with unit tests for factorial functions.
 *
 * Test naming convention: (unit under test)_(use case)_(expected result)
 */

/**
 * @brief Basic "happy path" checks for runtime version of factorial.
 */
TEST(test_factorial, runtimeFactorial_validSmallPositiveInput_expectedResult) {
  // arrange, act, assert
  ASSERT_EQ(1UL, factorial(0));
  ASSERT_EQ(1UL, factorial(1));
  ASSERT_EQ(2UL, factorial(2));
  ASSERT_EQ(6UL, factorial(3));
  ASSERT_EQ(24UL, factorial(4));
  ASSERT_EQ(120UL, factorial(5));
  ASSERT_EQ(720UL, factorial(6));
  ASSERT_EQ(5040UL, factorial(7));
  ASSERT_EQ(40320UL, factorial(8));
  ASSERT_EQ(362880UL, factorial(9));
}
