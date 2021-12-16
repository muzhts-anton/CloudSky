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

namespace media {

class MediaPlayer : public QObject {
    Q_OBJECT
public:
    MediaPlayer();
    ~MediaPlayer();
    void initInputStream(const std::string path);
    void play();

    bool* getbutts() { return _butts; }
    bool* getmouse() { return _mouse; }

private:
    void onKeyDown(SDL_Keycode sym);
    void onKeyUp(SDL_Keycode sym);
    void onLeftMouseButtonPress();
    void onRightMouseButtonPress();
    void onLeftMouseButtonRelease();
    void onRightMouseButtonRelease();

public slots:
    void start();

signals:
    void finished();

private:
    enum class Buttons {
        A = 0,
        W,
        S,
        D,
        SPACE,
        Q,
        E,
        F,
        ESC,
        COUNT,
    };
    enum class Mouse {
        LEFT = 0,
        RIGHT,
        COUNT,
    };

private:
    AVFormatContext* _pFormatCtx = nullptr;
    AVCodecContext* _pCodecCtx = nullptr;
    AVCodec* _pCodec = nullptr;
    AVFrame* _pFrame = nullptr;
    AVFrame* _pFrameRGB = nullptr;
    size_t _buffer_size;
    AVFrame* _pict = nullptr;
    struct SwsContext* _swsCtx = nullptr;
    AVPacket* _pPacket = nullptr;
    std::vector<uint8_t> _buffer;
    int _videoStream = -1;
    SDL_Window* _screen = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Texture* _texture = nullptr;
    SDL_Event _event;
    bool _quit;
    AVDictionary* _opts = nullptr;

    void initAndCreateWindowSDL();
    void updateScreen(); 
    void close();

    bool _butts[(size_t)Buttons::COUNT];
    bool _mouse[(size_t)Mouse::COUNT];
};

} // namespace media
#endif