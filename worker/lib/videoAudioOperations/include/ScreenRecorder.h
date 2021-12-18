#ifndef __SCREEN_RECORDER_H__
#define __SCREEN_RECORDER_H__

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/audio_fifo.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

#include <list>
#include <thread>
#include <memory>

#include <iostream>
#include <vector>
#include "Worker.h"


class ScreenRecorder {
public:
	ScreenRecorder();
	~ScreenRecorder();
	void Start(Worker *initWorker);
	void Stop();

private:
	// initialize decoder
	// initialize scaler
	// initialize encoder
	int InitVideo(AVCodecContext* video_encoder_codec_context);
	
	int InitWriter();

	void EmulateClientInput();

	void DecodeVideo();
	void ScaleVideo(AVFrame* decoded_frame);
	void EncodeVideo(AVFrame* scaled_frame);
	void Writer(AVPacket* output_packet);	
	
	// decoder
	AVFormatContext* input_video_format_context_ = nullptr;
	AVCodecContext* video_decoder_codec_context_ = nullptr;
	AVFormatContext* input_audio_format_context_ = nullptr;
	AVCodecContext* audio_decoder_codec_context_ = nullptr;

	// scaler
	SwsContext* sws_context_ = nullptr;
	SwrContext* swr_context_ = nullptr;

	// encoder
	AVCodecContext* video_encoder_codec_context_ = nullptr;
	AVCodecContext* audio_encoder_codec_context_ = nullptr;

	// writer
	AVFormatContext* output_format_context_ = nullptr;
	AVStream* out_video_stream_ = nullptr;
	AVStream* out_audio_stream_ = nullptr;

	std::string output_filename_;

	bool isRecord_ = false;

	Worker *worker_ = nullptr;
	std::list<std::shared_ptr<std::thread>> threads_;
};

#endif