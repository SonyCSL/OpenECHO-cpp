/*
 * NodeProfile.h
 *
 *  Created on: 2013/10/29
 *      Author: Fumiaki
 */

#ifndef NODEPROFILE_H_
#define NODEPROFILE_H_

#include "ProfileObject.h"

namespace sonycsl_openecho {

class NodeProfile: public ProfileObject {
public:
	class Receiver;
	class Setter;
	class Getter;
	class Informer;
	class InformerC;
	class Proxy;

public:
	static const unsigned short ECHO_CLASS_CODE;
	static const unsigned char INSTANCE_CODE;
	static const unsigned char INSTANCE_CODE_TRANSMISSION_ONLY;

	static const unsigned char EPC_OPERATING_STATUS;
	static const unsigned char EPC_VERSION_INFORMATION;
	static const unsigned char EPC_IDENTIFICATION_NUMBER;
	static const unsigned char EPC_FAULT_CONTENT;
	static const unsigned char EPC_UNIQUE_IDENTIFIER_DATA;
	static const unsigned char EPC_NUMBER_OF_SELF_NODE_INSTANCES;
	static const unsigned char EPC_NUMBER_OF_SELF_NODE_CLASSES;
	static const unsigned char EPC_INSTANCE_LIST_NOTIFICATION;
	static const unsigned char EPC_SELF_NODE_INSTANCE_LIST_S;
	static const unsigned char EPC_SELF_NODE_CLASS_LIST;

protected:
	std::shared_ptr<std::vector<unsigned char> > mVersionInformation;

public:
	NodeProfile();
	virtual ~NodeProfile();

	virtual unsigned char getInstanceCode();
	virtual unsigned short getEchoClassCode();

public:
	virtual bool setProperty(EchoProperty& property);
	virtual std::shared_ptr<std::vector<unsigned char> > getProperty(unsigned char epc);
	virtual bool isValidProperty(EchoProperty& property);

	NodeProfile::Setter set();
	NodeProfile::Setter set(bool responseRequired);
	NodeProfile::Getter get();
	NodeProfile::Informer inform();

protected:
	NodeProfile::Informer inform(bool multicast);
	NodeProfile::InformerC informC(std::string address);

	virtual void setupPropertyMaps();

