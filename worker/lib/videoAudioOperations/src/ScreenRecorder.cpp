#include "ScreenRecorder.h"
#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include "operationEmulation.h"


ScreenRecorder::ScreenRecorder(Worker *initWorker)
	: worker_(initWorker) {
	worker_->start();
	worker_->receiveClientIP();
	output_filename_ = "udp://" + worker_->getClientIP() + ":8080";
    AVCodecContext video_encoder_codec_context;

	video_encoder_codec_context.bit_rate = 4000000;
	video_encoder_codec_context.width = 1920;
	video_encoder_codec_context.height = 1080;
	video_encoder_codec_context.pix_fmt = AV_PIX_FMT_YUV420P;
	video_encoder_codec_context.time_base.num = 1;
	video_encoder_codec_context.time_base.den = 60;
	video_encoder_codec_context.gop_size =  3;
	video_encoder_codec_context.qmin = 16;
	video_encoder_codec_context.qmax = 26;
	video_encoder_codec_context.max_b_frames = 1;
	InitVideo(&video_encoder_codec_context);
	InitWriter();
}

int ScreenRecorder::InitWriter(){
	
	avformat_alloc_output_context2(&output_format_context_, nullptr, "mpegts", output_filename_.c_str());
	if (!output_format_context_)
	{
		std::cout << "\n [ERROR] error in allocating av format output context";
		return 1;
	}
	out_video_stream_ = avformat_new_stream(output_format_context_, nullptr);
	out_video_stream_->id = output_format_context_->nb_streams - 1;
	out_video_stream_->time_base = video_encoder_codec_context_->time_base;
	int ret = avcodec_parameters_from_context(out_video_stream_->codecpar, video_encoder_codec_context_);
	if (ret < 0) {
		av_log(nullptr, AV_LOG_ERROR, "[ERROR] Failed to copy encoder parameters to output stream\n");
		return ret;
	}

	if (output_format_context_->oformat->flags & AVFMT_GLOBALHEADER)
	{
		output_format_context_->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}
	
	AVDictionary* options = nullptr;



	if (!(output_format_context_->flags & AVFMT_NOFILE))
	{
		if (avio_open2(&output_format_context_->pb, output_filename_.c_str(), AVIO_FLAG_WRITE, nullptr, &options) < 0)
		{
			std::cout << "\n[ERROR] error in creating the video file";
			return 1;
		}
	}

	if (!output_format_context_->nb_streams)
	{
		std::cout << "\n[ERROR] output file dose not contain any stream";
		return 1;
	}

	ret = avformat_write_header(output_format_context_, nullptr);
	if (ret < 0)
	{
		std::cout << "\n[ERROR] error in writing the header context";
		return 1;
	}
	return 0;
}

