#include "gameFragment.h"
#include "messageOperations.h"


#include <QHBoxLayout>
#include <QString>
#include <QDir>
#include <unistd.h>

namespace fragment {

GameFragment::GameFragment()
    : TCPSocket(8080, "10.147.18.164")
    , _player(new media::MediaPlayer)
    , _backBut(new QPushButton("Go back\nStop testing"))
{
    TCPSocket.activateSocket();
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

    // QDir vidfile;
    // vidfile.cdUp();
    // vidfile.cd("lib/ui/media/");
    usleep(1000000);
    emit play(QString("udp://10.147.18.164:8080"));

    _timer = new QTimer(this);
    _timer->setInterval(1000.f / GameFragment::fps);
    _timer->start();

    connect(_backBut, &QPushButton::clicked, this, &GameFragment::onBack);
    connect(_timer, &QTimer::timeout, this, &GameFragment::timerOutEvent);
}

void GameFragment::timerOutEvent()
{
    std::string fileToSendPath = "buttonsCoords.bin";

    bool *butts = _player->getbutts();
    bool *mouse = _player->getmouse();
    KeyboardMouse::ButtonsCoords message;

    for (size_t i = 0; i < buttonQuanity; ++i)
        (butts[i]) ? message.add_buttonpressed(true) : message.add_buttonpressed(false);
 
    message.set_xcoord(cursor().pos().x());
    message.set_ycoord(cursor().pos().y());
    
    for (size_t i = 0; i < coordQuanity; ++i)
        (mouse[i]) ? message.add_mousebuttons(true) : message.add_mousebuttons(false);

    ViktorDev::SendInteraction SendM(fileToSendPath, message);
    SendM.sendIt();
    try {
        TCPSocket.transmitFile(fileToSendPath);
    } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
    }
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
