
#include "onvif.h"


Onvif::Onvif()
{
}

// --- создание ответов на запросы ----- НАЧАЛО --------

QByteArray Onvif::getResponseFromFile( const QString fileName )
{
    QFile file("../integral/tcpserver/xmls/" + fileName + ".xml");

    if ( !file.open( QIODevice::ReadOnly ) )
    {
        qWarning() << "Failed to open file.";
        return "";
    }


    QTextStream textStream{ &file };


    // TO DO проверку правильности построения XML

    //    QXmlStreamReader xml{ textStream.readAll() };
    //    QString answer;
    //    while (!xml.atEnd()) {
    //        xml.readNext();
    //        answer = xml.readElementText();
    //        qDebug() << answer;
    //    }
    //    if (xml.hasError()) {
    //        qWarning() << "error";
    //    }


    auto response = textStream.readAll();

    file.close();

    qInfo() << "The response created";

    return response.toUtf8();
}

Onvif::CapabilityCategory Onvif::toCapabilityCategory( const QString category )
{
    if ( category == "All" )
        return CapabilityCategory::All;
    else if ( category == "Analytics" )
        return CapabilityCategory::Analytics;
    else if ( category == "Device" )
        return CapabilityCategory::Analytics;
    else if ( category == "Events" )
        return CapabilityCategory::Analytics;
    else if ( category == "Imaging" )
        return CapabilityCategory::Analytics;
    else if ( category == "Media" )
        return CapabilityCategory::Analytics;
    else if ( category == "PTZ" )
        return CapabilityCategory::Analytics;
    else if ( category == "PTZ" )
        return CapabilityCategory::Analytics;
    else {
        qWarning() << "unknown сategory: " << category;
        return CapabilityCategory::UnknownCategory;
    }
}

QByteArray Onvif::getCapabilitiesResponse( const CapabilityCategory category )
{
    // начинаем создавать XML
    auto root{ createRootDocument() };
    root.appendChild( createHeaderDocument() );
    auto body{ createBodyDocument() };
    root.appendChild( body );

    document.appendChild( root );

    QDomElement getCapabilitiesResponse { document.createElement("GetCapabilitiesResponse") };
    getCapabilitiesResponse.setAttribute("xmlns", "http://www.onvif.org/ver10/device/wsdl");
    body.appendChild( getCapabilitiesResponse );

    QDomElement capabilities{ document.createElement("tds:Capabilities") };
    getCapabilitiesResponse.appendChild( capabilities );

    switch ( category )
    {
        case CapabilityCategory::All :
            qInfo() << "Category - All";
            capabilities.appendChild( createDevice()  );
            capabilities.appendChild( createEvents()  );
            capabilities.appendChild( createImaging() );
            capabilities.appendChild( createMedia()   );
            capabilities.appendChild( createPTZ()     );
            break;
        case CapabilityCategory::Device :
            qInfo() << "Device";
            capabilities.appendChild( createDevice()  );
            break;
        case CapabilityCategory::Events :
            qInfo() << "Events";
            capabilities.appendChild( createEvents()  );
            break;
        case CapabilityCategory::Imaging :
            qInfo() << "Imaging";
            capabilities.appendChild( createImaging() );
            break;
        case CapabilityCategory::Media :
            qInfo() << "Media";
            capabilities.appendChild( createMedia()   );
            break;
        case CapabilityCategory::PTZ :
            qInfo() << "PTZ";
            capabilities.appendChild( createPTZ()     );
            break;
        case CapabilityCategory::UnknownCategory :
            qWarning() << "UnknownCategory";
            break;
        default:
            qWarning() << "default";
    }

    qInfo() << "The response created";

    return document.toByteArray();
}

QByteArray Onvif::getScopesResponse()
{
    // начинаем создавать XML
    auto root{ createRootDocument() };
    root.appendChild( createHeaderDocument() );
    auto body{ createBodyDocument() };
    root.appendChild( body );

    document.appendChild( root );

    QDomElement getScopesResponse { document.createElement("GetScopesResponse") };
    body.appendChild( getScopesResponse );

    QDomElement scopes1{ document.createElement("tds:Scopes") };
    scopes1.appendChild( createElement( prefix + "ScopeDef", "Fixed" ) );
    scopes1.appendChild( createElement( prefix + "ScopeItem", "onvif://www.onvif.org/Profile/Streaming" ) );
    getScopesResponse.appendChild( scopes1 );

    QDomElement scopes2{ document.createElement("tds:Scopes") };
    scopes2.appendChild( createElement( prefix + "ScopeDef", "Fixed" ) );
    scopes2.appendChild( createElement( prefix + "ScopeItem", "onvif://www.onvif.org/type/video_encoder" ) );
    getScopesResponse.appendChild( scopes2 );

    QDomElement scopes3{ document.createElement("tds:Scopes") };
    scopes3.appendChild( createElement( prefix + "ScopeDef", "Fixed" ) );
    scopes3.appendChild( createElement( prefix + "ScopeItem", "onvif://www.onvif.org/type/audio_encoder" ) );
    getScopesResponse.appendChild( scopes3 );

    QDomElement scopes4{ document.createElement("tds:Scopes") };
    scopes4.appendChild( createElement( prefix + "ScopeDef", "Configurable" ) );
    scopes4.appendChild( createElement( prefix + "ScopeItem", "onvif://www.onvif.org/location" ) );
    getScopesResponse.appendChild( scopes4 );

    qInfo() << "The response created";

    return document.toByteArray();
}

