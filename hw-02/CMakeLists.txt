project(allocators VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

#configure_file(product_version.h.in "${CMAKE_CURRENT_SOURCE_DIR}/product_version.h")

add_executable(allocators main.cpp)
include_directories(math)

# add_library(ver ver.cpp)
# add_executable(test_version test/test_version.cpp)
# add_executable(test_ip_filter_logic test/test_ip_filter_logic.cpp)
# add_executable(test_ip_input_adapter test/test_ip_input_adapter.cpp)
# add_executable(test_ip_filter_controller test/test_ip_filter_controller.cpp)

set_target_properties(allocators PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(allocators
    PRIVATE "${CMAKE_BINARY_DIR}/hw-02"
)
# target_include_directories(ver
#     PRIVATE "${CMAKE_BINARY_DIR}/hw-02"
# )
# target_link_libraries(ip_filter PRIVATE
#     ver
# )

#test
find_package(GTest REQUIRED)

# target_link_libraries(test_version GTest::GTest GTest::Main ver)
# target_link_libraries(test_ip_filter_logic GTest::GTest GTest::Main ver)
# target_link_libraries(test_ip_input_adapter GTest::GTest GTest::Main ver)
# target_link_libraries(test_ip_filter_controller GTest::GTest GTest::Main ver)

enable_testing()
# add_test(test_version test_version)
# add_test(test_ip_filter_logic test_ip_filter_logic)
# add_test(test_ip_input_adapter test_ip_input_adapter)
# add_test(test_ip_filter_controller test_ip_filter_controller)




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
