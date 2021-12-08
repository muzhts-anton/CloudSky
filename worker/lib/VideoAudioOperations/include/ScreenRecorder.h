#include <iostream>
#include <string>
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
    int CaptureVideoData(Worker* worker);

private:
    AVFormatContext * avFmtCtx = NULL;
    AVCodecContext * avRawCodecCtx = NULL;
    AVCodecContext * avEncoderCtx;
    AVDictionary * avRawOptions = NULL;
    AVCodec * avDecodec = NULL;
    AVCodec * avEncodec = NULL;
    struct SwsContext *swsCtx = NULL;
    AVPacket * avRawPkt = NULL;
    long int videoIndex = -1;
    AVFrame *avYUVFrame = NULL;

    unsigned int width = 640;
    unsigned int height = 480;
};
