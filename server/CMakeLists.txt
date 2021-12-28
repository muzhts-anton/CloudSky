cmake_minimum_required(VERSION 3.5)

project(CloudSky_Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic  -c -g -lpqxx -L/usr/lib/x86_64-linux-gnu/libpq -lpq)
add_compile_options(-pthread) 
add_link_options(-pthread)
add_link_options(-lpqxx -lpq )

find_package(GTest REQUIRED)

find_package(Boost)
FIND_PACKAGE(Protobuf REQUIRED)
find_package(PostgreSQL REQUIRED)

INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${Boost_INCLUDE_DIRS})


include_directories(${GTEST_INCLUDE_DIRS}/inc/)

add_subdirectory(lib/dbOperations)
add_subdirectory(lib/ServerConnection)

add_executable(CloudSky_MyServer src/main.cpp)

target_include_directories(CloudSky_MyServer PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(CloudSky_MyServer ServerConnection ${Boost_LIBRARIES} ${PostgreSQL_LIBRARIES} dbOperations)