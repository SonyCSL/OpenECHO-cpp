/*
 * ProfileObject.h
 *
 *  Created on: 2013/10/29
 *      Author: Fumiaki
 */

#ifndef PROFILEOBJECT_H_
#define PROFILEOBJECT_H_

#include "EchoObject.h"

class ProfileObject: public EchoObject {
public:
	class Receiver;
	class Setter;
	class Getter;
	class Informer;
	class InformerC;

public:
	static const unsigned char EPC_FAULT_STATUS;
	static const unsigned char EPC_MANUFACTURER_CODE;
	static const unsigned char EPC_PLACE_OF_BUSINESS_CODE;
	static const unsigned char EPC_PRODUCT_CODE;
	static const unsigned char EPC_SERIAL_NUMBER;
	static const unsigned char EPC_DATE_OF_MANUFACTURE;
	static const unsigned char EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP;
	static const unsigned char EPC_SET_PROPERTY_MAP;
	static const unsigned char EPC_GET_PROPERTY_MAP;

public:
	ProfileObject();
	virtual ~ProfileObject();

public:
	virtual bool setProperty(EchoProperty& property);
	virtual std::shared_ptr<std::vector<unsigned char> > getProperty(unsigned char epc);
	virtual bool isValidProperty(EchoProperty& property);

	ProfileObject::Setter set();
	ProfileObject::Setter set(bool responseRequired);
	ProfileObject::Getter get();
	ProfileObject::Informer inform();

protected:
	ProfileObject::Informer inform(bool multicast);
	ProfileObject::InformerC informC(std::string address);

	virtual void setupPropertyMaps();

	virtual std::shared_ptr<std::vector<unsigned char> > getFaultStatus();
	virtual bool isValidFaultStatus(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturerCode() = 0;
	virtual bool isValidManufacturerCode(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getPlaceOfBusinessCode();
	virtual bool isValidPlaceOfBusinessCode(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getProductCode();
	virtual bool isValidProductCode(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getSerialNumber();
	virtual bool isValidSerialNumber(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getDateOfManufacture();
	virtual bool isValidDateOfManufacture(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getStatusChangeAnnouncementPropertyMap();
	virtual bool isValidStatusChangeAnnouncementPropertyMap(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getSetPropertyMap();
	virtual bool isValidSetPropertyMap(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getGetPropertyMap();
	virtual bool isValidGetPropertyMap(std::vector<unsigned char>& edt);

public:
	class Receiver : public EchoObject::Receiver {
	public:
		Receiver();
		virtual ~Receiver();
	protected:
		virtual bool onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual bool onInformProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property);

		virtual void onGetFaultStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetManufacturerCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetPlaceOfBusinessCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetProductCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetSerialNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetDateOfManufacture(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetStatusChangeAnnouncementPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetSetPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetGetPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);

	};

	class Setter : public EchoObject::Setter {
	public:
		Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress, bool responseRequired);
		virtual ~Setter();
		virtual ProfileObject::Setter& reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);
	};

	class Getter : public EchoObject::Getter {
	public:
		Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~Getter();
		virtual ProfileObject::Getter& reqGetProperty(unsigned char epc);

		virtual ProfileObject::Getter& reqGetFaultStatus();
		virtual ProfileObject::Getter& reqGetManufacturerCode();
		virtual ProfileObject::Getter& reqGetPlaceOfBusinessCode();
		virtual ProfileObject::Getter& reqGetProductCode();
		virtual ProfileObject::Getter& reqGetSerialNumber();
		virtual ProfileObject::Getter& reqGetDateOfManufacture();
		virtual ProfileObject::Getter& reqGetStatusChangeAnnouncementPropertyMap();
		virtual ProfileObject::Getter& reqGetSetPropertyMap();
		virtual ProfileObject::Getter& reqGetGetPropertyMap();
	};

	class Informer : public EchoObject::Informer {
	public:
		Informer(unsigned short echoClassCode, unsigned char echoInstanceCode
				, std::string dstEchoAddress, bool isSelfObject);
		virtual ~Informer();
		virtual ProfileObject::Informer& reqInformProperty(unsigned char epc);

		virtual ProfileObject::Informer& reqInformFaultStatus();
		virtual ProfileObject::Informer& reqInformManufacturerCode();
		virtual ProfileObject::Informer& reqInformPlaceOfBusinessCode();
		virtual ProfileObject::Informer& reqInformProductCode();
		virtual ProfileObject::Informer& reqInformSerialNumber();
		virtual ProfileObject::Informer& reqInformDateOfManufacture();
		virtual ProfileObject::Informer& reqInformStatusChangeAnnouncementPropertyMap();
		virtual ProfileObject::Informer& reqInformSetPropertyMap();
		virtual ProfileObject::Informer& reqInformGetPropertyMap();
	};

	class InformerC : public EchoObject::InformerC {
	public:
		InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~InformerC();
		virtual ProfileObject::InformerC& reqInformProperty(unsigned char epc);
	};
};

#endif /* PROFILEOBJECT_H_ */
