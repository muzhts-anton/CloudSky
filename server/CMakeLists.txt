cmake_minimum_required(VERSION 3.8)
project(cloudGaming)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CXX g++)

set(LIB_SOURCE_FILES src/TCPServerSocket.cpp src/UDPServerSocket.cpp src/Server.cpp)
set(LIB_HEADERS_FILES include/TCPServerSocket.h include/UDPServerSocket.h include/Server.h include/Interactions.h include/DataBaseHandler.h include/SoundComponent.h include/VideoComponent.h include/constants.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ggdb3 -pthread -Wall -Werror -pedantic -Wvla -Iinc -Wfloat-equal -pthread -Wpedantic -Wextra")
add_compile_options("--coverage")

add_library(serverSockets STATIC ${LIB_SOURCE_FILES} ${LIB_HEADERS_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

# enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS}/inc/)
# add_subdirectory(unit_tests)


add_executable(server src/Server.cpp)
target_link_libraries(server gcov)  
target_link_libraries(server serverSockets)