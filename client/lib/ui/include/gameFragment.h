#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "baseFragment.h"
#include "SDLWidget.h"
#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QtGui>
#include <QThread>
#include <QString>

namespace fragment {

class GameFragment : public BaseFragment {
    Q_OBJECT
    QThread playerThread;

    static constexpr short fps = 40;

public:
    GameFragment();
    ~GameFragment();

public slots:
    void timerOutEvent();
    void onBack();

signals:
    void play(QString path);

private:
    TCPClient::TCPClientSocket TCPSocket;
    media::MediaPlayer* _player;
    QPushButton* _backBut;
    QTimer* _timer;
};

} // namespace fragment

#endif // GAMEFRAGMENT_H