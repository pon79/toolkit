#ifndef TMPNETWORK_H
#define TMPNETWORK_H

#include <QTimer>
#include <QObject>
#include <QDebug>

#include <QtNetwork>
#include <QRegExp>

class TmpNetwork : public QObject
{
    Q_OBJECT

//    QTimer timer;


    QNetworkAccessManager m_accessManager;
//    QNetworkConfigurationManager m_confManager;

public:
    explicit TmpNetwork(QObject *parent = nullptr);

signals:

private:
    void tmpNetworkConfiguration();

private slots:
//    void slotNetworkAccessibleChanged( QNetworkAccessManager::NetworkAccessibility accessible );
};

#endif // TMPNETWORK_H
