#include "startFragment.h"

#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

namespace fragment {

StartFragment::StartFragment()
    : _authBut(new QPushButton("Authorization"))
    , _regBut(new QPushButton("Registration"))
{
    _authBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");
    _regBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");

    QDir logofile;
    logofile.cd("project/lib/ui/media/");

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

    buttonsVL->addWidget(_regBut);
    buttonsVL->addWidget(_authBut);
    buttonsVL->setAlignment(Qt::AlignCenter);
    mainHL->setAlignment(Qt::AlignCenter);

    connect(_authBut, &QPushButton::clicked, this, &StartFragment::onAuth);
    connect(_regBut, &QPushButton::clicked, this, &StartFragment::onReg);
}

StartFragment::~StartFragment()
{
    delete _authBut;
    delete _regBut;
}

// slots
void StartFragment::onAuth()
{
    emit navigateTo(screens::ScreenNames::LOGIN);
}

void StartFragment::onReg()
{
    emit navigateTo(screens::ScreenNames::MAIN);
}

} // namespace fragment
