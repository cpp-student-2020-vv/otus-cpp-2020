project(allocators VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

#configure_file(product_version.h.in "${CMAKE_CURRENT_SOURCE_DIR}/product_version.h")

add_executable(allocators main.cpp)
include_directories(math)

set_target_properties(allocators PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(allocators
    PRIVATE "${CMAKE_BINARY_DIR}/hw-02"
)

#test
find_package(GTest REQUIRED)

add_executable(test_factorial test/test_factorial.cpp)
target_link_libraries(test_factorial GTest::GTest GTest::Main)

enable_testing()
add_test(test_factorial test_factorial)

#pack
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_NAME allocators)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cpp.student.2020.vv@gmail.com)

include(CPack)

#deploy
install(TARGETS allocators RUNTIME DESTINATION bin)
