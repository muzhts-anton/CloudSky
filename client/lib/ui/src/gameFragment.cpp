#include "gameFragment.h"
#include "messageOperations.h"

#include <QHBoxLayout>
#include <QString>
#include <QDir>

namespace fragment {

GameFragment::GameFragment()
    : _player(new media::MediaPlayer)
    , _backBut(new QPushButton("Go back\nStop testing"))
{
    _backBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");

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
    vidfile.cdUp();
    vidfile.cd("lib/ui/media/");

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

    bool *butts = _player->getbutts();
    bool *mouse = _player->getmouse();
    std::string file_path = "buttonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;

    for (size_t i = 0; i < BUTTON_QUANITY; ++i)
        (butts[i]) ? message.add_buttonpressed(true) : message.add_buttonpressed(false);
 
    message.set_xcoord(cursor().pos().x());
    message.set_ycoord(cursor().pos().y());
    
    for (size_t i = 0; i < COORD_QUANITY; ++i)
        (mouse[i]) ? message.add_mousebuttons(true) : message.add_mousebuttons(false);

    ViktorDev::SendInteraction SendM(file_path, message);
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
