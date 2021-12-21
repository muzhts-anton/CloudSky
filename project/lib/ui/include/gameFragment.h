#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "baseFragment.h"
#include "SDLWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QtGui>
#include <QThread>
#include <QString>
#include <QPointer>
#include <QHBoxLayout>

namespace fragment {

class GameFragment : public BaseFragment {
    Q_OBJECT
    QThread playerThread;

    static constexpr short fps = 80;

public:
    GameFragment();
    ~GameFragment();

public slots:
    void timerOutEvent();
    void onBack();

signals:
    void play(QString path);

private:
    QPointer<media::MediaPlayer> _player;
    QPointer<QPushButton> _backBut;
    QPointer<QTimer> _timer;

    QPointer<QHBoxLayout> _mainHLayout;
};

} // namespace fragment

#endif // GAMEFRAGMENT_H