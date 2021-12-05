#include <iostream>
#include <string>

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
    int CaptureVideoData();

private:
    AVFormatContext * avFmtCtx = NULL;
    AVCodecContext * avRawCodecCtx = NULL;
    AVCodecContext * avEncoderCtx;
    AVDictionary * avRawOptions = NULL;
    AVCodec * avDecodec = NULL;
    AVCodec * avEncodec = NULL;
    struct SwsContext *swsCtx = NULL;
    AVPacket * avRawPkt = NULL;
    int videoIndex = -1;
    AVFrame *avYUVFrame = NULL;

    unsigned int width = 1920;
    unsigned int height = 950;
};
