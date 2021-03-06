#include "mainwindow.h"
#include "fragmentThemeStyle.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _container(new QStackedWidget)
    , _factory(new ScreensFactory)
    , _nav(new Navigator(_container, _factory))
{
    _container->setStyleSheet(themestyle::fixed.value(themestyle::Type::STACKEDWIDGET));
    this->setWindowTitle("CloudSky");
    this->setCentralWidget(_container);
}

MainWindow::~MainWindow()
{
    delete _nav;
    delete _factory;
    delete _container;
}
