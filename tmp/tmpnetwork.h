#ifndef TMPNETWORK_H
#define TMPNETWORK_H

#include <QObject>
#include <QDebug>
#include <QNetworkInterface>


class TmpNetwork : public QObject
{
    Q_OBJECT
public:
    explicit TmpNetwork(QObject *parent = nullptr);

signals:

};

#endif // TMPNETWORK_H
