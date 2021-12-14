#include "mainFragment.h"
#include "watcherHoverBut.h"

#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVBoxLayout>

namespace fragment {

MainFragment::MainFragment()
    : _pic(new QLabel(this))
    , _openGameBut(new QPushButton("Go to game screen"))
    , _settingsBut(new QPushButton("open soon"))
//, _addGameBut(new QPushButton("open soon"))
{
    _openGameBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");
    //_addGameBut->setStyleSheet("background-color: grey; border: none; border-radius: 7px; padding: 10px; color: white;");
    _settingsBut->setStyleSheet("background-color: grey; border: none; border-radius: 7px; padding: 10px; color: white;");

    QDir logofile;
    logofile.cd("project/lib/ui/media/");

    QPixmap piclogo(logofile.absoluteFilePath("CloudSky.png"));
    _pic->setPixmap(piclogo);
    _pic->setScaledContents(true);
    _pic->setFixedHeight(235);
    _pic->setFixedWidth(235);

    QHBoxLayout* mainHL = new QHBoxLayout(this);
    QVBoxLayout* buttonsVL = new QVBoxLayout;
    mainHL->addLayout(buttonsVL);
    mainHL->addWidget(_pic);

    buttonsVL->addWidget(_openGameBut);
    // buttonsVL->addWidget(_addGameBut);
    buttonsVL->addWidget(_settingsBut);
    buttonsVL->setAlignment(Qt::AlignCenter);
    mainHL->setAlignment(Qt::AlignCenter);

    ButtonHoverWatcher* watcher = new ButtonHoverWatcher(this);
    _openGameBut->installEventFilter(watcher);
    //_addGameBut->installEventFilter(watcher);
    _settingsBut->installEventFilter(watcher);

    connect(watcher, &ButtonHoverWatcher::onButHovered, this, &MainFragment::onButHovered);
    connect(_openGameBut, &QPushButton::clicked, this, &MainFragment::onGame);
}

MainFragment::~MainFragment()
{
    delete _pic;
    delete _openGameBut;
    delete _settingsBut;
    // delete _addGameBut;
}

// slots
void MainFragment::onGame()
{
    emit navigateTo(screens::ScreenNames::GAME);
}

void MainFragment::onButHovered(QPushButton* obj)
{
    if (obj == _settingsBut) {
        QDir picfile;
        picfile.cd("project/lib/ui/media/");

        QPixmap piclogo(picfile.absoluteFilePath("settings.png"));
        _pic->setPixmap(piclogo);
    } else if (obj == _openGameBut) {
        QDir picfile;
        picfile.cd("project/lib/ui/media/");

        QPixmap piclogo(picfile.absoluteFilePath("controller.png"));
        _pic->setPixmap(piclogo);
    }
}

} // namespace fragment
