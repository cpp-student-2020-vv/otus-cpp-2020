cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(product_version.h.in product_version.h)

add_executable(ip_filter main.cpp)
add_library(ver ver.cpp)
add_executable(test_version test/test_version.cpp)
add_executable(test_ip_filter_logic test/test_ip_filter_logic.cpp)
add_executable(test_ip_input_adapter test/test_ip_input_adapter.cpp)
add_executable(test_ip_filter_controller test/test_ip_filter_controller.cpp)

set_target_properties(ip_filter ver test_version PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_include_directories(ver
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(ip_filter PRIVATE
    ver
)

#test
find_package(GTest REQUIRED)

target_link_libraries(test_version GTest::GTest GTest::Main ver)
target_link_libraries(test_ip_filter_logic GTest::GTest GTest::Main ver)
target_link_libraries(test_ip_input_adapter GTest::GTest GTest::Main ver)
target_link_libraries(test_ip_filter_controller GTest::GTest GTest::Main ver)

enable_testing()
add_test(test_version test_version)
add_test(test_ip_filter_logic test_ip_filter_logic)
add_test(test_ip_input_adapter test_ip_input_adapter)
add_test(test_ip_filter_controller test_ip_filter_controller)



if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ver PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ver PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


#pack
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT vadim-volkov@github.com)

include(CPack)

#deploy
install(TARGETS ip_filter RUNTIME DESTINATION bin)
