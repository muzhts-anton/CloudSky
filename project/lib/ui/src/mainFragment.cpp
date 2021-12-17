#include "mainFragment.h"
#include "fragmentThemeStyle.h"

#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVBoxLayout>

namespace fragment {

MainFragment::MainFragment()
    : _greetingLabel(new QLabel("Hi []! This is [] coins on your account."))
    , _pic(new QLabel(this))
    , _watcher(new secondfit::ButtonHoverWatcher(this))
    , _openGameBut(new QPushButton("Go to game screen"))
    , _settingsBut(new QPushButton("Settings [open soon]"))
    , _addGameBut(new QPushButton("Add Game"))
    , _logOutBut(new QPushButton("Log Out"))
{
    _greetingLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _openGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _settingsBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _addGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _logOutBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));

    _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("logout.png")));
    _pic->setScaledContents(true);
    _pic->setFixedHeight(235);
    _pic->setFixedWidth(235);

    QHBoxLayout* mainHL = new QHBoxLayout(this);
    QVBoxLayout* buttonsVL = new QVBoxLayout;

    buttonsVL->addWidget(_greetingLabel);
    buttonsVL->addWidget(_openGameBut);
    buttonsVL->addWidget(_settingsBut);
    buttonsVL->addWidget(_addGameBut);
    buttonsVL->addWidget(_logOutBut);

    mainHL->addLayout(buttonsVL);
    mainHL->addWidget(_pic);
    
    buttonsVL->setAlignment(Qt::AlignCenter);
    mainHL->setAlignment(Qt::AlignCenter);

    _openGameBut->installEventFilter(_watcher);
    _addGameBut->installEventFilter(_watcher);
    _settingsBut->installEventFilter(_watcher);
    _logOutBut->installEventFilter(_watcher);

    connect(_watcher, &secondfit::ButtonHoverWatcher::onButHovered, this, &MainFragment::onButHovered);
    connect(_openGameBut, &QPushButton::clicked, this, &MainFragment::onGame);
    connect(_addGameBut, &QPushButton::clicked, this, &MainFragment::onAddGame);
    connect(_logOutBut, &QPushButton::clicked, this, &MainFragment::onLogOut);
}

MainFragment::~MainFragment()
{
    delete _greetingLabel;
    delete _pic;
    delete _watcher;
    delete _openGameBut;
    delete _settingsBut;
    delete _addGameBut;
    delete _logOutBut;
}

// slots
void MainFragment::onGame()
{
    emit navigateTo(screens::ScreenNames::OPENGAME);
}

void MainFragment::onAddGame()
{
    emit navigateTo(screens::ScreenNames::ADDGAME);
}

void MainFragment::onButHovered(QPushButton* obj)
{
    if (obj == _settingsBut)
        _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("settings.png")));
    else if (obj == _openGameBut)
        _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("controller.png")));
    else if (obj == _logOutBut)
        _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("logout.png")));
    else if (obj == _addGameBut)
        _pic->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("sale.png")));

}

void MainFragment::onLogOut()
{
    emit back();
}

} // namespace fragment
