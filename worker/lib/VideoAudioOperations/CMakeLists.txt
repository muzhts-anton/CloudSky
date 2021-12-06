add_library(VideoAudioOperations src/ScreenRecorder.cpp include/ScreenRecorder.h)

include_directories(CloudSky_server/include)


target_include_directories(VideoAudioOperations PUBLIC include)

target_link_libraries(VideoAudioOperations
    avcodec
    avformat
    swresample
    swscale
    avutil
    avdevice
    avfilter
)
