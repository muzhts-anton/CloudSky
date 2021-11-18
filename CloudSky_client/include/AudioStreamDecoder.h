#pragma once
#include <stdlib.h>
#include <string.h>
using namespace std;
extern "C"
{

#include <libavcodec/avcodec.h>
#include <libavutil/samplefmt.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}


class AudioStreamDecoder
{
public:
	AudioStreamDecoder();
	~AudioStreamDecoder();
	bool initDecorder();
	bool decodeAudioFrame(char *indata,int insize,AVFrame **frame,int *outSize);
private:
    AVCodec *audio_codec;
	AVCodecContext *audio_codec_context;
	bool openAudioCodec();
	AVFrame *outputaudioFrame;
	AVPacket audioavpkt;
	AVFrame* audioframe;
};