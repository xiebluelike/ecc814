/* soapStub.h
   Generated by gSOAP 2.7.12 from D:\program\huaWei\soap\soap\huaWei.h
   Copyright(C) 2000-2008, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapStub_H
#define soapStub_H
#include <vector>
#include "stdsoap2.h"

/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


#ifndef SOAP_TYPE__ns1__SetParameterAttributesStruct_Notification
#define SOAP_TYPE__ns1__SetParameterAttributesStruct_Notification (36)
/* ns1:SetParameterAttributesStruct-Notification */
enum _ns1__SetParameterAttributesStruct_Notification {_ns1__SetParameterAttributesStruct_Notification__0 = 0, _ns1__SetParameterAttributesStruct_Notification__1 = 1, _ns1__SetParameterAttributesStruct_Notification__2 = 2};
#endif

#ifndef SOAP_TYPE__ns1__ParameterAttributeStruct_Notification
#define SOAP_TYPE__ns1__ParameterAttributeStruct_Notification (38)
/* ns1:ParameterAttributeStruct-Notification */
enum _ns1__ParameterAttributeStruct_Notification {_ns1__ParameterAttributeStruct_Notification__0 = 0, _ns1__ParameterAttributeStruct_Notification__1 = 1, _ns1__ParameterAttributeStruct_Notification__2 = 2};
#endif

#ifndef SOAP_TYPE__ns1__SetParameterValuesResponse_Status
#define SOAP_TYPE__ns1__SetParameterValuesResponse_Status (41)
/* ns1:SetParameterValuesResponse-Status */
enum _ns1__SetParameterValuesResponse_Status {_ns1__SetParameterValuesResponse_Status__0 = 0, _ns1__SetParameterValuesResponse_Status__1 = 1};
#endif

/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not redeclare here */

#endif

#if 0 /* volatile type: do not redeclare here */

#endif

#ifndef SOAP_TYPE_ns1__DeviceIdStruct
#define SOAP_TYPE_ns1__DeviceIdStruct (10)
/* ns1:DeviceIdStruct */
class SOAP_CMAC ns1__DeviceIdStruct
{
public:
	std::string Manufacturer;	/* required element of type xsd:string */
	std::string OUI;	/* required element of type xsd:string */
	std::string ProductClass;	/* required element of type xsd:string */
	std::string SerialNumber;	/* required element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 10; } /* = unique id SOAP_TYPE_ns1__DeviceIdStruct */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__DeviceIdStruct() : soap(NULL) { }
	virtual ~ns1__DeviceIdStruct() { }
};
#endif

#ifndef SOAP_TYPE_ns1__EventStruct
#define SOAP_TYPE_ns1__EventStruct (11)
/* ns1:EventStruct */
class SOAP_CMAC ns1__EventStruct
{
public:
	std::string EventCode;	/* required element of type xsd:string */
	std::string CommandKey;	/* required element of type ns1:CommandKeyType */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 11; } /* = unique id SOAP_TYPE_ns1__EventStruct */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__EventStruct() : soap(NULL) { }
	virtual ~ns1__EventStruct() { }
};
#endif

#ifndef SOAP_TYPE_ns1__ParameterValueStruct
#define SOAP_TYPE_ns1__ParameterValueStruct (13)
/* ns1:ParameterValueStruct */
class SOAP_CMAC ns1__ParameterValueStruct
{
public:
	std::string Name;	/* required element of type xsd:string */
	std::string Value;	/* required element of type xsd:anySimpleType */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 13; } /* = unique id SOAP_TYPE_ns1__ParameterValueStruct */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__ParameterValueStruct() : soap(NULL) { }
	virtual ~ns1__ParameterValueStruct() { }
};
#endif

#ifndef SOAP_TYPE_ns1__ParameterInfoStruct
#define SOAP_TYPE_ns1__ParameterInfoStruct (15)
/* ns1:ParameterInfoStruct */
class SOAP_CMAC ns1__ParameterInfoStruct
{
public:
	std::string Name;	/* required element of type xsd:string */
	bool Writable;	/* required element of type xsd:boolean */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 15; } /* = unique id SOAP_TYPE_ns1__ParameterInfoStruct */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__ParameterInfoStruct() : Writable((bool)0), soap(NULL) { }
	virtual ~ns1__ParameterInfoStruct() { }
};
#endif

