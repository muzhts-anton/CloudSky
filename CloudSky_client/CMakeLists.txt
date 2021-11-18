cmake_minimum_required(VERSION 3.16)
project(client_decoder)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(CloudSky_client/include)

add_executable(decoder main.cpp src/AudioStreamDecoder.cpp src/VideoStreamDecoder.cpp)

target_include_directories(decoder PUBLIC include)

target_link_libraries(decoder
    avcodec
    avformat
    swresample
    swscale
    avutil
)
