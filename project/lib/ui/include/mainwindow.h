#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "navigator.h"
#include "screensFactory.h"

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    //Ui::MainWindow* _ui;
    QStackedWidget* _container;
    ScreensFactory* _factory;
    Navigator* _nav;
};

#endif // MAINWINDOW_H