// --- создание ответов на запросы ----- КОНЕЦ --------


// --- создание элементов ----- НАЧАЛО --------

QDomElement Onvif::createElement(const QString name, const QString text)
{
    QDomElement element{ document.createElement( name ) };

    if ( !text.isEmpty() )
        element.appendChild(  document.createTextNode( text ));

    return element;
}

QDomElement Onvif::createRootDocument()
{
    QDomElement root = document.createElement("env:Envelope");
    root.setAttribute("xmlns:env", "http://www.w3.org/2003/05/soap-envelope");
    root.setAttribute("xmlns:a", "http://www.w3.org/2005/08/addressing");
    root.setAttribute("xmlns:s", "http://www.w3.org/2003/05/soap-envelope");

    return root;
}

QDomElement Onvif::createHeaderDocument()
{
    QDomElement header = document.createElement("env:Header");

    return header;
}

QDomElement Onvif::createBodyDocument()
{

    QDomElement body = document.createElement("env:Body");

    body.setAttribute("xmlns:tns1", "http://www.onvif.org/ver10/topics");
    body.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    body.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instances");

    body.setAttribute("xmlns:tds", "http://www.onvif.org/ver10/device/wsdl");
    body.setAttribute("xmlns:tt", "http://www.onvif.org/ver10/schema");

    return body;
}

QDomElement Onvif::createDevice()
{
    QDomElement device{ document.createElement( prefix + "Device" ) };
    device.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif/device_service" ) );
    device.appendChild( createNetwork()  );
    device.appendChild( createSystem()   );
    device.appendChild( createDeviceIO() );
    device.appendChild( createSecurity() );

    return device;
}

QDomElement Onvif::createEvents()
{
    QDomElement events{ document.createElement( prefix + "Events") };
    events.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif" ) );
    events.appendChild( createElement( prefix + "WSSubscriptionPolicySupport", "false" ) );
    events.appendChild( createElement( prefix + "WSPullPointSupport", "false" ) );
    events.appendChild( createElement( prefix + "WSPausableSubscriptionManagerInterfaceSupport", "false" ) );

    return events;
}

QDomElement Onvif::createImaging()
{
    QDomElement imaging{ document.createElement( prefix + "Imaging") };
    imaging.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif" ) );

    return imaging;
}

QDomElement Onvif::createMedia()
{
    QDomElement media{ document.createElement( prefix + "Media") };
    media.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif" ) );

    QDomElement streamingCapabilities{ document.createElement( prefix + "StreamingCapabilities") };
    streamingCapabilities.appendChild( createElement( prefix + "RTPMulticast", "false"  ) );
    streamingCapabilities.appendChild( createElement( prefix + "RTP_TCP",      "true"   ) );
    streamingCapabilities.appendChild( createElement( prefix + "RTP_RTSP_TCP", "true"   ) );
    media.appendChild( streamingCapabilities );

    QDomElement mediaExtension{ document.createElement( prefix + "Extension") };
    media.appendChild( mediaExtension );

    QDomElement profileCapabilities{ document.createElement( prefix + "ProfileCapabilities") };
    profileCapabilities.appendChild( createElement( prefix + "MaximumNumberOfProfiles", "11" ) );
    mediaExtension.appendChild( profileCapabilities );

    return media;
}

QDomElement Onvif::createPTZ()
{
    QDomElement PTZ{ document.createElement( prefix + "PTZ") };
    PTZ.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif" ) );

    return PTZ;
}

