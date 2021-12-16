#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <X11/Xlib.h>

#include "../lib/WorkerConnection/include/UDPWorkerSocket.h"
#include "../lib/WorkerConnection/include/Worker.h"

#define PACKETSIZE 4092
extern "C" {
#include "libswscale/swscale.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libavdevice/avdevice.h"
#include "libavutil/imgutils.h"
}

class ScreenRecorder{
public:
    ScreenRecorder();
    ~ScreenRecorder();

    int initScreenGrabber();
    int captureVideoData(Worker* worker);

private:

    AVFormatContext * recorderFmtCtx = nullptr;
    AVInputFormat *avInputFmt = nullptr;
    AVCodecContext * avVideoCodecCtx = nullptr;
    AVCodecContext * avVideoEncoderCtx = nullptr;
    AVDictionary * avInputDeviceOptions = nullptr;
    AVCodec * avVideoDecodec = nullptr;
    AVCodec * avVideoEncodec = nullptr;
    struct SwsContext *swsVideoCtx = nullptr;
    AVPacket* avRecorderPkt = nullptr;
    long int videoIndex = -1;
    AVFrame *avYUVFrame = nullptr;
    std::vector<uint8_t> videoBuffer;

    unsigned int width;
    unsigned int height;

    int getVideoStream();
    void openInputDevices();
    void close();
};
