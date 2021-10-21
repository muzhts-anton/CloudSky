#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtGui>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QFile filetmp("alajson.txt");
    filetmp.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&filetmp);

    if (event->key() == Qt::Key_A || event->key() == Qt::Key_W
        || event->key() == Qt::Key_S || event->key() == Qt::Key_D)
    {
        ui->label->setText(event->text());
        out << "\"Key\": \"" << event->text() << "\"\n";
    }
    else if (event->key() == Qt::Key_Space)
    {
        ui->label->setText("Jump");
        out << "\"Key\": \"" << "Jump" << "\"\n";
    }

    filetmp.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

