#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "navigator.h"
#include "screensFactory.h"

#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>

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

private slots:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void timerOutEvent();

private:
    Ui::MainWindow* _ui;
    QTimer* _timer;
    bool _butts[9];
    QStackedWidget* _container;
    ScreensFactory* _factory;
    Navigator* _nav;
};

#endif // MAINWINDOW_H
