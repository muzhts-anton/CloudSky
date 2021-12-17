add_library(videoAudioOperations src/ScreenRecorder.cpp include/ScreenRecorder.h)

include_directories(CloudSky_server/include)


target_include_directories(videoAudioOperations PUBLIC include ../../build/lib/emulation)

target_link_libraries(videoAudioOperations
    avcodec
    avformat
    swresample
    swscale
    avutil
    avdevice
    avfilter
    SDL2
    X11
    protobufOperations
    emulation
    workerConnection
)
