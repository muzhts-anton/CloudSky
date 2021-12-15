#include "mainFragment.h"
#include "fragmentThemeStyle.h"

#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVBoxLayout>

namespace fragment {

MainFragment::MainFragment()
    : _pic(new QLabel(this))
    , _watcher(new secondfit::ButtonHoverWatcher(this))
    , _openGameBut(new QPushButton("Go to game screen"))
    , _settingsBut(new QPushButton("Settings [open soon]"))
//  , _addGameBut(new QPushButton("open soon"))
{ 
    _openGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::BUTTON));
    _settingsBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::BUTTON));
//  _addGameBut->setStyleSheet("background-color: grey; border: none; border-radius: 7px; padding: 10px; color: white;");

    _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("CloudSky.png")));
    _pic->setScaledContents(true);
    _pic->setFixedHeight(235);
    _pic->setFixedWidth(235);

    QHBoxLayout* mainHL = new QHBoxLayout(this);
    QVBoxLayout* buttonsVL = new QVBoxLayout;
    mainHL->addLayout(buttonsVL);
    mainHL->addWidget(_pic);

    buttonsVL->addWidget(_openGameBut);
    buttonsVL->addWidget(_settingsBut);
//  buttonsVL->addWidget(_addGameBut);

    buttonsVL->setAlignment(Qt::AlignCenter);
    mainHL->setAlignment(Qt::AlignCenter);

    _openGameBut->installEventFilter(_watcher);
//  _addGameBut->installEventFilter(watcher);
    _settingsBut->installEventFilter(_watcher);

    connect(_watcher, &secondfit::ButtonHoverWatcher::onButHovered, this, &MainFragment::onButHovered);
    connect(_openGameBut, &QPushButton::clicked, this, &MainFragment::onGame);
}

MainFragment::~MainFragment()
{
    delete _pic;
    delete _watcher;
    delete _openGameBut;
    delete _settingsBut;
//  delete _addGameBut;
}

// slots
void MainFragment::onGame()
{
    emit navigateTo(screens::ScreenNames::GAME);
}

void MainFragment::onButHovered(QPushButton* obj)
{
    if (obj == _settingsBut)
        _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("settings.png")));
    else if (obj == _openGameBut)
        _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("controller.png")));
}

} // namespace fragment
