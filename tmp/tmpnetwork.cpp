#include "tmpnetwork.h"

TmpNetwork::TmpNetwork(QObject *parent) : QObject(parent)
{

    for( auto interface : QNetworkInterface::allInterfaces())
        qDebug() << interface.name();

}
