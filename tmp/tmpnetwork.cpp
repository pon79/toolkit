#include "tmpnetwork.h"

TmpNetwork::TmpNetwork(QObject *parent) : QObject(parent)
{

//    for( auto interface : QNetworkInterface::allInterfaces())
//        qDebug() << interface.name();

//    tmpNetworkConfiguration();


    QHostAddress address = QHostAddress();

    if( address.isNull() )
        qDebug() << "address.isNull";

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
