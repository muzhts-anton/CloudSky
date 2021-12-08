#ifndef SDLWIDGET_H
#define SDLWIDGET_H

extern "C" {

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#include <QWidget>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class MediaPlayer : public QObject {
    Q_OBJECT
public:
    MediaPlayer();
    ~MediaPlayer();
    void initInputStream(const std::string path);
    void play();
    void saveFrame(AVFrame* frame, size_t width, size_t height, std::string path);

signals:
    void finished();

public slots:
    void go();

private:
    AVFormatContext* pFormatCtx = NULL;
    AVCodecContext* pCodecCtx = NULL;
    AVCodec* pCodec = NULL;
    AVFrame* pFrame = NULL;
    AVFrame* pFrameRGB = NULL;
    size_t buffer_size;
    struct SwsContext* swsCtx = NULL;
    AVPacket* pPacket = NULL;
    std::vector<uint8_t> buffer;
    int videoStream = -1;
    SDL_Window* screen = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    SDL_Event event;
};

#endif