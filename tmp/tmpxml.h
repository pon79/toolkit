#ifndef TMPXML_H
#define TMPXML_H

#include <QObject>

#include <QtXml>
#include <QUuid>

class TmpXML : public QObject
{
    Q_OBJECT

    QDomDocument document;

public:
    explicit TmpXML(QObject *parent = nullptr);

signals:

};

#endif // TMPXML_H
