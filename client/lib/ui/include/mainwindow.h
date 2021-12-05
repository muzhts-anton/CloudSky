#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerOutEvent();

private:
    Ui::MainWindow *_ui;
    TCPClient::TCPClientSocket TCPSocket;
    UDPClient::UDPClientSocket UDPSocket;
    QTimer *_timer;
    bool _butts[9];
};

#endif // MAINWINDOW_H
