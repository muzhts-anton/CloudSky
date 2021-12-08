#include "startFragment.h"

#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

namespace fragment {

StartFragment::StartFragment()
    : _openGameBut(new QPushButton("Go to game screen"))
    , _settingsBut(new QPushButton("open soon"))
    , _addGameBut(new QPushButton("open soon"))
{
    _openGameBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");
    _addGameBut->setStyleSheet("background-color: grey; border: none; border-radius: 7px; padding: 10px; color: white;");
    _settingsBut->setStyleSheet("background-color: grey; border: none; border-radius: 7px; padding: 10px; color: white;");

    QDir logofile;
    logofile.cdUp();
    logofile.cd("lib/ui/media/");

    QLabel* logo = new QLabel(this);
    QPixmap piclogo(logofile.absoluteFilePath("CloudSky.png"));
    logo->setPixmap(piclogo);
    logo->setScaledContents(true);
    logo->setFixedHeight(235);
    logo->setFixedWidth(235);

    QHBoxLayout* mainHL = new QHBoxLayout(this);
    QVBoxLayout* buttonsVL = new QVBoxLayout;
    mainHL->addWidget(logo);
    mainHL->addLayout(buttonsVL);

    buttonsVL->addWidget(_openGameBut);
    buttonsVL->addWidget(_addGameBut);
    buttonsVL->addWidget(_settingsBut);
    buttonsVL->setAlignment(Qt::AlignCenter);
    mainHL->setAlignment(Qt::AlignCenter);
    // this->setLayout(buttonsVL);

    connect(_openGameBut, &QPushButton::clicked, this, &StartFragment::onGame);
}

StartFragment::~StartFragment()
{
    delete _openGameBut;
    delete _settingsBut;
    delete _addGameBut;
}

// slots
void StartFragment::onGame()
{
    emit navigateTo(screens::ScreenNames::GAME);
}

} // namespace fragment
