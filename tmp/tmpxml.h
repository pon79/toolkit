#ifndef TMPXML_H
#define TMPXML_H

#include <QObject>

#include <QtXml>
#include <QUuid>
#include <QHostAddress>

class TmpXML : public QObject
{
    Q_OBJECT

    QDomDocument document;

public:
    explicit TmpXML(QObject *parent = nullptr);

signals:


private:
    void createGetCapabilitiesResponse();
    void createGetScopesResponse();
};

#endif // TMPXML_H
