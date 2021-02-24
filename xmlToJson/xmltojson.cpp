
#include <QJsonObject>
#include <QJsonArray>

#include "xmltojson.h"

XmlToJson::XmlToJson(QObject *parent) : QObject(parent)
{

}

QJsonObject XmlToJson::toJson(QByteArray xmlByteArray )
{
    QXmlStreamReader xml{ xmlByteArray };

    xml.readNext();

    if( !xml.isStartDocument() )
    {
        qWarning() << "XML StartDocument FALSE";
        return QJsonObject();
    }

    xml.readNext();

    QJsonValue mainJson = readNextStartElement( xml );

     if (xml.hasError()) {
           qWarning() << "errorString: " << xml.errorString();
     }

     return mainJson.toObject();
}

QJsonObject XmlToJson::readNextStartElement(QXmlStreamReader &xml)
{
    QString tokenName = xml.name().split(':').last().toString();

    QJsonObject jsonObject;
    QString tokenText;

    QXmlStreamAttributes attributes;

    xml.readNext();

    //если XML битый, то синтаксический анализатор может не найти isEndElement
    // и мы окажемся в бесконечном цикле
    // будем считать инвалидные токены и если их значение превысит 5, то выйдем из цикла
    int countInvalidToken{0};

    while( !xml.isEndElement() && countInvalidToken < 5 )
    {
        if( xml.isStartElement() )
        {
            attributes = xml.attributes();

            // получаем значение каждого следующего токена рекурсивно
            QJsonObject newToken= readNextStartElement( xml );

            QString newTokenKey{ newToken.constBegin().key() };
            QJsonValue newTokenValue = newToken.value( newTokenKey );

            // если есть атрибуты, то запишем их в виде нового объекта
            if( !attributes.isEmpty() )
            {
                if( newTokenValue.isObject() )
                {
                    QJsonObject newTokenObject{ newTokenValue.toObject() };

                    for( auto it{ attributes.constBegin() }; it != attributes.constEnd(); it++ )
                    {
                        QString name = it->name().toString();
                        QString strValue = it->value().toString();


                        if( strValue == "true" )
                            newTokenObject.insert( "@" + name, true );
                        else if( strValue == "false" )
                            newTokenObject.insert( "@" + name, false );
                        else if ( name == "token" ) // встречается токен в виде числа, но это всё равно строка (GetVideoSourceModes)
                            newTokenObject.insert( "@" + name, strValue );
                        else
                        {
                            bool ok;
                            int number = strValue.toInt(&ok);

                            if( ok )
                                newTokenObject.insert( "@" + it->name().toString(), number );
                            else
                                newTokenObject.insert( "@" + it->name().toString(), strValue );
                        }
                    }

                    newTokenValue = QJsonValue{ newTokenObject };
                }
                else
                {
                    // TO DO
                    qWarning() << "newTokenValue not object";
                }
            }

            // если существующий объект содержит одноимённый ключ, то нужно использовать JsonArray
            if( jsonObject.keys().contains( newTokenKey ) /*&& ( newTokenValue.isObject() || newTokenValue.isArray() )*/ )
            {
                QJsonArray jsonArray;

                // если одноимённый элемент - JsonObject, то удалим этот JsonObject и создадим вместо него JsonArray
                if( jsonObject.value( newTokenKey ).isObject() )
                {
                    // получим значение существующего объекта, чтобы поместить его в JsonArray
                    QJsonValue previousValue = jsonObject.value( newTokenKey );

                    jsonArray.append( previousValue );
                }
                // если одноимённый элемент - JsonString, то добавим старое значение в новый массив
                else if( jsonObject.value( newTokenKey ).isString() )
                    jsonArray.append( jsonObject.value( newTokenKey ).toString() );
                // если одноимённый элемент - JsonArray, то вынем этот массив
                else if( jsonObject.value( newTokenKey ).isArray() )
                    jsonArray = jsonObject.value( newTokenKey ).toArray();

                jsonArray.append( newTokenValue ); // добавим в этот массив новый элемент
                jsonObject.remove(newTokenKey ); // удалим прошлый элемент
                jsonObject.insert( newTokenKey, jsonArray ); // вставим новый массив
            }
            else
                jsonObject.insert( newTokenKey, newTokenValue );

        }
        else if( xml.isCharacters() ) // если нам встретился текст
        {
            QString tmpText;
            tmpText.append( xml.text() );

            tmpText = tmpText.simplified();

            if( !tmpText.isEmpty() )
                tokenText.append( tmpText );
        }
        else
        {
            qInfo() << "token: " + xml.tokenString();
            countInvalidToken++;
        }

        xml.readNext();
    }

    // если встретился текст, то выявим его тип и запишем ключ:значение
    // где ключ - это имя элемента в котором текст
    // а значение - это сам текст или bool или число
    if( !tokenText.isEmpty() )
    {
        if( tokenText.toLower() == "true" )
            jsonObject.insert(tokenName, true);
        else if( tokenText.toLower() == "false" )
            jsonObject.insert(tokenName, false);
        else {

            bool ok{ false };

            auto number{ tokenText.toDouble(&ok) };

            if( ok )
                jsonObject.insert(tokenName, number);
            else
                jsonObject.insert(tokenName, tokenText);
        }

        return  jsonObject ;
    }
    else
    {
        QJsonObject returnObject{ {tokenName, jsonObject} };

        return returnObject;
    }
}