QDomElement Onvif::createExtension()
{
    QDomElement extension{ document.createElement( prefix + "Extension") };

    QDomElement deviceIO{ document.createElement( prefix + "DeviceIO") };
    deviceIO.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif" ) );
    deviceIO.appendChild( createElement( prefix + "VideoSources", "1" ) );
    deviceIO.appendChild( createElement( prefix + "VideoOutputs", "0" ) );
    deviceIO.appendChild( createElement( prefix + "AudioSources", "1" ) );
    deviceIO.appendChild( createElement( prefix + "AudioOutputs", "1" ) );
    deviceIO.appendChild( createElement( prefix + "RelayOutputs", "0" ) );
    extension.appendChild( deviceIO );

    QDomElement search{ document.createElement( prefix + "Search") };
    search.appendChild( createElement( prefix + "XAddr", xAddr + "/onvif" ) );
    search.appendChild( createElement( prefix + "MetadataSearch", "false" ) );
    extension.appendChild( search );

    QDomElement replay{ document.createElement( prefix + "Replay") };
    replay.appendChild( createElement( prefix + "XAddr",  xAddr + "/onvif" ) );
    extension.appendChild( replay );

    return extension;
}

QDomElement Onvif::createNetwork()
{
    QDomElement network{ document.createElement( prefix + "Network") };
    network.appendChild( createElement( prefix + "IPFilter", "false" ) );
    network.appendChild( createElement( prefix + "ZeroConfiguration", "false" ) );
    network.appendChild( createElement( prefix + "IPVersion6", "false" ) );
    network.appendChild( createElement( prefix + "DynDNS", "true" ) );

    QDomElement extension{ document.createElement( prefix + "Extension") };
    extension.appendChild( createElement( prefix + "Dot11Configuration", "false" ) );

    network.appendChild( extension );

    return network;
}

QDomElement Onvif::createSystem()
{
    QDomElement system{ document.createElement( prefix + "System" ) };
    system.appendChild( createElement( prefix + "DiscoveryResolve", "true" )  );
    system.appendChild( createElement( prefix + "DiscoveryBye", "true" )      );
    system.appendChild( createElement( prefix + "RemoteDiscovery", "false" )  );
    system.appendChild( createElement( prefix + "SystemBackup", "false" )     );
    system.appendChild( createElement( prefix + "SystemLogging", "false" )    );
    system.appendChild( createElement( prefix + "FirmwareUpgrade", "false" )  );

    QDomElement supportedVersion{ document.createElement( prefix + "SupportedVersion") };
    supportedVersion.appendChild( createElement( prefix + "Major", "16" ) );
    supportedVersion.appendChild( createElement( prefix + "Minor", "12" ) );
    system.appendChild( supportedVersion );

    QDomElement extension{ document.createElement( prefix + "Extension") };
    extension.appendChild( createElement( prefix + "HttpFirmwareUpgrade", "false" ) );
    extension.appendChild( createElement( prefix + "HttpSystemBackup", "false"    ) );
    system.appendChild( extension );

    return system;
}

QDomElement Onvif::createDeviceIO()
{
    QDomElement IO{ document.createElement( prefix + "IO") };
    IO.appendChild( createElement( prefix + "InputConnectors", "3" ) );
    IO.appendChild( createElement( prefix + "RelayOutputs", "1"    ) );

    QDomElement IOExtension{ document.createElement( prefix + "Extension" ) };
    IOExtension.appendChild( createElement( prefix + "Auxiliary", "false" ) );
    IOExtension.appendChild( createElement( prefix + "Extension"          ) );
    IO.appendChild( IOExtension );

    return IO;
}

QDomElement Onvif::createSecurity()
{
    QDomElement security{ document.createElement( prefix + "Security" ) };
    security.appendChild( createElement( prefix + "TLS1.1", "false" ) );
    security.appendChild( createElement( prefix + "TLS1.2", "false" ) );
    security.appendChild( createElement( prefix + "OnboardKeyGeneration", "false" ) );
    security.appendChild( createElement( prefix + "AccessPolicyConfig", "false" ) );
    security.appendChild( createElement( prefix + "X.509Token", "false" ) );
    security.appendChild( createElement( prefix + "SAMLToken", "false" ) );
    security.appendChild( createElement( prefix + "KerberosToken", "false" ) );
    security.appendChild( createElement( prefix + "RELToken", "false" ) );

    QDomElement securityExtension{ document.createElement( prefix + "Extension" ) };
    securityExtension.appendChild( createElement( prefix + "TLS1.0", "false" ) );
    security.appendChild( securityExtension );

    QDomElement securityExtensionExtension{ document.createElement( prefix + "Extension" ) };
    securityExtensionExtension.appendChild( createElement( prefix + "Dot1X", "false" ) );
    securityExtensionExtension.appendChild( createElement( prefix + "RemoteUserHandling", "false" ) );
    securityExtension.appendChild( securityExtensionExtension );

    return security;
}

// --- создание элементов ----- КОНЕЦ --------

