# xmlToJson Qt


XML to JSON converter using QxmlStreamReader and JSON classes (QJsonDocument, QJsonArray, QJsonObject, QJsonParseError).

The converter is implemented using recursion.


Example:
```xml
<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://www.w3.org/2003/05/soap-envelope" xmlns:SOAP-ENC="http://www.w3.org/2003/05/soap-encoding"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xop="http://www.w3.org/2004/08/xop/include"
xmlns:xmime4="http://www.w3.org/2004/11/xmlmime" xmlns:wsa5="http://www.w3.org/2005/08/addressing" xmlns:wsrf-bf="http://docs.oasis-open.org/wsrf/bf-2"
xmlns:wstop="http://docs.oasis-open.org/wsn/t-1" xmlns:wsrf-r="http://docs.oasis-open.org/wsrf/r-2" xmlns:tes-e="http://www.onvif.org/ver10/events/wsdl/EventBinding"
xmlns:tev="http://www.onvif.org/ver10/events/wsdl" xmlns:tes-nc="http://www.onvif.org/ver10/events/wsdl/NotificationConsumerBinding"
xmlns:tes-np="http://www.onvif.org/ver10/events/wsdl/NotificationProducerBinding" xmlns:tes-sm="http://www.onvif.org/ver10/events/wsdl/SubscriptionManagerBinding"
xmlns:tns1="http://www.onvif.org/ver10/topics" xmlns:xmime="http://www.w3.org/2004/06/xmlmime" xmlns:tt="http://www.onvif.org/ver10/schema"
xmlns:wsnt="http://docs.oasis-open.org/wsn/b-2" xmlns:tds="http://www.onvif.org/ver10/device/wsdl" xmlns:timg="http://www.onvif.org/ver20/imaging/wsdl"
xmlns:tmd="http://www.onvif.org/ver10/deviceIO/wsdl" xmlns:tptz="http://www.onvif.org/ver20/ptz/wsdl" xmlns:trt="http://www.onvif.org/ver10/media/wsdl"
xmlns:tr2="http://www.onvif.org/ver20/media/wsdl" xmlns:wsse="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd"
xmlns:wsu="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd" xmlns:ter="http://www.onvif.org/ver10/error"
xmlns:tan="http://www.onvif.org/ver20/analytics/wsdl" xmlns:tan-ae="http://www.onvif.org/ver20/analytics/wsdl/AnalyticsEngineBinding"
xmlns:tan-re="http://www.onvif.org/ver20/analytics/wsdl/RuleEngineBinding" xmlns:trc="http://www.onvif.org/ver10/recording/wsdl"
xmlns:trp="http://www.onvif.org/ver10/replay/wsdl" xmlns:tse="http://www.onvif.org/ver10/search/wsdl" xmlns:tpl="http://www.onvif.org/ver10/plus/wsdl"
xmlns:tplt="http://www.onvif.org/ver10/plus/schema">
	<SOAP-ENV:Body>
		<tds:GetNetworkInterfacesResponse>
			<tds:NetworkInterfaces token="eth0">
				<tt:Enabled>true</tt:Enabled>
				<tt:Info>
					<tt:Name>eth0</tt:Name>
					<tt:HwAddress>48ea63906cdb</tt:HwAddress>
					<tt:MTU>1500</tt:MTU>
				</tt:Info>
				<tt:Link>
					<tt:AdminSettings>
						<tt:AutoNegotiation>true</tt:AutoNegotiation>
						<tt:Speed>100</tt:Speed>
						<tt:Duplex>Full</tt:Duplex>
					</tt:AdminSettings>
					<tt:OperSettings>
						<tt:AutoNegotiation>true</tt:AutoNegotiation>
						<tt:Speed>100</tt:Speed>
						<tt:Duplex>Full</tt:Duplex>
					</tt:OperSettings>
					<tt:InterfaceType>6</tt:InterfaceType>
				</tt:Link>
				<tt:IPv4>
					<tt:Enabled>true</tt:Enabled>
					<tt:Config>
						<tt:Manual>
							<tt:Address>192.168.7.245</tt:Address>
							<tt:PrefixLength>24</tt:PrefixLength>
						</tt:Manual>
						<tt:DHCP>false</tt:DHCP>
					</tt:Config>
				</tt:IPv4>
				<tt:IPv6>
					<tt:Enabled>false</tt:Enabled>
				</tt:IPv6>
			</tds:NetworkInterfaces>
		</tds:GetNetworkInterfacesResponse>
	</SOAP-ENV:Body>
</SOAP-ENV:Envelope> 

```



```json
{
    "Envelope": {
        "Body": {
            "GetNetworkInterfacesResponse": {
                "NetworkInterfaces": {
                    "@token": "eth0",
                    "Enabled": true,
                    "IPv4": {
                        "Config": {
                            "DHCP": false,
                            "Manual": {
                                "Address": "192.168.7.245",
                                "PrefixLength": 24
                            }
                        },
                        "Enabled": true
                    },
                    "IPv6": {
                        "Enabled": false
                    },
                    "Info": {
                        "HwAddress": "48ea63906cdb",
                        "MTU": 1500,
                        "Name": "eth0"
                    },
                    "Link": {
                        "AdminSettings": {
                            "AutoNegotiation": true,
                            "Duplex": "Full",
                            "Speed": 100
                        },
                        "InterfaceType": 6,
                        "OperSettings": {
                            "AutoNegotiation": true,
                            "Duplex": "Full",
                            "Speed": 100
                        }
                    }
                }
            }
        }
    }
}
```


С учётом следующих особенностей:
- если в атрибутах элемента XML встречается число, то сохраняем его как строку (нужно для большинства запросов ONVIF);
- если предполагаемое число не конвертируется в double, то сохраняем его как строку (скорее всего это серийный номер устройства);
- пространства имён в атрибутах Envelope (например, xmlns:xsd="http://www.w3.org/2001/XMLSchema") не конвертируются;
- атрибуты XML в JSON имеют префикс @;
