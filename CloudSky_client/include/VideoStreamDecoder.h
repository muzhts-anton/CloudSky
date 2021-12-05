#pragma once
#include <stdlib.h>
#include <string.h>
#include <queue>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/common.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

class VideoStreamDecoder
{
public:
	VideoStreamDecoder();
	~VideoStreamDecoder();
	bool initDecoder();
	bool decodeVideoFrame(char *indata,int insize,AVFrame **frame);
private:
    AVCodec *video_codec;
	AVCodecContext *video_codec_context;
	bool openVideoCodec();
	bool setupSwscale();
	AVPacket videoavpkt;
	AVFrame* videoframe;
	int outputWidth;
	int outputHeight;
	SwsContext *img_convert_ctx;
};