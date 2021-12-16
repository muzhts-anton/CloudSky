#include "SDLWidget.h"

#include <iostream>

namespace media {

MediaPlayer::MediaPlayer()
{
    for (size_t i = 0; i < (size_t)Buttons::COUNT; ++i)
        _butts[i] = false;

    avformat_network_init();
}

void MediaPlayer::start()
{
    this->initInputStream("/home/konstantin/rep_cpp/tmpPlayer/CloudSky/project/lib/ui/media/vid.mp4");
    this->play();
}

MediaPlayer::~MediaPlayer()
{
    av_frame_free(&_pFrame);
    av_free(_pFrame);
    avcodec_close(_pCodecCtx);
    avformat_close_input(&_pFormatCtx);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyTexture(_texture);
    SDL_DestroyWindow(_screen);
    SDL_Quit();
}

void MediaPlayer::initInputStream(const std::string path)
{
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (ret != 0) {
        std::cerr << "[ERROR] Cannot not initialize. " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "before\n";
    _pFormatCtx = avformat_alloc_context();

    av_dict_set(&_opts, "buffer_size", "204800", 0);
    av_dict_set(&_opts, "max_interleave_delta", "1", 0);
    ret = avformat_open_input(&_pFormatCtx, path.c_str(), nullptr, &_opts);
    std::cout << "after\n";

    if (ret < 0) {
        std::cerr << "[ERROR] Error while open file: " << path << std::endl;
    }

    ret = avformat_find_stream_info(_pFormatCtx, nullptr);
    if (ret < 0) {
        std::cerr << "[ERROR] Could not find stream information %s\n";
    }

    av_dump_format(_pFormatCtx, 0, path.c_str(), 0);
    for (int i = 0; i < (int)_pFormatCtx->nb_streams; i++) {
        if (_pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            _videoStream = i;
            break;
        }
    }
    if (_videoStream == -1) {
        std::cerr << "[ERROR] Didnt find video stream\n";
    }

    _pCodec = avcodec_find_decoder(_pFormatCtx->streams[_videoStream]->codecpar->codec_id);
    if (_pCodec == nullptr) {
        std::cerr << "[ERROR] Unsupported codec!\n";
    }

    _pCodecCtx = avcodec_alloc_context3(_pCodec);
    ret = avcodec_parameters_to_context(_pCodecCtx, _pFormatCtx->streams[_videoStream]->codecpar);
    if (ret != 0) {
        std::cerr << "[ERROR] Could not copy codec context\n";
    }

    ret = avcodec_open2(_pCodecCtx, _pCodec, nullptr);
    if (ret < 0) {
        std::cerr << "[ERROR] Could not open codec.\n";
    }
}

void MediaPlayer::play()
{

    _pFrame = av_frame_alloc();
    if (_pFrame == nullptr) {
        std::cerr << "[ERROR] Cannot allocate frame\n";
        return;
    }

    _pict = av_frame_alloc();

    // pCodecCtx->width = 1024;
    // pCodecCtx->height = 768;
    initAndCreateWindowSDL();

    _quit = false;
    while (av_read_frame(_pFormatCtx, _pPacket) >= 0 && !_quit) {
        SDL_PollEvent(&_event);
        switch (_event.type) {
        case SDL_QUIT: {
            _quit = true;
            SDL_VideoQuit();
            SDL_Quit();
            emit finished();
            break;
        }
        case SDL_KEYDOWN: {
            onKeyDown(_event.key.keysym.sym);
            break;
        }

        case SDL_KEYUP: {
            onKeyUp(_event.key.keysym.sym);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch (_event.button.button) {
            case SDL_BUTTON_LEFT: {
                onLeftMouseButtonPress();
                break;
            }
            case SDL_BUTTON_RIGHT: {
                onRightMouseButtonPress();
                break;
            }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP: {
            switch (_event.button.button) {
            case SDL_BUTTON_LEFT: {
                onLeftMouseButtonRelease();
                break;
            }
            case SDL_BUTTON_RIGHT: {
                onRightMouseButtonRelease();
                break;
            }
            }
            break;
        }
        default:
            break;
        }

        if (_pPacket->stream_index == _videoStream) {
            int ret = avcodec_send_packet(_pCodecCtx, _pPacket);
            if (ret < 0) {
                std::cerr << "[ERROR] Error sending packet for decoding.\n";
            }

            while (ret >= 0) {
                ret = avcodec_receive_frame(_pCodecCtx, _pFrame);

                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    std::cerr << "[ERROR] Error while decoding.\n";
                }

                sws_scale(
                    _swsCtx,
                    const_cast<uint8_t const* const*>(_pFrame->data),
                    _pFrame->linesize,
                    0,
                    _pCodecCtx->height,
                    _pict->data,
                    _pict->linesize);

                updateScreen();
                
                
            }
        }
        av_packet_unref(_pPacket);
    }

    av_frame_free(&_pict);
    av_free(_pict);
}

void MediaPlayer::initAndCreateWindowSDL(){
    _screen = SDL_CreateWindow(
        "SDL Video Player",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!_screen) {
        std::cerr << "[ERROR] Cannot set video mode\n";
        return;
    }

    SDL_GL_SetSwapInterval(0);

    _renderer = SDL_CreateRenderer(_screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

    _texture = SDL_CreateTexture(
        _renderer,
        SDL_PIXELFORMAT_YV12,
        SDL_TEXTUREACCESS_STREAMING,
        _pCodecCtx->width,
        _pCodecCtx->height);

    _pPacket = av_packet_alloc();
    if (_pPacket == nullptr) {
        std::cerr << "[ERROR] Could not alloc packet,\n";
    }

    _swsCtx = sws_getContext(
        _pCodecCtx->width,
        _pCodecCtx->height,
        _pCodecCtx->pix_fmt,
        _pCodecCtx->width,
        _pCodecCtx->height,
        AV_PIX_FMT_YUV420P,
        SWS_BILINEAR,
        nullptr,
        nullptr,
        nullptr);

    _buffer_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, _pCodecCtx->width, _pCodecCtx->height, 32);
    _buffer.reserve(_buffer_size * sizeof(uint8_t));

    av_image_fill_arrays(
        _pict->data,
        _pict->linesize,
        _buffer.data(),
        AV_PIX_FMT_YUV420P,
        _pCodecCtx->width,
        _pCodecCtx->height,
        32);
}

void MediaPlayer::updateScreen(){
    double fps = av_q2d(_pFormatCtx->streams[_videoStream]->r_frame_rate);
    double sleep_time = 1.0/(double)fps;
    SDL_Delay((1000 * sleep_time));
    SDL_Rect rect;
                rect.x = 0;
                rect.y = 0;
                rect.w = _pCodecCtx->width;
                rect.h = _pCodecCtx->height;
                // printf(
                //     "Frame %c (%d) pts %ld dts %ld key_frame %d [coded_picture_number %d, display_picture_number %d, %dx%d]\n",
                //     av_get_picture_type_char(pFrame->pict_type),
                //     _pCodecCtx->frame_number,
                //     pFrame->pts,
                //     pFrame->pkt_dts,
                //     pFrame->key_frame,
                //     pFrame->coded_picture_number,
                //     pFrame->display_picture_number,
                //     _pCodecCtx->width,
                //     _pCodecCtx->height
                // );
                SDL_UpdateYUVTexture(
                    _texture,
                    &rect,
                    _pict->data[0],
                    _pict->linesize[0],
                    _pict->data[1],
                    _pict->linesize[1],
                    _pict->data[2],
                    _pict->linesize[2]);
                SDL_RenderClear(_renderer);
                SDL_RenderCopy(
                    _renderer,
                    _texture,
                    nullptr,
                    nullptr);
                SDL_ShowCursor(SDL_ENABLE);
                SDL_RenderPresent(_renderer);
}

// tracing
void MediaPlayer::onKeyDown(SDL_Keycode sym)
{
    switch (sym) {
    case SDLK_a: {
        _butts[(size_t)Buttons::A] = true;
        break;
    }
    case SDLK_w: {
        _butts[(size_t)Buttons::W] = true;
        break;
    }
    case SDLK_s: {
        _butts[(size_t)Buttons::S] = true;
        break;
    }
    case SDLK_d: {
        _butts[(size_t)Buttons::D] = true;
        break;
    }
    case SDLK_SPACE: {
        _butts[(size_t)Buttons::SPACE] = true;
        break;
    }
    case SDLK_q: {
        _butts[(size_t)Buttons::Q] = true;
        break;
    }
    case SDLK_e: {
        _butts[(size_t)Buttons::E] = true;
        break;
    }
    case SDLK_f: {
        _butts[(size_t)Buttons::F] = true;
        break;
    }
    case SDLK_ESCAPE: {
        _butts[(size_t)Buttons::ESC] = true;
        break;
    }
    default:
        break;
    }
}

void MediaPlayer::onKeyUp(SDL_Keycode sym)
{
    switch (sym) {
    case SDLK_a: {
        _butts[(size_t)Buttons::A] = false;
        break;
    }
    case SDLK_w: {
        _butts[(size_t)Buttons::W] = false;
        break;
    }
    case SDLK_s: {
        _butts[(size_t)Buttons::S] = false;
        break;
    }
    case SDLK_d: {
        _butts[(size_t)Buttons::D] = false;
        break;
    }
    case SDLK_SPACE: {
        _butts[(size_t)Buttons::SPACE] = false;
        break;
    }
    case SDLK_q: {
        _butts[(size_t)Buttons::Q] = false;
        break;
    }
    case SDLK_e: {
        _butts[(size_t)Buttons::E] = false;
        break;
    }
    case SDLK_f: {
        _butts[(size_t)Buttons::F] = false;
        break;
    }
    case SDLK_ESCAPE: {
        _butts[(size_t)Buttons::ESC] = false;
        break;
    }
    default:
        break;
    }
}

void MediaPlayer::onLeftMouseButtonPress()
{
    _mouse[(size_t)Mouse::LEFT] = true;
}

void MediaPlayer::onRightMouseButtonPress()
{
    _mouse[(size_t)Mouse::RIGHT] = true;
}

void MediaPlayer::onLeftMouseButtonRelease()
{
    _mouse[(size_t)Mouse::LEFT] = false;
}

void MediaPlayer::onRightMouseButtonRelease()
{
    _mouse[(size_t)Mouse::RIGHT] = false;
}

} // namespace media
