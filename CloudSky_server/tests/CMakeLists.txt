cmake_minimum_required(VERSION 3.16)
project(server_encoder)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})
add_executable(tests_server tests.cpp)

target_link_libraries(tests_server ${GTEST_LIBRARIES} -lpthread)