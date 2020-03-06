#include "udprequest.h"

UDPRequest::UDPRequest(QObject *parent) :
    QObject(parent)
  , m_udpSocket( new QUdpSocket(this) )
{

//    m_udpSocket.bind(QHostAddress::LocalHost, 7755);

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << "hello, world!";
//    out.device()->seek(qint64(0));
//    out << qint64(data.size() - sizeof(qint64));
    qDebug() << m_udpSocket->writeDatagram(data, QHostAddress::LocalHost, 7755);
}
