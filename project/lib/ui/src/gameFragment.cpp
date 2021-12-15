#include "gameFragment.h"
#include "fragmentThemeStyle.h"

#include <QHBoxLayout>
#include <QString>
#include <QDir>

namespace fragment {

GameFragment::GameFragment()
    : _player(new media::MediaPlayer)
    , _backBut(new QPushButton("Go back\nStop testing"))
{
    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));

    QHBoxLayout* mainHLayout = new QHBoxLayout(this);
    mainHLayout->addWidget(_backBut);
    mainHLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(mainHLayout);

    _player->moveToThread(&playerThread);
    connect(&playerThread, &QThread::finished, _player, &QObject::deleteLater);
    connect(this, &GameFragment::play, _player, &media::MediaPlayer::start);
    connect(_player, &media::MediaPlayer::finished, this, &GameFragment::onBack);
    playerThread.start();

    QDir vidfile;
    vidfile.cd("project/lib/ui/media/");

    emit play(vidfile.absoluteFilePath("vid.mp4"));

    _timer = new QTimer(this);
    _timer->setInterval(1000.f / GameFragment::fps);
    _timer->start();

    connect(_backBut, &QPushButton::clicked, this, &GameFragment::onBack);
    connect(_timer, &QTimer::timeout, this, &GameFragment::timerOutEvent);
}

void GameFragment::timerOutEvent()
{
    /* TODO(Paul): place to merge */

    // mouse: _player->getmouse();
    // buttons: _player->getbutts();
    // cursor: [ cursor().pos().x() ; cursor().pos().y() ]
}

void GameFragment::onBack()
{
    emit back();
}

GameFragment::~GameFragment()
{
    playerThread.quit();
    playerThread.wait();
    delete _backBut;
    delete _timer;
}

} // namespace fragment
