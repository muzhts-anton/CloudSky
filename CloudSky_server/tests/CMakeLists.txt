cmake_minimum_required(VERSION 3.16)
project(server_encoder)
include_directories(include)
include_directories(src)

add_library(video_component ../include/VideoComponent.h
    ../src/VideoComponent.cpp)

add_library(audio_component ../include/SoundComponent.h
    ../src/SoundComponent.cpp)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})
add_executable(tests_server tests.cpp)

target_link_libraries(tests_server ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_server video_component audio_component)
target_include_directories(tests_server PUBLIC CloudSky_server/include)
target_link_libraries(tests_server
    avcodec
    avformat
    swresample
    swscale
    avutil
)