cmake_minimum_required(VERSION 3.8)
project(cloudGaming)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CXX g++)

set(LIB_SOURCE_FILES src/TCPServerSocket.cpp src/UDPServerSocket.cpp src/Server.cpp)
set(LIB_HEADERS_FILES include/TCPServerSocket.hpp include/UDPServerSocket.hpp include/Server.hpp include/Interactions.hpp include/DataBaseHandler.hpp include/SoundComponent.hpp include/VideoComponent.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wvla -Iinc -Wfloat-equal -pthread -Wpedantic -Wextra")

add_library(serverSockets STATIC ${LIB_SOURCE_FILES} ${LIB_HEADERS_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(server src/main.cpp)
target_link_libraries(server serverSockets)