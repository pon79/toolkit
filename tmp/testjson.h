#ifndef TESTJSON_H
#define TESTJSON_H

#include <QObject>
#include <QtDebug>

#include <QJsonDocument>
#include <QJsonObject>



class TestJSON : public QObject
{
    Q_OBJECT
public:
    explicit TestJSON(QObject *parent = nullptr);

signals:

};

#endif // TESTJSON_H
