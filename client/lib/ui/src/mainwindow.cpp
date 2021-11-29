#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messageOperations.h"
#include "KeyboardMouseMessage.pb.h"
#include "TCPClientSocket.h"

#include <QtGui>
#include <iostream>
#include <fstream>
#include <QDebug>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow), socket(8050, "127.0.0.2")
{
    _ui->setupUi(this);

    for (size_t i = 0; i < 9; ++i)
        _butts[i] = false;
    
    _timer = new QTimer();
    _timer->setInterval(1000 / 80);
    _timer->start();
    socket.activateSocket();
    connect(_timer, &QTimer::timeout, this, &MainWindow::timerOutEvent);
}

void MainWindow::timerOutEvent()
{
    qDebug() << cursor().pos().x() << ":" << cursor().pos().y();
    std::string file_path = "buttonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;

    for (size_t i = 0; i < 9; ++i)
        (_butts[i]) ? message.add_buttonpressed(true) : message.add_buttonpressed(false);
 
    message.set_xcoord(cursor().pos().x());
    message.set_ycoord(cursor().pos().y());

    
    ViktorDev::SendInteraction SendM(file_path, message);
    //SendM.printMessage();

    std::ofstream out;
    if (SendM.sendIt())
        cout << "Error with sending";
    socket.transmit_file(file_path);

    KeyboardMouse::ButtonsCoords ReceiveMessage;
    ViktorDev::ReceiveInteraction ReceiveM(file_path, ReceiveMessage);
    ifstream inp;
    KeyboardMouse::ButtonsCoords parsed_buttons_coords;

    if (ReceiveM.receiveIt(file_path))
        cout << "Error wint receiving";
    ReceiveM.printMessage();
}

    // a w s d space q e f esc
    // 0 1 2 3 4     5 6 7 8
    // mouse.x mouse.y

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
        _butts[0] = true;
    
    if (event->key() == Qt::Key_W)
        _butts[1] = true;
    
    if (event->key() == Qt::Key_S)
        _butts[2] = true;
    
    if (event->key() == Qt::Key_D)
        _butts[3] = true;
    
    if (event->key() == Qt::Key_Space)
        _butts[4] = true;
    
    if (event->key() == Qt::Key_Q)
        _butts[5] = true;
    
    if (event->key() == Qt::Key_E)
        _butts[6] = true;
    
    if (event->key() == Qt::Key_F)
        _butts[7] = true;
    
    if (event->key() == Qt::Key_Escape)
        _butts[8] = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
        _butts[0] = false;
    
    if (event->key() == Qt::Key_W)
        _butts[1] = false;
    
    if (event->key() == Qt::Key_S)
        _butts[2] = false;
    
    if (event->key() == Qt::Key_D)
        _butts[3] = false;
    
    if (event->key() == Qt::Key_Space)
        _butts[4] = false;
    
    if (event->key() == Qt::Key_Q)
        _butts[5] = false;
    
    if (event->key() == Qt::Key_E)
        _butts[6] = false;
    
    if (event->key() == Qt::Key_F)
        _butts[7] = false;
    
    if (event->key() == Qt::Key_Escape)
        _butts[8] = false;
}

MainWindow::~MainWindow()
{
    delete _ui;
}
