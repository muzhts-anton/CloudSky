cmake_minimum_required(VERSION 3.8)
project(cloudGaming)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CXX g++)

set(LIB_SOURCE_FILES src/TCPClientSocket.cpp src/UDPClientSocket.cpp)
set(LIB_HEADERS_FILES include/TCPClientSocket.hpp include/UDPClientSocket.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wvla -Iinc -Wfloat-equal -pthread -Wpedantic -Wextra")

add_library(clientSockets STATIC ${LIB_SOURCE_FILES} ${LIB_HEADERS_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(client src/main.cpp)
target_link_libraries(client clientSockets)