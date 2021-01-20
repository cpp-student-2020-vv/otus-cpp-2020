#include "../ver.h"

#include "gtest/gtest.h"

using namespace otus_cpp::unit1::task2;

TEST(test_version, test_valid_version) { ASSERT_TRUE(version() > 0); }
