#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _container(new QStackedWidget)
    , _factory(new ScreensFactory)
    , _nav(new Navigator(_container, _factory))
{
    _container->setStyleSheet("background-color: rgb(193,243,255);");
    this->setWindowTitle("CloudSky");
    this->setCentralWidget(_container);
}

MainWindow::~MainWindow()
{
    delete _nav;
    delete _factory;
    delete _container;
}
