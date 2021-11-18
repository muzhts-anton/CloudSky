#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "navigator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    Navigator navigator;
};

#endif // MAINWINDOW_H
