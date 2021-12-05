#include "startFragment.h"

#include <QDebug>
#include <QHBoxLayout>

namespace fragment {

StartFragment::StartFragment()
    : _gameBut(new QPushButton("Go to checking mouse n buttons"))
{
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
