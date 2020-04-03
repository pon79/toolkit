#include "tmpnetwork.h"

TmpNetwork::TmpNetwork(QObject *parent) : QObject(parent)
{

//    for( auto interface : QNetworkInterface::allInterfaces())
//        qDebug() << interface.name();

//    tmpNetworkConfiguration();

    connect(m_pReply, &QIODevice::readyRead, this, &TmpNetwork::slotReadyRead);
    connect(m_pReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &TmpNetwork::slotError);
    connect(m_pReply, &QNetworkReply::sslErrors,
            this, &TmpNetwork::slotSslErrors);

    tmpPostOnvifServer();

}

void TmpNetwork::tmpNetworkConfiguration()
{
    QNetworkAccessManager accessManager;
    QNetworkConfiguration configuration;
    QNetworkConfigurationManager confManager;

    for( auto conf : confManager.allConfigurations( QNetworkConfiguration::Active ))
    {
        qDebug() << conf.name();
        if( conf.name() == "enp4s0" )
            configuration = conf;
    }

    connect(&m_accessManager, &QNetworkAccessManager::networkAccessibleChanged, [](QNetworkAccessManager::NetworkAccessibility accessible){
       qDebug() << "accessible: " << accessible;
    });


//    qDebug() << "configuration.connectTimeout() " << configuration.connectTimeout();
//    configuration.setConnectTimeout( 3000 );

    accessManager.setConfiguration( confManager.defaultConfiguration() );

    if( m_accessManager.networkAccessible() == QNetworkAccessManager::NetworkAccessibility::Accessible )
        qDebug() << "networkAccessible" << m_accessManager.networkAccessible();

}

void TmpNetwork::tmpPostOnvifServer()
{
//    QNetworkRequest request;

    QNetworkRequest request;
    request.setUrl(QUrl("http://192.168.7.14:5577"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"text/plain");

//    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    m_pReply = m_accessManager.post( request, " onvif.org/ver10/device/wsdl GetScopes" );

//    m_pReply = m_accessManager.get( request );



}

void TmpNetwork::slotReadyRead()
{
    qDebug() << "ReadyRead: " << m_pReply->readAll();
}

void TmpNetwork::slotError()
{
    qDebug() << "error: " << m_pReply->errorString();
}

void TmpNetwork::slotSslErrors()
{
    qDebug() << "SSL error: " << m_pReply->errorString();
}
