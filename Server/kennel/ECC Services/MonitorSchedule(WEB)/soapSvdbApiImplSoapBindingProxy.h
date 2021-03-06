/* soapSvdbApiImplSoapBindingProxy.h
   Generated by gSOAP 2.7.12 from ecc.h
   Copyright(C) 2000-2008, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapSvdbApiImplSoapBindingProxy_H
#define soapSvdbApiImplSoapBindingProxy_H
#include "soapH.h"
class SvdbApiImplSoapBinding
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'SvdbApiImplSoapBinding' (change as needed)
	char strTemp[1024];
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	SvdbApiImplSoapBinding()
	{ soap = soap_new(); endpoint = "http://192.168.0.15:8080/SvdbCache/services/SvdbApiImpl"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://svdb.siteview.com", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };

	SvdbApiImplSoapBinding(const char * web_service_addr , int web_service_port)
	{ 
		soap = soap_new();
		sprintf(strTemp , "http://%s:%d/SvdbCache/services/SvdbApiImpl" , web_service_addr , web_service_port);
//		endpoint = "http://192.168.0.15:8080/SvdbCache/services/SvdbApiImpl"; 
		endpoint = strTemp;
		if (soap && !soap->namespaces) 
		{
			static const struct Namespace namespaces[] = 
			{
				{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
				{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
				{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
				{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
				{"ns1", "http://svdb.siteview.com", NULL, NULL},
				{NULL, NULL, NULL, NULL}
			};
			soap->namespaces = namespaces; 
		}
	};
	/// Destructor frees deserialized data and soap engine context
	virtual ~SvdbApiImplSoapBinding() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'appendRecord' of service 'SvdbApiImplSoapBinding' and return error code (or SOAP_OK)
	virtual int __ns1__appendRecord(_ns1__appendRecord *ns1__appendRecord, _ns1__appendRecordResponse *ns1__appendRecordResponse) { return soap ? soap_call___ns1__appendRecord(soap, endpoint, NULL, ns1__appendRecord, ns1__appendRecordResponse) : SOAP_EOM; };
};
#endif
