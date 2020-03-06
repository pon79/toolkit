#include "tmpxml.h"


TmpXML::TmpXML(QObject *parent) : QObject(parent)
{
    createGetScopesResponse();
}

void TmpXML::createGetCapabilitiesResponse()
{
    QHostAddress m_hostAddress{"192.168.7.14"};

    // SOAP namespaces
    QString m_soapenv{"http://www.w3.org/2003/05/soap-envelope"};
    QString m_xsi{"http://www.w3.org/2001/XMLSchema-instance"};
    QString m_xs{"http://www.w3.org/2001/XMLSchema"};

    // ONFIV namespaces
    QString m_tds{"http://www.onvif.org/ver10/device/wsdl"};
    QString m_tt{"http://www.onvif.org/ver10/schema"};

    QFile file("/home/pon79/tmp/GetCapabilitiesResponse.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter m_xmlWriter(&file);

//    QByteArray array;
//    QXmlStreamWriter xmlWriter(&array);

    m_xmlWriter.setAutoFormatting(true);

    m_xmlWriter.writeNamespace(m_soapenv, "soapenv");
    m_xmlWriter.writeNamespace(m_xsi, "xsi");
    m_xmlWriter.writeNamespace(m_xs, "xs");
    m_xmlWriter.writeNamespace(m_tds, "tds");
    m_xmlWriter.writeNamespace(m_tt, "tt");

    m_xmlWriter.writeStartDocument();
    m_xmlWriter.writeStartElement( m_soapenv , "Envelope");
    m_xmlWriter.writeStartElement(m_soapenv, "Body");

    m_xmlWriter.writeStartElement( m_tds, "GetCapabilitiesResponse" );
    m_xmlWriter.writeStartElement( m_tds, "Capabilities" );

    m_xmlWriter.writeStartElement( m_tt, "Analytics" );
    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/analytics_service");
    m_xmlWriter.writeTextElement(m_tt, "RuleSupport", "True");
    m_xmlWriter.writeTextElement(m_tt, "AnalyticsModuleSupport", "True");
    m_xmlWriter.writeEndElement(); // close Analytics

    m_xmlWriter.writeStartElement( m_tt, "Device" );

    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/device_service");
    m_xmlWriter.writeStartElement( m_tt, "Network" );
    m_xmlWriter.writeTextElement(m_tt, "IPFilter", "false");
    m_xmlWriter.writeTextElement(m_tt, "ZeroConfiguration", "false");
    m_xmlWriter.writeTextElement(m_tt, "IPVersion6", "false");
    m_xmlWriter.writeTextElement(m_tt, "DynDNS", "false");
    m_xmlWriter.writeEndElement(); // close Network

    m_xmlWriter.writeStartElement( m_tt, "System" );
    m_xmlWriter.writeTextElement(m_tt, "DiscoveryResolve", "false");
    m_xmlWriter.writeTextElement(m_tt, "DiscoveryBye", "false");
    m_xmlWriter.writeTextElement(m_tt, "RemoteDiscovery", "false");
    m_xmlWriter.writeTextElement(m_tt, "SystemBackup", "false");
    m_xmlWriter.writeTextElement(m_tt, "SystemLogging", "false");
    m_xmlWriter.writeTextElement(m_tt, "FirmwareUpgrade", "false");
    m_xmlWriter.writeStartElement( m_tt, "SupportedVersions" );
    m_xmlWriter.writeTextElement(m_tt, "Major", "19");
    m_xmlWriter.writeTextElement(m_tt, "Minor", "12");
    m_xmlWriter.writeEndElement(); // close SupportedVersions
    m_xmlWriter.writeStartElement( m_tt, "SupportedVersions" );
    m_xmlWriter.writeTextElement(m_tt, "Major", "2");
    m_xmlWriter.writeTextElement(m_tt, "Minor", "40");
    m_xmlWriter.writeEndElement(); // close SupportedVersions
    m_xmlWriter.writeStartElement( m_tt, "SupportedVersions" );
    m_xmlWriter.writeTextElement(m_tt, "Major", "2");
    m_xmlWriter.writeTextElement(m_tt, "Minor", "20");
    m_xmlWriter.writeEndElement(); // close SupportedVersions
    m_xmlWriter.writeStartElement( m_tt, "SupportedVersions" );
    m_xmlWriter.writeTextElement(m_tt, "Major", "2");
    m_xmlWriter.writeTextElement(m_tt, "Minor", "10");
    m_xmlWriter.writeEndElement(); // close SupportedVersions
    m_xmlWriter.writeStartElement( m_tt, "SupportedVersions" );
    m_xmlWriter.writeTextElement(m_tt, "Major", "2");
    m_xmlWriter.writeTextElement(m_tt, "Minor", "0");
    m_xmlWriter.writeEndElement(); // close SupportedVersions
    m_xmlWriter.writeEndElement(); // close System

    m_xmlWriter.writeStartElement( m_tt, "IO" );
    m_xmlWriter.writeTextElement(m_tt, "InputConnectors", "1");
    m_xmlWriter.writeTextElement(m_tt, "RelayOutputs", "1");
    m_xmlWriter.writeEndElement(); // close IO

    m_xmlWriter.writeStartElement( m_tt, "Security" );
    m_xmlWriter.writeTextElement(m_tt, "TLS1.1", "false");
    m_xmlWriter.writeTextElement(m_tt, "TLS1.2", "false");
    m_xmlWriter.writeTextElement(m_tt, "OnboardKeyGeneration", "false");
    m_xmlWriter.writeTextElement(m_tt, "AccessPolicyConfig", "false");
    m_xmlWriter.writeTextElement(m_tt, "X.509Token", "false");
    m_xmlWriter.writeTextElement(m_tt, "SAMLToken", "false");
    m_xmlWriter.writeTextElement(m_tt, "KerberosToken", "false");
    m_xmlWriter.writeTextElement(m_tt, "RELToken", "false");
    m_xmlWriter.writeEndElement(); // close Security

    m_xmlWriter.writeEndElement(); // close Device

    m_xmlWriter.writeStartElement( m_tt, "Events" );
    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/event_service");
    m_xmlWriter.writeTextElement(m_tt, "WSSubscriptionPolicySupport", "false");
    m_xmlWriter.writeTextElement(m_tt, "WSPullPointSupport", "false");
    m_xmlWriter.writeTextElement(m_tt, "WSPausableSubscriptionManagerInterfaceSupport", "false");
    m_xmlWriter.writeEndElement(); // close Events

    m_xmlWriter.writeStartElement( m_tt, "Imaging" );
    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/image_service");
    m_xmlWriter.writeEndElement(); // close Imaging

    m_xmlWriter.writeStartElement( m_tt, "Media" );
    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/media_service");
    m_xmlWriter.writeStartElement( m_tt, "StreamingCapabilities" );
    m_xmlWriter.writeTextElement(m_tt, "RTPMulticast", "false");
    m_xmlWriter.writeTextElement(m_tt, "RTP_TCP", "false");
    m_xmlWriter.writeTextElement(m_tt, "RTP_RTSP_TCP", "false");
    m_xmlWriter.writeEndElement(); // close StreamingCapabilities
    m_xmlWriter.writeEndElement(); // close Media

    m_xmlWriter.writeStartElement( m_tt, "Media" );
    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/media_service");
    m_xmlWriter.writeStartElement( m_tt, "StreamingCapabilities" );
    m_xmlWriter.writeTextElement(m_tt, "RTPMulticast", "false");
    m_xmlWriter.writeTextElement(m_tt, "RTP_TCP", "false");
    m_xmlWriter.writeTextElement(m_tt, "RTP_RTSP_TCP", "false");
    m_xmlWriter.writeEndElement(); // close StreamingCapabilities
    m_xmlWriter.writeEndElement(); // close Media

    m_xmlWriter.writeStartElement( m_tt, "PTZ" );
    m_xmlWriter.writeTextElement(m_tt, "XAddr", "http://" + m_hostAddress.toString() + "/onvif/ptz_service");
    m_xmlWriter.writeEndElement(); // close PTZ

    m_xmlWriter.writeEndElement(); // close Capabilities
    m_xmlWriter.writeEndElement(); // close GetCapabilitiesResponse

    m_xmlWriter.writeEndElement();  // close Body
    m_xmlWriter.writeEndElement(); // close Envelope
    m_xmlWriter.writeEndDocument();

    file.close();   // Закрываем файл
}

void TmpXML::createGetScopesResponse()
{
    // SOAP namespaces
    QString m_soapenv{"http://www.w3.org/2003/05/soap-envelope"};
    QString m_xsi{"http://www.w3.org/2001/XMLSchema-instance"};
    QString m_xs{"http://www.w3.org/2001/XMLSchema"};

    // ONFIV namespaces
    QString m_tds{"http://www.onvif.org/ver10/device/wsdl"};
    QString m_tt{"http://www.onvif.org/ver10/schema"};

    QFile file("/home/pon79/tmp/GetScopesResponse.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter m_xmlWriter(&file);

    m_xmlWriter.setAutoFormatting(true);

    m_xmlWriter.writeNamespace(m_soapenv, "soapenv");
    m_xmlWriter.writeNamespace(m_xsi, "xsi");
    m_xmlWriter.writeNamespace(m_xs, "xs");
    m_xmlWriter.writeNamespace(m_tds, "tds");
    m_xmlWriter.writeNamespace(m_tt, "tt");

    m_xmlWriter.writeStartDocument();
    m_xmlWriter.writeStartElement( m_soapenv , "Envelope");
    m_xmlWriter.writeStartElement(m_soapenv, "Body");

    m_xmlWriter.writeStartElement( m_tds, "GetScopesResponse" );

    QStringList scopeItems;
    scopeItems << "onvif://www.onvif.org/type/Network_Video_Transmitter"
               << "onvif://www.onvif.org/Profile/Streaming"
               << "onvif://www.onvif.org/type/video_analytics"
               << "onvif://www.onvif.org/type/ptz"
               << "onvif://www.onvif.org/location/country/russia"
               << "onvif://www.onvif.org/hardware/IPcamera";

    for( auto scopeItem : scopeItems)
    {
        m_xmlWriter.writeStartElement( m_tds, "Scopes" );
        m_xmlWriter.writeTextElement(m_tt, "ScopeDef", "Fixed");
        m_xmlWriter.writeTextElement(m_tt, "ScopeItem", scopeItem);
        m_xmlWriter.writeEndElement(); // close Scopes
    }

    m_xmlWriter.writeEndElement(); // close GetScopesResponse

    m_xmlWriter.writeEndElement();  // close Body
    m_xmlWriter.writeEndElement(); // close Envelope
    m_xmlWriter.writeEndDocument();

    file.close();   // Закрываем файл
}
