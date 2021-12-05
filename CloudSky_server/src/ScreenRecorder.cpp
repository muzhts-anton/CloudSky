#include "ScreenRecorder.h"

ScreenRecorder::ScreenRecorder(){
    avdevice_register_all();
    std::cout << "All required functions have been registered!";
}

ScreenRecorder::~ScreenRecorder(){
    avformat_close_input(&avFmtCtx);
    if(!avFmtCtx)
	{
		std::cout<<"\nFile closed sucessfully";
	}
	else
	{
		std::cout<<"\nunable to close the file";
		exit(1);
	}

	avformat_free_context(avFmtCtx);
	if( !avFmtCtx )
	{
		std::cout<<"\navformat free successfully";
	}
	else
	{
		std::cout<<"\nunable to free avformat context";
		exit(1);
	}
}

int ScreenRecorder::initScreenGrabber(){
    avFmtCtx = avformat_alloc_context();
    avRawPkt = (AVPacket *)malloc(sizeof(AVPacket));

    AVInputFormat *avInputFmt = av_find_input_format("x11grab");
    if (avInputFmt == NULL)  {
        std::cout << "av_find_input_format not found......\n";
        return 0;
    }

    if(avformat_open_input(&avFmtCtx,":0.0", avInputFmt, &avRawOptions) !=0 ) {
        std::cout << "Couldn't open input stream.\n";
        return 0;
    }
    if (avformat_find_stream_info(avFmtCtx, &avRawOptions) < 0) {
        std::cout << "Couldn't find stream information.\n";
        return 0;
    }
	
	for (int i=0; i < avFmtCtx->nb_streams; ++i) {
        if (avFmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoIndex = i;
            break;
        }
    }

    if (videoIndex == -1 || videoIndex >= avFmtCtx->nb_streams) {
        std::cout << "Didn't find a video stream.\n";
        return 0;
    }
    
    avRawCodecCtx = avFmtCtx->streams[videoIndex]->codec;
    avDecodec = avcodec_find_decoder(avRawCodecCtx->codec_id);
    if (avDecodec == NULL) {
        std::cout << "Codec not found.\n";
        return 0;
    }
    if (avcodec_open2(avRawCodecCtx, avDecodec, NULL) < 0) {
        std::cout << "Could not open decodec . \n";
        return 0;
    }	

    swsCtx = sws_getContext(avRawCodecCtx->width,
        avRawCodecCtx->height,
        avRawCodecCtx->pix_fmt,
        avRawCodecCtx->width,
        avRawCodecCtx->height,
        AV_PIX_FMT_YUV420P,
        SWS_BICUBIC, NULL, NULL, NULL);

    
    avYUVFrame = av_frame_alloc();
    int yuvLen = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, avRawCodecCtx->width, avRawCodecCtx->height,1);
    uint8_t *yuvBuf = new uint8_t[yuvLen];
    av_image_fill_arrays(avYUVFrame->data, avYUVFrame->linesize, (uint8_t *)yuvBuf, AV_PIX_FMT_YUV420P, avRawCodecCtx->width, avRawCodecCtx->height,1); 

    avYUVFrame->width = avRawCodecCtx->width;
    avYUVFrame->height = avRawCodecCtx->height;
    avYUVFrame->format = AV_PIX_FMT_YUV420P;

    avEncodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if(!avEncodec) {
      std::cout << "h264 codec not found\n";
      return 0;
    }
    
    avEncoderCtx = avcodec_alloc_context3(avEncodec);
    
    avEncoderCtx->codec_id = AV_CODEC_ID_H264;
    avEncoderCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    avEncoderCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    avEncoderCtx->width = width;
    avEncoderCtx->height = height;
    avEncoderCtx->time_base.num = 1;
    avEncoderCtx->time_base.den = 75;
    avEncoderCtx->bit_rate = 128*1024*8;
    avEncoderCtx->gop_size = 250;
    avEncoderCtx->qmin = 1;
    avEncoderCtx->qmax = 10;

    AVDictionary *param = 0;
    
    av_dict_set(&param, "preset", "superfast", 0);
    av_dict_set(&param, "tune", "zerolatency", 0);

    if (avcodec_open2(avEncoderCtx, avEncodec, &param) < 0)  {
        std::cout << "Failed to open video encoder!\n";
        return 0;
    }
    return 0;
}

int ScreenRecorder::CaptureVideoData(){

    int got_picture = 0;
    int ret = 0;
    int flag = 0;
    int bufLen = 0;
    uint8_t * outBuf = NULL;
    
    bufLen = width * height * 3;
    outBuf = (uint8_t*)malloc(bufLen);
    
    AVFrame *avOutFrame;
    avOutFrame = av_frame_alloc();
    av_image_fill_arrays(avOutFrame->data, avOutFrame->linesize, (uint8_t *)outBuf, avEncoderCtx->pix_fmt, avEncoderCtx->width, avEncoderCtx->height,1);
    
    AVPacket* pkt = av_packet_alloc();    

    FILE *h264Fp = fopen("out.mp4","wb");

    while (true) {
        if (av_read_frame(avFmtCtx, avRawPkt) >= 0)  {
            if (avRawPkt->stream_index == videoIndex) {
                flag = avcodec_decode_video2(avRawCodecCtx, avOutFrame, &got_picture, avRawPkt);
                if (flag < 0) {
                    break;
                }
                if (got_picture > 0) {
                    sws_scale(swsCtx, avOutFrame->data, avOutFrame->linesize, 0, avRawCodecCtx->height, avYUVFrame->data, avYUVFrame->linesize);
                    got_picture = 0;
                    flag = avcodec_encode_video2(avEncoderCtx, pkt, avYUVFrame, &got_picture);
                    if (flag >= 0) {
                        if (got_picture > 0) {
                            int w = fwrite(pkt->data, 1, pkt->size, h264Fp);
                        }
                    }
                    av_packet_unref(pkt);
                    av_packet_unref(avRawPkt);
                }
            }
        }

    }
    return 0;
}
