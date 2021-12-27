#include "gameFragment.h"
#include "messageOperations.h"
#include "fragmentThemeStyle.h"

#include <QString>
#include <QDir>
#include <unistd.h>

constexpr const char *serverIP = "10.147.18.164";
constexpr int serverPort = 8085;
constexpr int workerPort = 8080;

namespace fragment {

GameFragment::GameFragment()
    : TCPSocket(serverPort, serverIP)
    , _player(new media::MediaPlayer)
    , _backBut(new QPushButton("Go back\nStop testing"))
    , _timer(new QTimer(this))
{
    TCPSocket.activateSocket();
    std::string newIP = TCPSocket.receiveIP();
    std::cout << "Переключаемся на IP " << newIP << std::endl;
    usleep(1000000);
    TCPSocket.changeIP(newIP);
    TCPSocket.activateSocket();
    TCPSocket.sendIP();
    usleep(1000000);

    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));

    _mainHLayout = new QHBoxLayout(this);
    _mainHLayout->addWidget(_backBut);
    _mainHLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(_mainHLayout);

    _player->moveToThread(&playerThread);
    connect(&playerThread, &QThread::finished, _player, &QObject::deleteLater);
    connect(this, &GameFragment::play, _player, &media::MediaPlayer::start);
    connect(_player, &media::MediaPlayer::finished, this, &GameFragment::onBack);
    playerThread.start();

    std::this_thread::sleep_for(std::chrono::seconds(4));
    emit play(QString(QString::fromStdString("udp://" + newIP + ":"+ std::to_string(workerPort))));

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
}

} // namespace fragment