#ifndef SOAP_TYPE_ns1__SetParameterAttributesStruct
#define SOAP_TYPE_ns1__SetParameterAttributesStruct (19)
/* ns1:SetParameterAttributesStruct */
class SOAP_CMAC ns1__SetParameterAttributesStruct
{
public:
	std::string *Name;	/* optional element of type xsd:string */
	bool NotificationChange;	/* required element of type xsd:boolean */
	enum _ns1__SetParameterAttributesStruct_Notification Notification;	/* required element of type ns1:SetParameterAttributesStruct-Notification */
	bool AccessListChange;	/* required element of type xsd:boolean */
	class AccessList *AccessList_;	/* required element of type ArrayOfstring */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 19; } /* = unique id SOAP_TYPE_ns1__SetParameterAttributesStruct */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__SetParameterAttributesStruct() : Name(NULL), NotificationChange((bool)0), Notification((enum _ns1__SetParameterAttributesStruct_Notification)0), AccessListChange((bool)0), AccessList_(NULL), soap(NULL) { }
	virtual ~ns1__SetParameterAttributesStruct() { }
};
#endif

#ifndef SOAP_TYPE_ns1__ParameterAttributeStruct
#define SOAP_TYPE_ns1__ParameterAttributeStruct (21)
/* ns1:ParameterAttributeStruct */
class SOAP_CMAC ns1__ParameterAttributeStruct
{
public:
	std::string Name;	/* required element of type xsd:string */
	enum _ns1__ParameterAttributeStruct_Notification Notification;	/* required element of type ns1:ParameterAttributeStruct-Notification */
	AccessList *AccessList_;	/* required element of type ArrayOfstring */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 21; } /* = unique id SOAP_TYPE_ns1__ParameterAttributeStruct */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__ParameterAttributeStruct() : Notification((enum _ns1__ParameterAttributeStruct_Notification)0), AccessList_(NULL), soap(NULL) { }
	virtual ~ns1__ParameterAttributeStruct() { }
};
#endif

#ifndef SOAP_TYPE__ns1__SetParameterValues
#define SOAP_TYPE__ns1__SetParameterValues (23)
/* ns1:SetParameterValues */
class SOAP_CMAC _ns1__SetParameterValues
{
public:
	ns1__DeviceIdStruct *DeviceId;	/* required element of type ns1:DeviceIdStruct */
	std::string Ip;	/* required element of type xsd:string */
	class ParameterValueList *ParameterList;	/* required element of type ArrayOfParameterValueStruct */
	std::string ParameterKey;	/* required element of type ns1:ParameterKeyType */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 23; } /* = unique id SOAP_TYPE__ns1__SetParameterValues */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__SetParameterValues() : DeviceId(NULL), ParameterList(NULL), soap(NULL) { }
	virtual ~_ns1__SetParameterValues() { }
};
#endif

#ifndef SOAP_TYPE__ns1__SetParameterValuesResponse
#define SOAP_TYPE__ns1__SetParameterValuesResponse (24)
/* ns1:SetParameterValuesResponse */
class SOAP_CMAC _ns1__SetParameterValuesResponse
{
public:
	enum _ns1__SetParameterValuesResponse_Status Status;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type ns1:SetParameterValuesResponse-Status */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 24; } /* = unique id SOAP_TYPE__ns1__SetParameterValuesResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__SetParameterValuesResponse() : Status((enum _ns1__SetParameterValuesResponse_Status)0), soap(NULL) { }
	virtual ~_ns1__SetParameterValuesResponse() { }
};
#endif

#ifndef SOAP_TYPE__ns1__GetParameterValues
#define SOAP_TYPE__ns1__GetParameterValues (25)
/* ns1:GetParameterValues */
class SOAP_CMAC _ns1__GetParameterValues
{
public:
	ns1__DeviceIdStruct *DeviceId;	/* required element of type ns1:DeviceIdStruct */
	std::string Ip;	/* required element of type xsd:string */
	class ParameterNames *ParameterNames_;	/* required element of type ArrayOfstring */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 25; } /* = unique id SOAP_TYPE__ns1__GetParameterValues */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__GetParameterValues() : DeviceId(NULL), ParameterNames_(NULL), soap(NULL) { }
	virtual ~_ns1__GetParameterValues() { }
};
#endif

#ifndef SOAP_TYPE__ns1__GetParameterValuesResponse
#define SOAP_TYPE__ns1__GetParameterValuesResponse (26)
/* ns1:GetParameterValuesResponse */
class SOAP_CMAC _ns1__GetParameterValuesResponse
{
public:
	ParameterValueList *ParameterList;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type ArrayOfParameterValueStruct */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 26; } /* = unique id SOAP_TYPE__ns1__GetParameterValuesResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__GetParameterValuesResponse() : ParameterList(NULL), soap(NULL) { }
	virtual ~_ns1__GetParameterValuesResponse() { }
};
#endif

#ifndef SOAP_TYPE__ns1__SetParameterAttributes
#define SOAP_TYPE__ns1__SetParameterAttributes (27)
/* ns1:SetParameterAttributes */
class SOAP_CMAC _ns1__SetParameterAttributes
{
public:
	ns1__DeviceIdStruct *DeviceId;	/* required element of type ns1:DeviceIdStruct */
	std::string Ip;	/* required element of type xsd:string */
	class SetParameterAttributesList *ParameterList;	/* required element of type ArrayOfSetParameterAttributesStruct */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 27; } /* = unique id SOAP_TYPE__ns1__SetParameterAttributes */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__SetParameterAttributes() : DeviceId(NULL), ParameterList(NULL), soap(NULL) { }
	virtual ~_ns1__SetParameterAttributes() { }
};
#endif

