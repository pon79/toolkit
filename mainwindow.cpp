#include "mainwindow.h"

#include "QtDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    qInfo() << "create constructor MainWindow";

    qDebug() << "test";

}

MainWindow::~MainWindow()
{

}
