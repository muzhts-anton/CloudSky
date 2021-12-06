#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "message_operations.h"
//#include "keyboard_mouse_message.pb.h"

#include <QDebug>
#include <QtGui>
#include <fstream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) //, _ui(new Ui::MainWindow)
    , _container(new QStackedWidget)
    , _factory(new ScreensFactory)
    , _nav(new Navigator(_container, _factory))
{
    //_ui->setupUi(this);
    _container->setStyleSheet("background-color: rgb(193,243,255);");
    this->setWindowTitle("CloudSky");
    this->setCentralWidget(_container);
}

MainWindow::~MainWindow()
{
    // delete _ui;
    delete _nav;
    delete _factory;
    delete _container;
}
