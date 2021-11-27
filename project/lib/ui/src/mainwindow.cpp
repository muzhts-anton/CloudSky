#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "message_operations.h"
//#include "keyboard_mouse_message.pb.h"

#include <QtGui>
#include <iostream>
#include <fstream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    for (size_t i = 0; i < 9; ++i)
        _butts[i] = false;
    
    _timer = new QTimer();
    _timer->setInterval(1000 / 80);
    _timer->start();

    connect(_timer, &QTimer::timeout, this, &MainWindow::timerOutEvent);
}

void MainWindow::timerOutEvent()
{
    qDebug() << cursor().pos().x() << ":" << cursor().pos().y();
    /*
    std::string file_path = "buttons_coords.bin";
    keyboard_mouse::buttons_coords message;

    for (size_t i = 0; i < 9; ++i)
        (_butts[i]) ? message.add_button_pressed(true) : message.add_button_pressed(false);
 
    message.set_x_coord(cursor().pos().x());
    message.set_y_coord(cursor().pos().y());

    SendInteraction SendM(file_path, message);
    SendM.PrintMessage();

    std::ofstream out;
    if (SendM.SendIt())
        cout << "Error with sending";

    keyboard_mouse::buttons_coords ReceiveMessage;
    ReceiveInteraction ReceiveM(file_path, ReceiveMessage);
    ifstream inp;
    keyboard_mouse::buttons_coords parsed_buttons_coords;

    if (ReceiveM.ReceiveIt())
        cout << "Error wint receiving";
    ReceiveM.PrintMessage();
    */
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
