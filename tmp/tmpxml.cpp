#include "tmpxml.h"


TmpXML::TmpXML(QObject *parent) : QObject(parent)
{
    QString s{"http://www.w3.org/2003/05/soap-envelope"};
    QString a{"http://www.w3.org/2005/08/addressing"};
    QString d{"http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01"};

    QFile file("/home/pon79/tmp/tmp.xml");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.writeNamespace(s, "s");

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement( s , "Envelope");

    xmlWriter.writeNamespace(a, "a");
    xmlWriter.writeNamespace(d, "d");

    xmlWriter.writeStartElement(s, "Header");
    xmlWriter.writeTextElement(a, "Action", "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Hello");
    xmlWriter.writeTextElement(a, "MessageID", "urn:uuid:" + QUuid::createUuid().toString(QUuid::WithoutBraces));
    xmlWriter.writeTextElement(a, "To", "urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01");
    xmlWriter.writeEndElement(); // close Header

    xmlWriter.writeStartElement(s, "Body");
    xmlWriter.writeStartElement(d, "Hello");
    xmlWriter.writeStartElement(a, "EndpointReference");
    xmlWriter.writeTextElement(a, "Address", "urn:uuid:" + QUuid::createUuid().toString(QUuid::WithoutBraces));
    xmlWriter.writeEndElement(); // close EndpointReference
    xmlWriter.writeTextElement(d, "MetadataVersion", "1");
    xmlWriter.writeEndElement(); // close Hello
    xmlWriter.writeEndElement(); // close Body

    xmlWriter.writeEndElement(); // close Envelope
    xmlWriter.writeEndDocument();

    file.close();   // Закрываем файл
}