int ScreenRecorder::InitVideo(AVCodecContext* video_encoder_codec_context) {
	avdevice_register_all();
	avformat_network_init();
	AVDictionary* options = nullptr;
	
	av_dict_set(&options,"video_size", "1920x1080",0); 
	av_dict_set(&options,"preset", "fast",0);
	av_dict_set(&options,"tune", "zerolatency", 0);
	av_dict_set(&options,"framerate", "60", 0);

	
	int ret;
	AVInputFormat* video_input_format_ = nullptr;
	video_input_format_ =  av_find_input_format("x11grab");
	
	ret = avformat_open_input(&input_video_format_context_, ":0.0", video_input_format_, &options);
	if (ret != 0)
	{
		std::cout << "\n[ERROR] error in opening input device";
		return ret;
	}
	ret = avformat_find_stream_info(input_video_format_context_, &options);
	if (ret < 0)
	{
		std::cout << "\n [ERROR] unable to find the stream information";
		return ret;
	}
	int out_video_stream_index = av_find_best_stream(input_video_format_context_, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	if (out_video_stream_index == -1)
	{
		std::cout << "\n[ERROR] unable to find the video stream index. (-1)";
		return 1;
	}

	AVCodecParameters* video_parameter_ = nullptr;
	video_parameter_ = input_video_format_context_->streams[out_video_stream_index]->codecpar;
	AVCodec* decoder_codec_ =nullptr;
	decoder_codec_ = avcodec_find_decoder(video_parameter_->codec_id);
	if (!decoder_codec_) {
		std::cout << "[ERROR] codec not found\n";
		return 1;
	}
	video_decoder_codec_context_ = avcodec_alloc_context3(decoder_codec_);
	if (!video_decoder_codec_context_) {
		std::cout << "[ERROR] Could not allocate video decoder context\n";
		return 1;
	}

	avcodec_parameters_to_context(video_decoder_codec_context_, video_parameter_);

	ret = avcodec_open2(video_decoder_codec_context_, decoder_codec_, nullptr);
	if (ret < 0) {
		std::cout << "[ERROR] Could not open decoder\n";
		return ret;
	}

	AVCodec* video_encoder_codec_ = nullptr;
	video_encoder_codec_ = avcodec_find_encoder(AV_CODEC_ID_MPEG4);
	if (!video_encoder_codec_) {
		std::cout << "[ERROR] Codec AV_CODEC_ID_H264 not found\n";
		return 1;
	}
	
	video_encoder_codec_context_ = avcodec_alloc_context3(video_encoder_codec_);
	if (!video_encoder_codec_context_) {
		std::cout << "[ERROR] Could not allocate video video encoder context\n";
		return 1;
	}

	video_encoder_codec_context_->bit_rate	  = video_encoder_codec_context->bit_rate;
	video_encoder_codec_context_->width		  = video_encoder_codec_context->width;
	video_encoder_codec_context_->height		= video_encoder_codec_context->height;
	video_encoder_codec_context_->pix_fmt		  = video_encoder_codec_context->pix_fmt;
	video_encoder_codec_context_->time_base.num = video_encoder_codec_context->time_base.num;
	video_encoder_codec_context_->time_base.den = video_encoder_codec_context->time_base.den;
	video_encoder_codec_context_->framerate.num = video_encoder_codec_context->framerate.num;
	video_encoder_codec_context_->framerate.den = video_encoder_codec_context->framerate.den;
	video_encoder_codec_context_->gop_size	  = video_encoder_codec_context->gop_size;
	video_encoder_codec_context_->max_b_frames  = video_encoder_codec_context->max_b_frames;
	video_encoder_codec_context_->qmin = 	video_encoder_codec_context->qmin;
	video_encoder_codec_context_->qmax = video_encoder_codec_context->qmax;


	av_opt_set(video_encoder_codec_context_, "preset", "fast", 0);
    av_opt_set(video_encoder_codec_context_, "tune", "zerolatency", 0);
	av_opt_set(video_encoder_codec_context_, "bitrate", "6000k", 0);
	av_opt_set(video_encoder_codec_context_, "analyzeduration", "0", 0);
	av_opt_set(video_encoder_codec_context_, "probesize", "32", 0);
	av_opt_set(video_encoder_codec_context_, "threads", "4", 0);
	av_opt_set(video_encoder_codec_context_, "sc_threshold", "1", 0);
    

	
	ret = avcodec_open2(video_encoder_codec_context_, video_encoder_codec_, &options);
	if (ret < 0) {
		std::cout << "[ERROR] Could not open video encoder\n";
		return ret;
	}

	sws_context_ = sws_getContext(
		video_decoder_codec_context_->width, video_decoder_codec_context_->height, video_decoder_codec_context_->pix_fmt,
		video_encoder_codec_context_->width, video_encoder_codec_context_->height, video_encoder_codec_context_->pix_fmt,
		SWS_BILINEAR, nullptr, nullptr, nullptr);

	av_dict_free(&options);
	avcodec_parameters_free(&video_parameter_);

	return 0;
}

ScreenRecorder::~ScreenRecorder() {
	avformat_network_deinit();
	
	if (video_encoder_codec_context_ != nullptr)
		avcodec_free_context(&video_encoder_codec_context_);

	if (video_decoder_codec_context_ != nullptr)
		avcodec_free_context(&video_decoder_codec_context_);

	sws_freeContext(sws_context_);
}

void ScreenRecorder::Start() {
	isRecord_ = true;
	threads_.push_back(std::make_shared<std::thread>(std::bind(&ScreenRecorder::EmulateClientInput, this)));
	threads_.push_back(std::make_shared<std::thread>(std::bind(&ScreenRecorder::DecodeVideo, this)));
}

void ScreenRecorder::Stop() {
	isRecord_ = false;
	for (auto i = threads_.begin(); i != threads_.end(); ++i) {
        if ((*i)->joinable()) {
            (*i)->join();
        }
    }
}

void ScreenRecorder::EmulateClientInput()
{
	KeyboardMouse::ButtonsCoords ReceiveMessage;
    ViktorDev::EmelationKeyBoard keyboard;
	ViktorDev::EmulationMouse mouse;
    std::string filename = "receivedButtonsCoords.bin";
    while (true)
    {

        worker_->getInteraction(filename);
        ViktorDev::ReceiveInteraction ReceiveM(filename, ReceiveMessage);
        if (ReceiveM.receiveIt()){
        	std::cout << "[ERROR] Error wint receiving";
		}
        ReceiveM.printMessage();
		if(ReceiveM.getMessage().xcoord() == 0){
			for(int i =0; i < buttonQuanity; ++i){
			ReceiveM.getMessage().add_buttonpressed(false);
		}
		ReceiveM.printMessage();
		ReceiveM.getMessage().set_xcoord(100);
		ReceiveM.getMessage().set_ycoord(100);
		ReceiveM.getMessage().mousebuttons(false);
		}

		keyboard.setKeyboard(ReceiveM.getMessage());
		mouse.setCoordsButtons(ReceiveM.getMessage());
		keyboard.emulateKeyboard();
		mouse.emulateMouse();
		std::cout << "Законч принимать\n";
    }
}

void ScreenRecorder::DecodeVideo() {
	bool previous = worker_->getState();
	while (isRecord_) {
		if(!worker_->getState()){
			previous = false;
			continue;
		}
		if(previous == false){
			usleep(1000000);
		}
		AVPacket* input_packet = av_packet_alloc();
		av_read_frame(input_video_format_context_, input_packet);
		int ret;
		ret = avcodec_send_packet(video_decoder_codec_context_, input_packet);
		if (ret < 0) {
			av_packet_free(&input_packet);
			std::cout << "[ERROR] Error sending a packet for decoding\n";
			return;
		}

		while (ret >= 0) {

			AVFrame* decoded_frame = av_frame_alloc();
			if (!decoded_frame) {

				std::cout << "[ERROR] Could not allocate video pFrame\n";
				return;
			}
			ret = avcodec_receive_frame(video_decoder_codec_context_, decoded_frame);
			if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
				break;
			else if (ret < 0) {
				av_frame_free(&decoded_frame);
				std::cout << "[ERROR] Error during decoding\n";
				return;
			}
			ScaleVideo(decoded_frame);
			av_packet_free(&input_packet);
			std::cout << "[LOG] Frame have been send\n";

		}		
		previous = worker_->getState();

	}

}

void ScreenRecorder::ScaleVideo(AVFrame* decoded_frame) {
	
	AVFrame* scaled_frame = av_frame_alloc();
	int nbytes = av_image_get_buffer_size(video_encoder_codec_context_->pix_fmt, video_encoder_codec_context_->width, video_encoder_codec_context_->height, 32);
	std::vector<uint8_t> video_outbuf;
	video_outbuf.reserve(nbytes);
	av_image_fill_arrays(scaled_frame->data, scaled_frame->linesize, video_outbuf.data(), video_encoder_codec_context_->pix_fmt, video_encoder_codec_context_->width, video_encoder_codec_context_->height, 1);

	sws_scale(sws_context_, decoded_frame->data, decoded_frame->linesize,
		0, video_decoder_codec_context_->height, scaled_frame->data, scaled_frame->linesize);
	
	EncodeVideo(scaled_frame);
	av_frame_free(&decoded_frame);
	video_outbuf.clear();
}

void ScreenRecorder::EncodeVideo(AVFrame* scaled_frame) {
	int ret;

	scaled_frame->format = video_encoder_codec_context_->pix_fmt;
	scaled_frame->width = video_encoder_codec_context_->width;
	scaled_frame->height = video_encoder_codec_context_->height;
	ret = avcodec_send_frame(video_encoder_codec_context_, scaled_frame);
	if (ret < 0) {
		std::cout << "[ERROR] Error sending a frame for encoding\n";
		return;
	}
	AVPacket* output_packet = av_packet_alloc();
	if (!output_packet)
		return;
	ret = avcodec_receive_packet(video_encoder_codec_context_, output_packet);
	if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
		return;
	else if (ret < 0) {
		std::cout << "[ERROR] Error during encoding\n";
		return;
	}
	if (output_packet->pts != AV_NOPTS_VALUE)
		output_packet->pts = av_rescale_q(output_packet->pts, video_encoder_codec_context_->time_base, out_video_stream_->time_base);
	if (output_packet->dts != AV_NOPTS_VALUE)
		output_packet->dts = av_rescale_q(output_packet->dts, video_encoder_codec_context_->time_base, out_video_stream_->time_base);
	output_packet->stream_index = out_video_stream_->index;

	av_frame_free(&scaled_frame);
	Writer(output_packet);

}

void ScreenRecorder::Writer(AVPacket* output_packet) {
	
	if (av_interleaved_write_frame(output_format_context_, output_packet) != 0)
	{
		std::cout << "\n [ERROR] error in writing video frame";
	}
	av_packet_unref(output_packet);
	av_packet_free(&output_packet);

}