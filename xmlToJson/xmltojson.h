#ifndef XMLTOJSON_H
#define XMLTOJSON_H

#include <QObject>

#include <QXmlStreamReader>
#include <QJsonValue>

class XmlToJson : public QObject
{
    Q_OBJECT

public:
    explicit XmlToJson(QObject *parent = nullptr);

    static QJsonObject toJson( QByteArray xmlByteArray );

signals:


private:
    static QJsonObject readNextStartElement( QXmlStreamReader &xml );
};

#endif // XMLTOJSON_H
