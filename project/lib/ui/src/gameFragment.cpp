#include "gameFragment.h"

#include <QHBoxLayout>

namespace fragment {

GameFragment::GameFragment()
    : _player(new MediaPlayer)
    , _backBut(new QPushButton("Go back\nStop testing"))
{
    _backBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");

    QHBoxLayout* mainHLayout = new QHBoxLayout(this);
    mainHLayout->addWidget(_backBut);
    mainHLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(mainHLayout);

    _player->moveToThread(&playerThread);
    connect(&playerThread, &QThread::finished, _player, &QObject::deleteLater);
    connect(this, &GameFragment::go, _player, &MediaPlayer::go);
    connect(_player, &MediaPlayer::finished, this, &GameFragment::onBack);
    playerThread.start();
    emit go();
    
    for (size_t i = 0; i < (size_t)GameFragment::Buttons::COUNT; ++i)
        _butts[i] = false;

    _timer = new QTimer(this);
    _timer->setInterval(1000.f / GameFragment::fps);
    _timer->start();

    connect(_backBut, &QPushButton::clicked, this, &GameFragment::onBack);
    connect(_timer, &QTimer::timeout, this, &GameFragment::timerOutEvent);
}

void GameFragment::timerOutEvent()
{
    /* TODO(Paul): place to merge */
    qDebug() << cursor().pos().x() << ":" << cursor().pos().y();
    qDebug() << _butts[0] << _butts[1];
}

void GameFragment::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "\n\nLOOOL\n\n";
    if (event->key() == Qt::Key_A)
        _butts[(size_t)Buttons::A] = true;

    if (event->key() == Qt::Key_W)
        _butts[(size_t)Buttons::W] = true;

    if (event->key() == Qt::Key_S)
        _butts[(size_t)Buttons::S] = true;

    if (event->key() == Qt::Key_D)
        _butts[(size_t)Buttons::D] = true;

    if (event->key() == Qt::Key_Space)
        _butts[(size_t)Buttons::SPACE] = true;

    if (event->key() == Qt::Key_Q)
        _butts[(size_t)Buttons::Q] = true;

    if (event->key() == Qt::Key_E)
        _butts[(size_t)Buttons::E] = true;

    if (event->key() == Qt::Key_F)
        _butts[(size_t)Buttons::F] = true;

    if (event->key() == Qt::Key_Escape)
        _butts[(size_t)Buttons::ESC] = true;
}

void GameFragment::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A)
        _butts[(size_t)Buttons::A] = false;

    if (event->key() == Qt::Key_W)
        _butts[(size_t)Buttons::W] = false;

    if (event->key() == Qt::Key_S)
        _butts[(size_t)Buttons::S] = false;

    if (event->key() == Qt::Key_D)
        _butts[(size_t)Buttons::D] = false;

    if (event->key() == Qt::Key_Space)
        _butts[(size_t)Buttons::SPACE] = false;

    if (event->key() == Qt::Key_Q)
        _butts[(size_t)Buttons::Q] = false;

    if (event->key() == Qt::Key_E)
        _butts[(size_t)Buttons::E] = false;

    if (event->key() == Qt::Key_F)
        _butts[(size_t)Buttons::F] = false;

    if (event->key() == Qt::Key_Escape)
        _butts[(size_t)Buttons::ESC] = false;
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
