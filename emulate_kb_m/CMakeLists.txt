cmake_minimum_required(VERSION 3.16)

project(emulate_devices)
set(CMAKE_CXX_STANDARD 17)

add_executable(emulate project/src/emulate.cpp)
add_executable(mouse_move project/src/mouse_move.cpp)