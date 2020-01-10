#include "testjson.h"

TestJSON::TestJSON(QObject *parent) : QObject(parent)
{


    QJsonObject mainObject
    {
        {"event", "bts:subscribe"},
        {"data", QJsonObject{ {"channel", "live_trades_btcusd"} }}
    };

    qInfo() << QJsonDocument{ mainObject }.toJson(QJsonDocument::Compact) ;

}
