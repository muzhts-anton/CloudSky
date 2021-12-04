#include "startFragment.h"

#include <QDebug>
//#include <QVBoxLayout>
#include <QHBoxLayout>

namespace fragment {

StartFragment::StartFragment()
    : _gameBut(new QPushButton("Go to checking mouse n buttons"))
{
    //QVBoxLayout* mainVLayout = new QVBoxLayout;
    QHBoxLayout* mainHLayout = new QHBoxLayout;

    mainHLayout->addWidget(_gameBut);
    mainHLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(mainHLayout);

    connect(_gameBut, &QPushButton::clicked, this, &StartFragment::onGame);
}

void StartFragment::onGame()
{
    emit navigateTo(screens::ScreenNames::GAME);
}

} // namespace fragment
