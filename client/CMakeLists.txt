cmake_minimum_required(VERSION 3.5)

project(CloudSky_MyClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)


add_subdirectory(lib/ClientConnection)

add_executable(CloudSky_MyClient src/main.cpp)

target_link_libraries(CloudSky_MyClient ClientConnection)
