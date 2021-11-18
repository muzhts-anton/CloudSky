#pragma once
#include <iostream>
extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswresample/swresample.h>
	#include <libavutil/frame.h>
}
class SoundComponent
{
public:
	SoundComponent();
	~SoundComponent();
	bool initSoundComponent();
	void startFrameLoop();
	void stopFrameLoop();

private:
	SwrContext *swr_ctx;
	AVCodecContext *audio_codec_context;
	AVFrame *frame;
	AVCodec *audio_codec;
	bool run_flag;
	bool openAudioEncoder();
	bool write_audio_frame(AVFrame *frame);
	void cleanupEncoder();
};