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
#include <QString>
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
    void start(QString path);

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
    AVFormatContext* pFormatCtx = nullptr;
    AVCodecContext* pCodecCtx = nullptr;
    const AVCodec* pCodec = nullptr;
    AVFrame* pFrame = nullptr;
    AVFrame* pFrameRGB = nullptr;
    size_t buffer_size;
    struct SwsContext* swsCtx = nullptr;
    AVPacket* pPacket = nullptr;
    std::vector<uint8_t> buffer;
    int videoStream = -1;
    SDL_Window* screen = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Event event;
    bool quit;
    AVDictionary* opts = nullptr;

    bool _butts[(size_t)Buttons::COUNT];
    bool _mouse[(size_t)Mouse::COUNT];
};

} // namespace media
#endif