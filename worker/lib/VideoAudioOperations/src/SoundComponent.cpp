#include "../include/SoundComponent.h"

SoundComponent::SoundComponent(){
	this->frame=0;
	this->swr_ctx=0;
	this->audio_codec=0;
	this->audio_codec_context=0;
}
SoundComponent::~SoundComponent(){
    if(frame!=0)
	{
		av_frame_free(&frame);
		frame=0;
	}
}
bool SoundComponent::initSoundComponent(){
    if(!openAudioEncoder())
	{
		printf("Failed to init audio Encoder\n");
		return false;
	}

	frame=av_frame_alloc();
	if(frame==0)
	{
		printf("Failed to init frame in audio\n");
		return false;
	}
	return true;
}
void SoundComponent::startFrameLoop(){
    return;
}
void SoundComponent::stopFrameLoop(){
    run_flag = false;
}
bool SoundComponent::write_audio_frame(AVFrame *frame)
{

	AVPacket pkt;
    int got_output,ret;
    pkt.data = NULL;  
    pkt.size = 0;
	ret =  avcodec_send_frame(this->audio_codec_context, frame);
	if (ret < 0) 
	{
        printf( "Error encoding audio frame\n");
        return false;
    }
	return true;

}


bool SoundComponent::openAudioEncoder()
{

	this->audio_codec_context=avcodec_alloc_context3(this->audio_codec);
	this->audio_codec_context->sample_fmt  = AV_SAMPLE_FMT_S16;
    this->audio_codec_context->bit_rate    = 64000;
    this->audio_codec_context->sample_rate = 48000;
    this->audio_codec_context->channels    = 2;
	this->audio_codec_context->channel_layout=AV_CH_LAYOUT_STEREO;
	if( avcodec_open2(this->audio_codec_context, this->audio_codec, NULL)<0)
	{
		printf( "could not open audio codec\n");
        return false;
	}
	return true;
}

void SoundComponent::cleanupEncoder()
{

	if(this->audio_codec_context!=0)
	{
		avcodec_close(this->audio_codec_context);
		av_freep(&this->audio_codec_context);
	}
	if(this->audio_codec!=0)
	{
		av_freep(&this->audio_codec);
		this->audio_codec=0;
	}

}