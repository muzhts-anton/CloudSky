cmake_minimum_required(VERSION 3.5)

project(CloudSky_Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_libraries(-lpq)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -Wno-deprecated-declarations -c -g -lpqxx -L/usr/lib/x86_64-linux-gnu/libpq -lpq)
add_link_options(-lpqxx -lpq )

find_package(GTest REQUIRED)
FIND_PACKAGE(Protobuf REQUIRED)
find_package(PostgreSQL REQUIRED)

INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})


include_directories(${GTEST_INCLUDE_DIRS}/inc/)

add_subdirectory(lib/emulation)
add_subdirectory(lib/workerConnection)
add_subdirectory(lib/protobufOperations)
add_subdirectory(lib/videoAudioOperations)
add_subdirectory(lib/dbOperations)

add_executable(CloudSky_MyWorker src/main.cpp)

target_include_directories(CloudSky_MyWorker PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(CloudSky_MyWorker workerConnection protobufOperations emulation videoAudioOperations ${PostgreSQL_LIBRARIES} dbOperations)
