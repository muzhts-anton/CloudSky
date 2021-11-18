#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <cstdint> 

extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
	#include <libavutil/pixfmt.h>
}

class VideoComponent
{
public:
	VideoComponent();
	~VideoComponent();
	bool initVideoComponent();
	void startFrameLoop();
	void stopFrameLoop();
	void setQuality(int width,int height,int bandwidth);
private:
	int frameCounter;
	int outputWidth,outputHeight;
	int bandwidth;
	AVCodec *video_codec;
	AVFrame* raw_frame;
	SwsContext *img_convert_ctx;
	AVCodecContext *video_codec_context;
	bool setup_scale(int width,int height);
    bool openVideoEncoder();
	bool sendOutFrame(AVPacket *packet);
	void cleanupEncoder();
	bool write_video_frame(AVFrame *frame);
};
