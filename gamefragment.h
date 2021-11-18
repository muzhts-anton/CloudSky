#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "basefragment.h"

#include <QMediaWidget>
#include <QVideoPlayer>

class GameFragment : public BaseFragment
{
    Q_OBJECT
public:
    GameFragment();

private slots:
    void keyPressEvent(QKeyEvent *event);

private:
    void playVideo();

private:
    QVideoWidget *videoWidget;
    QMediaPlayer *player;
};

#endif // GAMEFRAGMENT_H
