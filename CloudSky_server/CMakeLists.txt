cmake_minimum_required(VERSION 3.16)
project(server_encoder)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(CloudSky_server/include)

add_executable(recorder main.cpp src/SoundComponent.cpp src/VideoComponent.cpp)

target_include_directories(recorder PUBLIC include)

target_link_libraries(recorder
    avcodec
    avformat
    swresample
    swscale
    avutil
)
