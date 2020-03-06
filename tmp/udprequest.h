#ifndef UDPREQUEST_H
#define UDPREQUEST_H

#include <QObject>

#include <QUdpSocket>
#include <QDataStream>


class UDPRequest : public QObject
{
    Q_OBJECT

    QUdpSocket *m_udpSocket;


public:
    explicit UDPRequest(QObject *parent = nullptr);

signals:

};

#endif // UDPREQUEST_H
