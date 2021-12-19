cmake_minimum_required(VERSION 3.5)

project(CloudSky_Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

include_directories(${GTEST_INCLUDE_DIRS}/inc/)

add_subdirectory(lib/workerConnection)

add_executable(CloudSky_MyWorker src/main.cpp)

target_link_libraries(CloudSky_MyWorker workerConnection)

enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(tests/testWorkerConnection)
