#include "mainwindow.h"

#include <QtDebug>
#include <QUuid>

//#include "tmp/testjson.h"
#include "tmp/tmpxml.h"

#include "tmp/tmpnetwork.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

//    TestJSON testJSON;

    TmpXML tmpXML;

//    TmpNetwork tmpNetwork;

//    qDebug() << QUuid::createUuid().toString(QUuid::WithoutBraces);
}

MainWindow::~MainWindow()
{

}
