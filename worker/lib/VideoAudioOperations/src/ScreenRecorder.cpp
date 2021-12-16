#include "ScreenRecorder.h"
#include <fstream>
#include <istream>


ScreenRecorder::ScreenRecorder(){
    avdevice_register_all();
    std::cout << "[LOG] : All required functions have been registered!";
}

ScreenRecorder::~ScreenRecorder(){
    close();
}

int ScreenRecorder::initScreenGrabber(){
    Display* serverDisplay = XOpenDisplay(nullptr); 
    Screen*  screen = DefaultScreenOfDisplay(serverDisplay); 
    height = screen->height; 
    width  = screen->width;
    XCloseDisplay(serverDisplay);

    openInputDevices();
    
    avVideoCodecCtx = recorderFmtCtx->streams[videoIndex]->codec;
    avVideoDecodec = avcodec_find_decoder(avVideoCodecCtx->codec_id);
    if (avVideoDecodec == nullptr) {
        std::cerr << "Codec not found.\n";
        throw std::invalid_argument("Codec not found.\n");
    }
    
    if (avcodec_open2(avVideoCodecCtx, avVideoDecodec, nullptr) < 0) {
        std::cout << "Could not open decodec . \n";
        throw std::invalid_argument("Could not open decodec .");
    }	

    swsVideoCtx = sws_getContext(avVideoCodecCtx->width,
        avVideoCodecCtx->height,
        avVideoCodecCtx->pix_fmt,
        avVideoCodecCtx->width,
        avVideoCodecCtx->height,
        AV_PIX_FMT_YUV420P,
        SWS_BICUBIC, nullptr, nullptr, nullptr);

    
    avYUVFrame = av_frame_alloc();
    videoBuffer.reserve(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, avVideoCodecCtx->width, avVideoCodecCtx->height,1));
    av_image_fill_arrays(avYUVFrame->data, avYUVFrame->linesize, videoBuffer.data(), AV_PIX_FMT_YUV420P, avVideoCodecCtx->width, avVideoCodecCtx->height,32); 

    avYUVFrame->width = avVideoCodecCtx->width;
    avYUVFrame->height = avVideoCodecCtx->height;
    avYUVFrame->format = AV_PIX_FMT_YUV420P;

    avVideoEncodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if(!avVideoEncodec) {
      std::cerr << "h264 codec not found\n";
      throw std::invalid_argument("h264 codec not found");
    }
    
    avVideoEncoderCtx = avcodec_alloc_context3(avVideoEncodec);
    
    avVideoEncoderCtx->codec_id = AV_CODEC_ID_H264;
    avVideoEncoderCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    avVideoEncoderCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    avVideoEncoderCtx->width = width;
    avVideoEncoderCtx->height = height;
    avVideoEncoderCtx->time_base.num = 1;
    avVideoEncoderCtx->time_base.den = 60;
    avVideoEncoderCtx->bit_rate = 128*1024*8;
    avVideoEncoderCtx->gop_size = 250;
    avVideoEncoderCtx->qmin = 1;
    avVideoEncoderCtx->qmax = 10;

    AVDictionary *param = 0;
    av_dict_set(&param, "rtbufsize ", "102400",0);
    av_dict_set(&param, "preset", "superfast", 0);
    av_dict_set(&param, "tune", "zerolatency", 0);

    if (avcodec_open2(avVideoEncoderCtx, avVideoEncodec, &param) < 0)  {
        std::cout << "Failed to open video encoder!\n";
        return 0;
    }
    return 0;
}

int ScreenRecorder::captureVideoData(Worker* worker){

    int got_picture = 0;
    int flag = 0;
    std::vector<uint8_t>  outBuf;;
    
    outBuf.reserve(width * height * 3);
    
    AVFrame *avOutFrame;
    avOutFrame = av_frame_alloc();
    av_image_fill_arrays(avOutFrame->data, avOutFrame->linesize, outBuf.data(), avVideoEncoderCtx->pix_fmt, avVideoEncoderCtx->width, avVideoEncoderCtx->height,32);

    avRecorderPkt = av_packet_alloc();
    AVPacket* pkt = av_packet_alloc();  
    while (worker) {
        if (av_read_frame(recorderFmtCtx, avRecorderPkt) >= 0)  {
            if (avRecorderPkt->stream_index == videoIndex) {
                flag = avcodec_decode_video2(avVideoCodecCtx, avOutFrame, &got_picture, avRecorderPkt);
                if (flag < 0) {
                    break;
                }
                if (got_picture > 0) {
                    sws_scale(swsVideoCtx, avOutFrame->data, avOutFrame->linesize, 0, avVideoEncoderCtx->height, avYUVFrame->data, avYUVFrame->linesize);
                    got_picture = 0;
                    flag = avcodec_encode_video2(avVideoEncoderCtx, pkt, avYUVFrame, &got_picture);
                    if (flag >= 0) {
                        if (got_picture > 0) {
                            size_t len = pkt->size;
                            char* data = reinterpret_cast<char*>(pkt->data);
                            while(len / PACKETSIZE){
                                worker->sendData(data, PACKETSIZE);
                                data+= PACKETSIZE;
                                len-=PACKETSIZE;
                            }
                            if(len>0){
                                worker->sendData(data, len);
                            }
                        }
                    }
                    av_packet_unref(pkt);
                    av_packet_unref(avRecorderPkt);
                }
            }
        }

    }
    
    return 0;
}

void ScreenRecorder::openInputDevices(){

    recorderFmtCtx = avformat_alloc_context();
    avInputFmt = av_find_input_format("x11grab");
    if (avInputFmt == nullptr)  {
        std::cerr << "av_find_input_format not found.\n";
        throw std::invalid_argument("av_find_input_format not found.\n");
    }

    if(avformat_open_input(&recorderFmtCtx,":0.0", avInputFmt, &avInputDeviceOptions) !=0 ) {
        std::cerr << "Couldn't open input stream.\n";
        throw std::invalid_argument("Couldn't open input stream.\n");
    }

    if (avformat_find_stream_info(recorderFmtCtx, &avInputDeviceOptions) < 0) {
        std::cerr << "Couldn't find stream information.\n";
        throw std::invalid_argument("Couldn't find stream information.\n");
    }
	
	for (unsigned int i=0; i < recorderFmtCtx->nb_streams; ++i) {
        if (recorderFmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoIndex = i;
            break;
        }
    }

    if (videoIndex == -1 || videoIndex >= recorderFmtCtx->nb_streams) {
        std::cerr << "Didn't find a video stream.\n";
        throw std::invalid_argument("Didn't find a video stream.\n");
    }
}

void ScreenRecorder::close(){
    avformat_close_input(&recorderFmtCtx);
    if(!recorderFmtCtx)
	{
		std::cout<<"[LOG] File closed sucessfully\n";
	}
	else
	{
		std::cerr<<"[ERROR] Unable to close the file\n";
		throw std::invalid_argument("[ERROR] Unable to close the file\n");
	}

	avformat_free_context(recorderFmtCtx);
	if( !recorderFmtCtx )
	{
		std::cout<<"\navformat free successfully";
	}
	else
	{
		std::cerr<<"[ERROR] Unable to free avformat context\n";
		throw std::invalid_argument("[ERROR] Unable to free avformat context\n");
	}
}
