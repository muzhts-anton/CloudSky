#include "SDLWidget.h"

#include <iostream>

namespace media {

MediaPlayer::MediaPlayer()
{
    for (size_t i = 0; i < (size_t)Buttons::COUNT; ++i)
        _butts[i] = false;

    avformat_network_init();
}

void MediaPlayer::start(QString path)
{
    this->initInputStream(path.toStdString());
    this->play();
}

MediaPlayer::~MediaPlayer()
{
    av_frame_free(&pFrame);
    av_free(pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

void MediaPlayer::initInputStream(const std::string path)
{
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (ret != 0) {
        std::cout << "Cannot not initialize. " << SDL_GetError() << std::endl;
    }
    std::cout << "before\n";
    pFormatCtx = avformat_alloc_context();
    
    //AVInputFormat* input = av_find_input_format("mp4");
    

    //AVInputFormat *pMjpegFormat = av_find_input_format("mp.4");
    //av_dict_set(&opts, "buffer_size", "204800", 0);
    // av_dict_set(&opts, "protocol_whitelist", "udp", 0);
    // av_dict_set(&opts, "rtsp_transport", "udp", 0);
    //std::string path2 = path.c_str() + (std::string)"mode=listener";
    //std::cout << path.c_str();
    std::cout << avformat_open_input(&pFormatCtx, path.c_str(), 0, &opts);
    std::cout << "after\n";

    if (ret < 0) {
        std::cout << "[LOG]: Error while open file: " << path << std::endl;
    }

    ret = avformat_find_stream_info(pFormatCtx, NULL);
    if (ret < 0) {
        std::cout << "Could not find stream information %s\n";
    }

    av_dump_format(pFormatCtx, 0, path.c_str(), 0);
    for (int i = 0; i < (int)pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1) {
        std::cout << "Didnt find video stream\n";
    }

    pCodec = avcodec_find_decoder(pFormatCtx->streams[videoStream]->codecpar->codec_id);
    if (pCodec == NULL) {
        std::cout << "Unsupported codec!\n";
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    ret = avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStream]->codecpar);
    if (ret != 0) {
        std::cout << "Could not copy codec context\n";
    }

    ret = avcodec_open2(pCodecCtx, pCodec, NULL);
    if (ret < 0) {
        std::cout << "Could not open codec.\n";
    }
}

void MediaPlayer::play()
{

    pFrame = av_frame_alloc();
    if (pFrame == NULL) {
        std::cout << "Cannot allocate frame\n";
    }

    // pCodecCtx->width = 1024;
    // pCodecCtx->height = 768;
    screen = SDL_CreateWindow(
        "SDL Video Player",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!screen) {
        std::cout << "Cannot set video mode\n";
    }

    SDL_GL_SetSwapInterval(0);

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_YV12,
        SDL_TEXTUREACCESS_STREAMING,
        pCodecCtx->width,
        pCodecCtx->height);

    pPacket = av_packet_alloc();
    if (pPacket == NULL) {
        std::cout << "Could not alloc packet,\n";
    }

    swsCtx = sws_getContext(
        pCodecCtx->width,
        pCodecCtx->height,
        pCodecCtx->pix_fmt,
        pCodecCtx->width,
        pCodecCtx->height,
        AV_PIX_FMT_YUV420P,
        SWS_BILINEAR,
        NULL,
        NULL,
        NULL);

    buffer_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 32);
    buffer.reserve(buffer_size * sizeof(uint8_t));

    AVFrame* pict = av_frame_alloc();

    av_image_fill_arrays(
        pict->data,
        pict->linesize,
        buffer.data(),
        AV_PIX_FMT_YUV420P,
        pCodecCtx->width,
        pCodecCtx->height,
        32);

    quit = false;
    while (av_read_frame(pFormatCtx, pPacket) >= 0 && !quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT: {
            quit = true;
            SDL_VideoQuit();
            SDL_Quit();
            emit finished();
            break;
        }
        case SDL_KEYDOWN: {
            onKeyDown(event.key.keysym.sym);
            break;
        }

        case SDL_KEYUP: {
            onKeyUp(event.key.keysym.sym);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch (event.button.button) {
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
            switch (event.button.button) {
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

        if (pPacket->stream_index == videoStream) {
            int ret = avcodec_send_packet(pCodecCtx, pPacket);
            if (ret < 0) {
                std::cout << "Error sending packet for decoding.\n";
            }

            while (ret >= 0) {
                ret = avcodec_receive_frame(pCodecCtx, pFrame);

                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    std::cout << "Error while decoding.\n";
                }

                sws_scale(
                    swsCtx,
                    (uint8_t const* const*)pFrame->data,
                    pFrame->linesize,
                    0,
                    pCodecCtx->height,
                    pict->data,
                    pict->linesize);

                double fps = av_q2d(pFormatCtx->streams[videoStream]->r_frame_rate);
                std::cout << fps << std::endl;
                double sleep_time = 1.0/(double)fps;
                SDL_Delay((1000 * sleep_time));
                SDL_Rect rect;
                rect.x = 0;
                rect.y = 0;
                rect.w = pCodecCtx->width;
                rect.h = pCodecCtx->height;
                // printf(
                //     "Frame %c (%d) pts %ld dts %ld key_frame %d [coded_picture_number %d, display_picture_number %d, %dx%d]\n",
                //     av_get_picture_type_char(pFrame->pict_type),
                //     pCodecCtx->frame_number,
                //     pFrame->pts,
                //     pFrame->pkt_dts,
                //     pFrame->key_frame,
                //     pFrame->coded_picture_number,
                //     pFrame->display_picture_number,
                //     pCodecCtx->width,
                //     pCodecCtx->height
                // );
                SDL_UpdateYUVTexture(
                    texture,
                    &rect,
                    pict->data[0],
                    pict->linesize[0],
                    pict->data[1],
                    pict->linesize[1],
                    pict->data[2],
                    pict->linesize[2]);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(
                    renderer,
                    texture,
                    NULL,
                    NULL);
                SDL_ShowCursor(SDL_ENABLE);
                SDL_RenderPresent(renderer);
            }
        }
        av_packet_unref(pPacket);
    }

    av_frame_free(&pict);
    av_free(pict);
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