#ifndef SOAP_TYPE__ns1__SetParameterAttributesResponse
#define SOAP_TYPE__ns1__SetParameterAttributesResponse (28)
/* ns1:SetParameterAttributesResponse */
class SOAP_CMAC _ns1__SetParameterAttributesResponse
{
public:
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 28; } /* = unique id SOAP_TYPE__ns1__SetParameterAttributesResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__SetParameterAttributesResponse() : soap(NULL) { }
	virtual ~_ns1__SetParameterAttributesResponse() { }
};
#endif

#ifndef SOAP_TYPE__ns1__GetParameterAttributes
#define SOAP_TYPE__ns1__GetParameterAttributes (29)
/* ns1:GetParameterAttributes */
class SOAP_CMAC _ns1__GetParameterAttributes
{
public:
	ns1__DeviceIdStruct *DeviceId;	/* required element of type ns1:DeviceIdStruct */
	std::string Ip;	/* required element of type xsd:string */
	ParameterNames *ParameterNames_;	/* required element of type ArrayOfstring */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 29; } /* = unique id SOAP_TYPE__ns1__GetParameterAttributes */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__GetParameterAttributes() : DeviceId(NULL), ParameterNames_(NULL), soap(NULL) { }
	virtual ~_ns1__GetParameterAttributes() { }
};
#endif

#ifndef SOAP_TYPE__ns1__GetParameterAttributesResponse
#define SOAP_TYPE__ns1__GetParameterAttributesResponse (30)
/* ns1:GetParameterAttributesResponse */
class SOAP_CMAC _ns1__GetParameterAttributesResponse
{
public:
	class ParameterAttributeList *ParameterList;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type ArrayOfParameterAttributeStruct */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 30; } /* = unique id SOAP_TYPE__ns1__GetParameterAttributesResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__GetParameterAttributesResponse() : ParameterList(NULL), soap(NULL) { }
	virtual ~_ns1__GetParameterAttributesResponse() { }
};
#endif

#ifndef SOAP_TYPE_EventList
#define SOAP_TYPE_EventList (12)
/* SOAP encoded array of ns1:EventStruct schema type: */
class SOAP_CMAC EventList
{
public:
	ns1__EventStruct **__ptrEventStruct;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 12; } /* = unique id SOAP_TYPE_EventList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         EventList() : __ptrEventStruct(NULL), __size(0), soap(NULL) { }
	virtual ~EventList() { }
};
#endif

#ifndef SOAP_TYPE_ParameterValueList
#define SOAP_TYPE_ParameterValueList (14)
/* SOAP encoded array of ns1:ParameterValueStruct schema type: */
class SOAP_CMAC ParameterValueList
{
public:
	ns1__ParameterValueStruct **__ptrParameterValueStruct;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 14; } /* = unique id SOAP_TYPE_ParameterValueList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ParameterValueList() : __ptrParameterValueStruct(NULL), __size(0), soap(NULL) { }
	virtual ~ParameterValueList() { }
};
#endif

#ifndef SOAP_TYPE_ParameterInfoList
#define SOAP_TYPE_ParameterInfoList (16)
/* SOAP encoded array of ns1:ParameterInfoStruct schema type: */
class SOAP_CMAC ParameterInfoList
{
public:
	ns1__ParameterInfoStruct **__ptrParameterInfoStruct;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 16; } /* = unique id SOAP_TYPE_ParameterInfoList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ParameterInfoList() : __ptrParameterInfoStruct(NULL), __size(0), soap(NULL) { }
	virtual ~ParameterInfoList() { }
};
#endif

#ifndef SOAP_TYPE_ParameterNames
#define SOAP_TYPE_ParameterNames (17)
/* SOAP encoded array of xsd:string schema type: */
class SOAP_CMAC ParameterNames
{
public:
	std::string *__ptrstring;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 17; } /* = unique id SOAP_TYPE_ParameterNames */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ParameterNames() : __ptrstring(NULL), __size(0), soap(NULL) { }
	virtual ~ParameterNames() { }
};
#endif

