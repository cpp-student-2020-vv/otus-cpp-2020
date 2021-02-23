cmake_minimum_required(VERSION 3.2)
#project(acm VERSION 0.0.1)

#add_executable(acm acm1409.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#test
find_package(GTest REQUIRED)

add_executable(test_acm1409 test_acm1409.cpp acm1409.cpp)
target_link_libraries(test_acm1409 GTest::GTest GTest::Main)

add_executable(test_acm1877 test_acm1877.cpp acm1877.cpp)
target_link_libraries(test_acm1877 GTest::GTest GTest::Main)

enable_testing()
add_test(test_acm1409 test_acm1409)
add_test(test_acm1877 test_acm1877)