	virtual bool setOperatingStatus(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getOperatingStatus() = 0;
	virtual bool isValidOperatingStatus(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getVersionInformation();
	virtual bool isValidVersionInformation(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getIdentificationNumber() = 0;
	virtual bool isValidIdentificationNumber(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getFaultContent();
	virtual bool isValidFaultContent(std::vector<unsigned char>& edt);
	virtual bool setUniqueIdentifierData(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getUniqueIdentifierData();
	virtual bool isValidUniqueIdentifierData(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getNumberOfSelfNodeInstances();
	virtual bool isValidNumberOfSelfNodeInstances(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getNumberOfSelfNodeClasses();
	virtual bool isValidNumberOfSelfNodeClasses(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getInstanceListNotification();
	virtual bool isValidInstanceListNotification(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getSelfNodeInstanceListS();
	virtual bool isValidSelfNodeInstanceListS(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getSelfNodeClassList();
	virtual bool isValidSelfNodeClassList(std::vector<unsigned char>& edt);


public:
	class Receiver : public ProfileObject::Receiver {
	public:
		Receiver();
		virtual ~Receiver();
	protected:
		virtual bool onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual bool onInformProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property);

		virtual void onSetOperatingStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetUniqueIdentifierData(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);

		virtual void onGetOperatingStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetVersionInformation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetIdentificationNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetFaultContent(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetUniqueIdentifierData(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetNumberOfSelfNodeInstances(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetNumberOfSelfNodeClasses(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetInstanceListNotification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetSelfNodeInstanceListS(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetSelfNodeClassList(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);

		virtual void onInformInstanceListNotification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property);

	};

	class Setter : public ProfileObject::Setter {
	public:
		Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress, bool responseRequired);
		virtual ~Setter();
		virtual NodeProfile::Setter& reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);

		virtual NodeProfile::Setter& reqSetOperatingStatus(std::vector<unsigned char> edt);
		virtual NodeProfile::Setter& reqSetUniqueIdentifierData(std::vector<unsigned char> edt);

	};

	class Getter : public ProfileObject::Getter {
	public:
		Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~Getter();
		virtual NodeProfile::Getter& reqGetProperty(unsigned char epc);

		virtual NodeProfile::Getter& reqGetFaultStatus();
		virtual NodeProfile::Getter& reqGetManufacturerCode();
		virtual NodeProfile::Getter& reqGetPlaceOfBusinessCode();
		virtual NodeProfile::Getter& reqGetProductCode();
		virtual NodeProfile::Getter& reqGetSerialNumber();
		virtual NodeProfile::Getter& reqGetDateOfManufacture();
		virtual NodeProfile::Getter& reqGetStatusChangeAnnouncementPropertyMap();
		virtual NodeProfile::Getter& reqGetSetPropertyMap();
		virtual NodeProfile::Getter& reqGetGetPropertyMap();

		virtual NodeProfile::Getter& reqGetOperatingStatus();
		virtual NodeProfile::Getter& reqGetVersionInformation();
		virtual NodeProfile::Getter& reqGetIdentificationNumber();
		virtual NodeProfile::Getter& reqGetFaultContent();
		virtual NodeProfile::Getter& reqGetUniqueIdentifierData();
		virtual NodeProfile::Getter& reqGetNumberOfSelfNodeInstances();
		virtual NodeProfile::Getter& reqGetNumberOfSelfNodeClasses();
		virtual NodeProfile::Getter& reqGetSelfNodeInstanceListS();
		virtual NodeProfile::Getter& reqGetSelfNodeClassList();
	};

	class Informer : public ProfileObject::Informer {
	public:
		Informer(unsigned short echoClassCode, unsigned char echoInstanceCode
				, std::string dstEchoAddress, bool isSelfObject);
		virtual ~Informer();
		virtual NodeProfile::Informer& reqInformProperty(unsigned char epc);

		virtual NodeProfile::Informer& reqInformFaultStatus();
		virtual NodeProfile::Informer& reqInformManufacturerCode();
		virtual NodeProfile::Informer& reqInformPlaceOfBusinessCode();
		virtual NodeProfile::Informer& reqInformProductCode();
		virtual NodeProfile::Informer& reqInformSerialNumber();
		virtual NodeProfile::Informer& reqInformDateOfManufacture();
		virtual NodeProfile::Informer& reqInformStatusChangeAnnouncementPropertyMap();
		virtual NodeProfile::Informer& reqInformSetPropertyMap();
		virtual NodeProfile::Informer& reqInformGetPropertyMap();

		virtual NodeProfile::Informer& reqInformOperatingStatus();
		virtual NodeProfile::Informer& reqInformVersionInformation();
		virtual NodeProfile::Informer& reqInformIdentificationNumber();
		virtual NodeProfile::Informer& reqInformFaultContent();
		virtual NodeProfile::Informer& reqInformUniqueIdentifierData();
		virtual NodeProfile::Informer& reqInformNumberOfSelfNodeInstances();
		virtual NodeProfile::Informer& reqInformNumberOfSelfNodeClasses();
		virtual NodeProfile::Informer& reqInformInstanceListNotification();
		virtual NodeProfile::Informer& reqInformSelfNodeInstanceListS();
		virtual NodeProfile::Informer& reqInformSelfNodeClassList();
	};

	class InformerC : public ProfileObject::InformerC {
	public:
		InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~InformerC();
		virtual NodeProfile::InformerC& reqInformProperty(unsigned char epc);

		virtual NodeProfile::InformerC& reqInformInstanceListNotification();

	};

};

class NodeProfile::Proxy : public NodeProfile {
protected:
	unsigned char mEchoInstanceCode;
public:
	Proxy();
	virtual ~Proxy();

	virtual void setInstanceCode(unsigned char instanceCode);
	virtual unsigned char getInstanceCode();
protected:
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturerCode();
	virtual std::shared_ptr<std::vector<unsigned char> > getOperatingStatus();
	virtual std::shared_ptr<std::vector<unsigned char> > getIdentificationNumber();
};

};

#endif /* NODEPROFILE_H_ */
