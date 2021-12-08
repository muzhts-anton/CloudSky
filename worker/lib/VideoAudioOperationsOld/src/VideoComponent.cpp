#include "../include/VideoComponent.h"

VideoComponent::VideoComponent()
{

	frameCounter=0;
	this->outputHeight=800;
	this->outputWidth=600;
	this->video_codec_context=0;
	this->video_codec=0;
	this->bandwidth=4000000;
	img_convert_ctx=NULL;
}
VideoComponent::~VideoComponent()
{
	if(raw_frame!=NULL)
	{
		av_freep(&raw_frame->data[0]);
		av_frame_free(&raw_frame);
		raw_frame=NULL;
	}
	
	cleanupEncoder();
}

bool VideoComponent::initVideoComponent()
{
	if(!openVideoEncoder())
	{
		printf("Video Encoder Failed\n");
		return false;
	}
	return true;
}
void VideoComponent::startFrameLoop()
{
	return;
}
void VideoComponent::stopFrameLoop()
{
    return;
}
bool VideoComponent::setup_scale(int in_width,int in_height)
{
	return true;
}

void VideoComponent::setQuality(int width,int height,int bandwidth)
{
	this->outputWidth=width;
	this->outputHeight=height;
	this->bandwidth=bandwidth;
}
bool VideoComponent::sendOutFrame(AVPacket *pkt)
{
	return true;
}

bool VideoComponent::openVideoEncoder()
{
	
	this->video_codec_context=avcodec_alloc_context3(this->video_codec);
	this->video_codec_context->bit_rate = this->bandwidth;
	this->video_codec_context->width = this->outputWidth;
	this->video_codec_context->height = this->outputHeight;
	this->video_codec_context->gop_size=0;
	this->video_codec_context->max_b_frames=0;
	this->video_codec_context->me_range = 16;
    this->video_codec_context->max_qdiff = 4;
    this->video_codec_context->qmin = 10;
    this->video_codec_context->qmax = 51;
	this->video_codec_context->refs=1;
	this->video_codec_context->dia_size=1;
	this->video_codec_context->keyint_min=46;
	this->video_codec_context->active_thread_type= FF_THREAD_SLICE;
	this->video_codec_context->thread_type=FF_THREAD_SLICE;
	this->video_codec_context->thread_count=4;
	this->video_codec_context->slices=4;
	
	this->video_codec_context->time_base.den = 25;
    this->video_codec_context->time_base.num = 1;
	if( avcodec_open2(this->video_codec_context, this->video_codec, NULL)<0)
	{
		printf( "could not open video codec\n");
        return false;
	}
	return true;
}
void VideoComponent::cleanupEncoder()
{
	if(this->video_codec_context!=NULL)
	{
		avcodec_close(this->video_codec_context);
		av_freep(&(this->video_codec_context));
	}
	if(this->video_codec!=NULL)
	{
		av_freep(&video_codec);
	}

}