#ifndef SOAP_TYPE_AccessList
#define SOAP_TYPE_AccessList (18)
/* SOAP encoded array of xsd:string schema type: */
class SOAP_CMAC AccessList
{
public:
	std::string *__ptrstring;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 18; } /* = unique id SOAP_TYPE_AccessList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         AccessList() : __ptrstring(NULL), __size(0), soap(NULL) { }
	virtual ~AccessList() { }
};
#endif

#ifndef SOAP_TYPE_SetParameterAttributesList
#define SOAP_TYPE_SetParameterAttributesList (20)
/* SOAP encoded array of ns1:SetParameterAttributesStruct schema type: */
class SOAP_CMAC SetParameterAttributesList
{
public:
	ns1__SetParameterAttributesStruct **__ptrSetParameterAttributesStruct;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 20; } /* = unique id SOAP_TYPE_SetParameterAttributesList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         SetParameterAttributesList() : __ptrSetParameterAttributesStruct(NULL), __size(0), soap(NULL) { }
	virtual ~SetParameterAttributesList() { }
};
#endif

#ifndef SOAP_TYPE_ParameterAttributeList
#define SOAP_TYPE_ParameterAttributeList (22)
/* SOAP encoded array of ns1:ParameterAttributeStruct schema type: */
class SOAP_CMAC ParameterAttributeList
{
public:
	ns1__ParameterAttributeStruct **__ptrParameterAttributeStruct;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 22; } /* = unique id SOAP_TYPE_ParameterAttributeList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ParameterAttributeList() : __ptrParameterAttributeStruct(NULL), __size(0), soap(NULL) { }
	virtual ~ParameterAttributeList() { }
};
#endif

#ifndef SOAP_TYPE___ns1__SetParameterValues
#define SOAP_TYPE___ns1__SetParameterValues (58)
/* Operation wrapper: */
struct __ns1__SetParameterValues
{
public:
	_ns1__SetParameterValues *ns1__SetParameterValues;	/* optional element of type ns1:SetParameterValues */
};
#endif

#ifndef SOAP_TYPE___ns1__GetParameterValues
#define SOAP_TYPE___ns1__GetParameterValues (62)
/* Operation wrapper: */
struct __ns1__GetParameterValues
{
public:
	_ns1__GetParameterValues *ns1__GetParameterValues;	/* optional element of type ns1:GetParameterValues */
};
#endif

#ifndef SOAP_TYPE___ns1__SetParameterAttributes
#define SOAP_TYPE___ns1__SetParameterAttributes (66)
/* Operation wrapper: */
struct __ns1__SetParameterAttributes
{
public:
	_ns1__SetParameterAttributes *ns1__SetParameterAttributes;	/* optional element of type ns1:SetParameterAttributes */
};
#endif

#ifndef SOAP_TYPE___ns1__GetParameterAttributes
#define SOAP_TYPE___ns1__GetParameterAttributes (70)
/* Operation wrapper: */
struct __ns1__GetParameterAttributes
{
public:
	_ns1__GetParameterAttributes *ns1__GetParameterAttributes;	/* optional element of type ns1:GetParameterAttributes */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (71)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (72)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (74)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
	char *__any;
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (77)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (78)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif

#ifndef SOAP_TYPE_xsd__anySimpleType
#define SOAP_TYPE_xsd__anySimpleType (9)
typedef std::string xsd__anySimpleType;
#endif

#ifndef SOAP_TYPE_ns1__CommandKeyType
#define SOAP_TYPE_ns1__CommandKeyType (31)
typedef std::string ns1__CommandKeyType;
#endif

#ifndef SOAP_TYPE_ns1__ParameterKeyType
#define SOAP_TYPE_ns1__ParameterKeyType (32)
typedef std::string ns1__ParameterKeyType;
#endif


/******************************************************************************\
 *                                                                            *
 * Typedef Synonyms                                                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Stubs                                                                      *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__SetParameterValues(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__SetParameterValues *ns1__SetParameterValues, _ns1__SetParameterValuesResponse *ns1__SetParameterValuesResponse);

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetParameterValues(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetParameterValues *ns1__GetParameterValues, _ns1__GetParameterValuesResponse *ns1__GetParameterValuesResponse);

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__SetParameterAttributes(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__SetParameterAttributes *ns1__SetParameterAttributes, _ns1__SetParameterAttributesResponse *ns1__SetParameterAttributesResponse);

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetParameterAttributes(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetParameterAttributes *ns1__GetParameterAttributes, _ns1__GetParameterAttributesResponse *ns1__GetParameterAttributesResponse);

#endif

/* End of soapStub.h */