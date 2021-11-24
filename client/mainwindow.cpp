#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QFile>
#include <QTextStream>

#include <QtMultimedia/QMediaPlayer>

#include <iostream>
#include <fstream>
#include "include/KeyboardMouseMessage.pb.h"
#include "include/MessageOperations.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    for (size_t i = 0; i < 9; ++i)
        _butts[i] = false;
    
    _timer = new QTimer();
    _timer->setInterval(1000 / 40);
    _timer->start();

    connect(_timer, &QTimer::timeout, this, &MainWindow::timerOutEvent);
}

void MainWindow::timerOutEvent()
{
    std::string file_path = "../data/buttons_coords.bin";
    KeyboardMouse::ButtonsCoords message;

    for (size_t i = 0; i < 9; ++i)
        (_butts[i]) ? message.add_buttonpressed(true) : message.add_buttonpressed(false);
 
    message.set_xcoord(cursor().pos().x());
    message.set_ycoord(cursor().pos().y());

    ViktorDev::SendInteraction SendM(file_path, message);
    //SendM.printMessage();
    if (SendM.sendIt())
        cout << "Error with sending";

    KeyboardMouse::ButtonsCoords ReceiveMessage;
    ViktorDev::ReceiveInteraction ReceiveM("../../server/data/received.bin", ReceiveMessage);
    ifstream inp;
    // keyboard_mouse::buttonsCoords parsed_buttons_coords;

    if (ReceiveM.receiveIt())
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
