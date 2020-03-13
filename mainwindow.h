#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>

#include <QTimer>

#include <QUuid>

//#include "tmp/testjson.h"
#include "tmp/tmpxml.h"

#include "tmp/tmpnetwork.h"
#include <QTimer>


class MainWindow : public QMainWindow
{
    Q_OBJECT


    TmpNetwork tmpNetwork;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
