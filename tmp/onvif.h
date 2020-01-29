/*!
 * Ovnif
 *
 */


#ifndef ONVIF_H
#define ONVIF_H


#include <QtXml>

class Onvif
{

    QDomDocument document;

    const QString prefix{ "tt:" };

    const QString xAddr{ "http://192.168.7.2" };

    QDomElement createElement(const QString name, const QString text = "" );

    QDomElement createRootDocument();
    QDomElement createHeaderDocument();
    QDomElement createBodyDocument();

    QDomElement createAnalytics();
    QDomElement createDevice();
    QDomElement createEvents();
    QDomElement createImaging();
    QDomElement createMedia();
    QDomElement createPTZ();
    QDomElement createExtension();

    QDomElement createNetwork();
    QDomElement createSystem();
    QDomElement createDeviceIO();
    QDomElement createSecurity();

public:
    Onvif();

    /*! Creating a response to the request from file
     * \param file name
     * \return enum as per CapabilityCategory
     */
    QByteArray getResponseFromFile( const QString fileName  );

    /*! List of categories to retrieve capability information on
     *  List matches http://www.onvif.org/ver10/device/wsdl/GetCapabilities
     */
    enum struct CapabilityCategory{
        All,
        Analytics,
        Device,
        Events,
        Imaging,
        Media,
        PTZ,
        UnknownCategory
    };

    /*!  Сonverts a string to an enum
     * \param category from XML
     * \return enum as per CapabilityCategory
     */
    static CapabilityCategory toCapabilityCategory( const QString category);


    /*! Creating a response to the request getCapabilities
     * \param category from XML
     * \return response
     */
    QByteArray getCapabilitiesResponse( const CapabilityCategory category = CapabilityCategory::All );


    QByteArray getScopesResponse(); //! Creating a response to the request getScopes

};

#endif // ONVIF_H
