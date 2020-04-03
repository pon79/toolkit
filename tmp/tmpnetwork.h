#ifndef TMPNETWORK_H
#define TMPNETWORK_H

#include <QTimer>
#include <QObject>
#include <QDebug>

#include <QtNetwork>


class TmpNetwork : public QObject
{
    Q_OBJECT

//    QTimer timer;


    QNetworkAccessManager m_accessManager;
//    QNetworkConfigurationManager m_confManager;

    QNetworkReply *m_pReply = nullptr;

public:
    explicit TmpNetwork(QObject *parent = nullptr);

signals:

private:
    void tmpNetworkConfiguration();
    void tmpPostOnvifServer();

private slots:
//    void slotNetworkAccessibleChanged( QNetworkAccessManager::NetworkAccessibility accessible );
    void slotReadyRead();
    void slotError();
    void slotSslErrors();
};

#endif // TMPNETWORK_H
