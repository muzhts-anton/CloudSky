#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <X11/Xlib.h>

#include "UDPWorkerSocket.h"
#include "Worker.h"

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

    AVFormatContext * recorderFmtCtx = NULL;
    AVInputFormat *avInputFmt = NULL;
    AVCodecContext * avVideoCodecCtx = NULL;
    AVCodecContext * avVideoEncoderCtx = NULL;
    AVDictionary * avInputDeviceOptions = NULL;
    AVCodec * avVideoDecodec = NULL;
    AVCodec * avVideoEncodec = NULL;
    struct SwsContext *swsVideoCtx = NULL;
    AVPacket* avRecorderPkt = NULL;
    long int videoIndex = -1;
    AVFrame *avYUVFrame = NULL;
    std::vector<uint8_t> videoBuffer;

    unsigned int width;
    unsigned int height;

    int getVideoStream();
    void openInputDevices();
    void close();
};
