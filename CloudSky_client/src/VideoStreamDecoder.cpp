#include "VideoStreamDecoder.h"
VideoStreamDecoder::VideoStreamDecoder()
{
	this->video_codec=0;
	this->videoframe=0;
	this->img_convert_ctx=0;
	this->outputHeight=800;
	this->outputWidth=600;
}
VideoStreamDecoder::~VideoStreamDecoder()
{
	if(this->video_codec_context!=0)
	{
		avcodec_close(video_codec_context);
		video_codec=0;

	}
	if(this->video_codec!=0)
	{
		av_freep(this->video_codec);
		this->video_codec=0;
	}
	av_free_packet(&videoavpkt);
}


bool VideoStreamDecoder::decodeVideoFrame(char*data,int size,AVFrame **getframe)
{
	int len, got_frame;
	videoavpkt.data = (uint8_t*)data;
	videoavpkt.size=size;
	//len = avcodec_decode_video2(this->video_codec_context, videoframe, &got_frame, &videoavpkt);
	if(len<0)
	{
		printf("Error happen when decoding\n");
		return false;
	}
	return true;
}

bool VideoStreamDecoder::openVideoCodec()
{

	this->video_codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (!this->video_codec) 
	{
		printf( "video codec not found/n");
		return false;
    }
	this->video_codec_context = avcodec_alloc_context3(this->video_codec);
	if (avcodec_open2(this->video_codec_context, this->video_codec,NULL) < 0) 
	{
        printf( "could not open video codec\n");
        return false;
    }
	return true;
}

bool VideoStreamDecoder::initDecoder()
{

	if(!this->openVideoCodec())
	{
		printf("Can open add video stream@!\n");
	    return false;
	}
	videoframe = av_frame_alloc();
    if (!videoframe) {
        printf("Could not allocate video frame\n");
        return false;
    }
	av_init_packet(&videoavpkt);
	return true;
}

bool VideoStreamDecoder::setupSwscale()
{
	return true;
}
