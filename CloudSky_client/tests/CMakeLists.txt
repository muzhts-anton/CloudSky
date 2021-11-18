cmake_minimum_required(VERSION 3.16)
project(client_decoder)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})
add_executable(tests_client tests.cpp)

target_link_libraries(tests_client ${GTEST_LIBRARIES} -lpthread)