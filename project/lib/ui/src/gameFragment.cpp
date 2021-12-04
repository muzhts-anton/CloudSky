#include "gameFragment.h"

#include <QHBoxLayout>

namespace fragment {

GameFragment::GameFragment() : _backBut(new QPushButton("Go back\nStop testing"))
{
    QHBoxLayout* mainHLayout = new QHBoxLayout;

    mainHLayout->addWidget(_backBut);
    mainHLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(mainHLayout);

    for (size_t i = 0; i < 9; ++i)
        _butts[i] = false;

    _timer = new QTimer();
    _timer->setInterval(1000 / 80.f);
    _timer->start();

    connect(_backBut, &QPushButton::clicked, this, &GameFragment::onBack);
    connect(_timer, &QTimer::timeout, this, &GameFragment::timerOutEvent);
}

void GameFragment::timerOutEvent()
{
    qDebug() << cursor().pos().x() << ":" << cursor().pos().y();
}

void GameFragment::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A)
        _butts[0] = true;

    if (event->key() == Qt::Key_W)
        _butts[1] = true;

    if (event->key() == Qt::Key_S)
        _butts[2] = true;

    if (event->key() == Qt::Key_D)
        _butts[3] = true;

    if (event->key() == Qt::Key_Space)
        _butts[4] = true;

    if (event->key() == Qt::Key_Q)
        _butts[5] = true;

    if (event->key() == Qt::Key_E)
        _butts[6] = true;

    if (event->key() == Qt::Key_F)
        _butts[7] = true;

    if (event->key() == Qt::Key_Escape)
        _butts[8] = true;
}

void GameFragment::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A)
        _butts[0] = false;

    if (event->key() == Qt::Key_W)
        _butts[1] = false;

    if (event->key() == Qt::Key_S)
        _butts[2] = false;

    if (event->key() == Qt::Key_D)
        _butts[3] = false;

    if (event->key() == Qt::Key_Space)
        _butts[4] = false;

    if (event->key() == Qt::Key_Q)
        _butts[5] = false;

    if (event->key() == Qt::Key_E)
        _butts[6] = false;

    if (event->key() == Qt::Key_F)
        _butts[7] = false;

    if (event->key() == Qt::Key_Escape)
        _butts[8] = false;
}

void GameFragment::onBack()
{
    emit back();
}

GameFragment::~GameFragment()
{
    delete _backBut;
    delete _timer;
}

} // namespace fragment
