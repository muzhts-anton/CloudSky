#include "AudioStreamDecoder.h"
AudioStreamDecoder::AudioStreamDecoder()
{
	this->outputaudioFrame=0;
	this->audio_codec=0;
	this->audioframe=0;

}
AudioStreamDecoder::~AudioStreamDecoder()
{
	if(this->audio_codec_context!=0)
	{
		avcodec_close(audio_codec_context);
		this->audio_codec=0;
	}
	if(this->audio_codec!=0)
	{
		av_freep(this->audio_codec);
		this->audio_codec=0;
	}
	if(this->audioframe!=0)
	{
		av_frame_free(&audioframe);
		audioframe=0;
	}
	if(this->outputaudioFrame!=0)
	{
		av_frame_free(&outputaudioFrame);
		outputaudioFrame=0;
	}
	av_free_packet(&audioavpkt);
}

bool AudioStreamDecoder::decodeAudioFrame(char*indata,int insize,AVFrame **outdata,int *outSize)
{
	return true;
}

bool AudioStreamDecoder::openAudioCodec()
{
	this->audio_codec=avcodec_find_decoder(AV_CODEC_ID_OPUS);
	if (!this->audio_codec) 
	{
		printf( "audio codec not found/n");
		return false;
	}
	this->audio_codec_context = avcodec_alloc_context3(this->audio_codec);
	this->audio_codec_context->channels=2;
	this->audio_codec_context->sample_rate=480000;

	if (avcodec_open2(this->audio_codec_context, this->audio_codec,NULL) < 0) 
	{
        printf( "could not open audio codec\n");
        return false;
    }
	return true;
}


bool AudioStreamDecoder::initDecorder()
{

	if(!this->openAudioCodec())
	{
		printf("Can open add video stream@!\n");
	    return false;
	}
	audioframe = av_frame_alloc();
	outputaudioFrame=av_frame_alloc();
    if (!audioframe || !outputaudioFrame) {
        printf("Could not allocate video frame\n");
        return false;
    }
	//av_init_packet(&audioavpkt);
	return true;
}