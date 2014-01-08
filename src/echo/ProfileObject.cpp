/*
 * ProfileObject.cpp
 *
 *  Created on: 2013/10/29
 *      Author: Fumiaki
 */

#include "ProfileObject.h"
#include "OpenECHO.h"

const unsigned char ProfileObject::EPC_FAULT_STATUS = 0x88;
const unsigned char ProfileObject::EPC_MANUFACTURER_CODE = 0x8A;
const unsigned char ProfileObject::EPC_PLACE_OF_BUSINESS_CODE = 0x8B;
const unsigned char ProfileObject::EPC_PRODUCT_CODE =  0x8C;
const unsigned char ProfileObject::EPC_SERIAL_NUMBER = 0x8D;
const unsigned char ProfileObject::EPC_DATE_OF_MANUFACTURE = 0x8E;
const unsigned char ProfileObject::EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP = 0x9D;
const unsigned char ProfileObject::EPC_SET_PROPERTY_MAP = 0x9E;
const unsigned char ProfileObject::EPC_GET_PROPERTY_MAP = 0x9F;

ProfileObject::ProfileObject() : EchoObject() {
	// TODO Auto-generated constructor stub

}

ProfileObject::~ProfileObject() {
	// TODO Auto-generated destructor stub
}

bool ProfileObject::setProperty(EchoProperty& property) {
	bool success = EchoObject::setProperty(property);
	if(success) return true;

	switch(property.epc) {
	default : return false;
	}
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getProperty(
		unsigned char epc) {
	std::shared_ptr<std::vector<unsigned char> > edt = EchoObject::getProperty(epc);
	if(edt.get() != nullptr) return edt;

	switch(epc) {
	case EPC_FAULT_STATUS : return getFaultStatus();
	case EPC_MANUFACTURER_CODE : return getManufacturerCode();
	case EPC_PLACE_OF_BUSINESS_CODE : return getPlaceOfBusinessCode();
	case EPC_PRODUCT_CODE : return getProductCode();
	case EPC_SERIAL_NUMBER : return getSerialNumber();
	case EPC_DATE_OF_MANUFACTURE : return getDateOfManufacture();
	case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP : return getStatusChangeAnnouncementPropertyMap();
	case EPC_SET_PROPERTY_MAP : return getSetPropertyMap();
	case EPC_GET_PROPERTY_MAP : return getGetPropertyMap();
	default : return std::shared_ptr<std::vector<unsigned char> >();
	}
}

bool ProfileObject::isValidProperty(EchoProperty& property) {
	bool valid = EchoObject::isValidProperty(property);
	if(valid) return true;

	switch(property.epc) {
	case EPC_FAULT_STATUS : return isValidFaultStatus(property.edt);
	case EPC_MANUFACTURER_CODE : return isValidManufacturerCode(property.edt);
	case EPC_PLACE_OF_BUSINESS_CODE : return isValidPlaceOfBusinessCode(property.edt);
	case EPC_PRODUCT_CODE : return isValidProductCode(property.edt);
	case EPC_SERIAL_NUMBER : return isValidSerialNumber(property.edt);
	case EPC_DATE_OF_MANUFACTURE : return isValidDateOfManufacture(property.edt);
	case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP : return isValidStatusChangeAnnouncementPropertyMap(property.edt);
	case EPC_SET_PROPERTY_MAP : return isValidSetPropertyMap(property.edt);
	case EPC_GET_PROPERTY_MAP : return isValidGetPropertyMap(property.edt);
	default : return false;
	}
}

ProfileObject::Setter ProfileObject::set() {
	return ProfileObject::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), true);
}

ProfileObject::Setter ProfileObject::set(bool responseRequired) {

	return ProfileObject::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), responseRequired);
}

ProfileObject::Getter ProfileObject::get() {

	return ProfileObject::Getter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress());
}

ProfileObject::Informer ProfileObject::inform() {

	std::string address;
	if(isProxy()) {
		address = getNode().get()->getAddress();
	} else {
		address = EchoSocket::MULTICAST_ADDRESS;
	}
	return ProfileObject::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

ProfileObject::Informer ProfileObject::inform(bool multicast) {

	std::string address;
	if(multicast) {
		address = EchoSocket::MULTICAST_ADDRESS;
	} else {
		address = getNode().get()->getAddress();
	}
	return ProfileObject::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

ProfileObject::InformerC ProfileObject::informC(std::string address) {

	return ProfileObject::InformerC(getEchoClassCode(), getInstanceCode()
			, address);
}

void ProfileObject::setupPropertyMaps() {
	EchoObject::setupPropertyMaps();

	addGetProperty(EPC_MANUFACTURER_CODE);
	addGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
	addGetProperty(EPC_SET_PROPERTY_MAP);
	addGetProperty(EPC_GET_PROPERTY_MAP);

}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getFaultStatus() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool ProfileObject::isValidFaultStatus(std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

bool ProfileObject::isValidManufacturerCode(std::vector<unsigned char>& edt) {
	if(edt.size() != 3) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getPlaceOfBusinessCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool ProfileObject::isValidPlaceOfBusinessCode(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 3) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getProductCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool ProfileObject::isValidProductCode(std::vector<unsigned char>& edt) {
	if(edt.size() != 12) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getSerialNumber() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool ProfileObject::isValidSerialNumber(std::vector<unsigned char>& edt) {
	if(edt.size() != 12) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getDateOfManufacture() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool ProfileObject::isValidDateOfManufacture(std::vector<unsigned char>& edt) {
	if(edt.size() != 4) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getStatusChangeAnnouncementPropertyMap() {
	return EchoUtils::convertPropertiesToPropertyMap(getStatusChangeAnnouncementProperties());
}

bool ProfileObject::isValidStatusChangeAnnouncementPropertyMap(
		std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getSetPropertyMap() {
	return EchoUtils::convertPropertiesToPropertyMap(getSetProperties());
}

bool ProfileObject::isValidSetPropertyMap(std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > ProfileObject::getGetPropertyMap() {
	return EchoUtils::convertPropertiesToPropertyMap(getGetProperties());
}

bool ProfileObject::isValidGetPropertyMap(std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

ProfileObject::Receiver::Receiver() : EchoObject::Receiver() {
}

ProfileObject::Receiver::~Receiver() {
}

bool ProfileObject::Receiver::onSetProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
	bool ret = EchoObject::Receiver::onSetProperty(eoj, tid, esv, property, success);
	if(ret) return true;
	return false;
}

bool ProfileObject::Receiver::onGetProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
	bool ret = EchoObject::Receiver::onGetProperty(eoj, tid, esv, property, success);
	if(ret) return true;
	switch(property.epc) {
	case EPC_FAULT_STATUS:
		onGetFaultStatus(eoj, tid, esv, property, success);
		return true;
	case EPC_MANUFACTURER_CODE:
		onGetManufacturerCode(eoj, tid, esv, property, success);
		return true;
	case EPC_PLACE_OF_BUSINESS_CODE:
		onGetPlaceOfBusinessCode(eoj, tid, esv, property, success);
		return true;
	case EPC_PRODUCT_CODE:
		onGetProductCode(eoj, tid, esv, property, success);
		return true;
	case EPC_SERIAL_NUMBER:
		onGetSerialNumber(eoj, tid, esv, property, success);
		return true;
	case EPC_DATE_OF_MANUFACTURE:
		onGetDateOfManufacture(eoj, tid, esv, property, success);
		return true;
	case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP:
		onGetStatusChangeAnnouncementPropertyMap(eoj, tid, esv, property, success);
		return true;
	case EPC_SET_PROPERTY_MAP:
		onGetSetPropertyMap(eoj, tid, esv, property, success);
		return true;
	case EPC_GET_PROPERTY_MAP:
		onGetGetPropertyMap(eoj, tid, esv, property, success);
		return true;
	default :
		return false;
	}
}

bool ProfileObject::Receiver::onInformProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property) {
	bool ret = EchoObject::Receiver::onInformProperty(eoj, tid, esv, property);
	if(ret) return true;
	return false;
}

void ProfileObject::Receiver::onGetFaultStatus(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
}

void ProfileObject::Receiver::onGetManufacturerCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void ProfileObject::Receiver::onGetPlaceOfBusinessCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void ProfileObject::Receiver::onGetProductCode(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
}

void ProfileObject::Receiver::onGetSerialNumber(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
}

void ProfileObject::Receiver::onGetDateOfManufacture(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void ProfileObject::Receiver::onGetStatusChangeAnnouncementPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void ProfileObject::Receiver::onGetSetPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void ProfileObject::Receiver::onGetGetPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

ProfileObject::Setter::Setter(unsigned short dstEchoClassCode,
		unsigned char dstEchoInstanceCode, std::string dstEchoAddress,
		bool responseRequired)
	: EchoObject::Setter(dstEchoClassCode
	, dstEchoInstanceCode ,dstEchoAddress, responseRequired) {
}

ProfileObject::Setter::~Setter() {
}

ProfileObject::Setter& ProfileObject::Setter::reqSetProperty(unsigned char epc,
		std::vector<unsigned char> edt) {
	return dynamic_cast<ProfileObject::Setter&>(EchoObject::Setter::reqSetProperty(epc, edt));
}

ProfileObject::Getter::Getter(unsigned short dstEchoClassCode,
		unsigned char dstEchoInstanceCode, std::string dstEchoAddress)
	: EchoObject::Getter(dstEchoClassCode
	, dstEchoInstanceCode, dstEchoAddress) {
}

ProfileObject::Getter::~Getter() {
}

ProfileObject::Getter& ProfileObject::Getter::reqGetProperty(
		unsigned char epc) {
	return dynamic_cast<ProfileObject::Getter&>(EchoObject::Getter::reqGetProperty(epc));

}

ProfileObject::Informer::Informer(unsigned short echoClassCode,
		unsigned char echoInstanceCode, std::string dstEchoAddress,
		bool isSelfObject)
	: EchoObject::Informer(echoClassCode, echoInstanceCode
	, dstEchoAddress, isSelfObject) {
}

ProfileObject::Informer::~Informer() {
}

ProfileObject::Informer& ProfileObject::Informer::reqInformProperty(
		unsigned char epc) {
	return dynamic_cast<ProfileObject::Informer&>(EchoObject::Informer::reqInformProperty(epc));

}

ProfileObject::InformerC::InformerC(unsigned short srcEchoClassCode,
		unsigned char srcEchoInstanceCode, std::string dstEchoAddress)
	: EchoObject::InformerC(srcEchoClassCode
	, srcEchoInstanceCode, dstEchoAddress) {
}

ProfileObject::InformerC::~InformerC() {
}

ProfileObject::InformerC& ProfileObject::InformerC::reqInformProperty(
		unsigned char epc) {
	return dynamic_cast<ProfileObject::InformerC&>(EchoObject::InformerC::reqInformProperty(epc));

}

ProfileObject::Getter& ProfileObject::Getter::reqGetFaultStatus() {
	return reqGetProperty(EPC_FAULT_STATUS);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetManufacturerCode() {
	return reqGetProperty(EPC_MANUFACTURER_CODE);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetPlaceOfBusinessCode() {
	return reqGetProperty(EPC_PLACE_OF_BUSINESS_CODE);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetProductCode() {
	return reqGetProperty(EPC_PRODUCT_CODE);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetSerialNumber() {
	return reqGetProperty(EPC_SERIAL_NUMBER);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetDateOfManufacture() {
	return reqGetProperty(EPC_DATE_OF_MANUFACTURE);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetStatusChangeAnnouncementPropertyMap() {
	return reqGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetSetPropertyMap() {
	return reqGetProperty(EPC_SET_PROPERTY_MAP);
}

ProfileObject::Getter& ProfileObject::Getter::reqGetGetPropertyMap() {
	return reqGetProperty(EPC_GET_PROPERTY_MAP);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformFaultStatus() {
	return reqInformProperty(EPC_FAULT_STATUS);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformManufacturerCode() {
	return reqInformProperty(EPC_MANUFACTURER_CODE);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformPlaceOfBusinessCode() {
	return reqInformProperty(EPC_PLACE_OF_BUSINESS_CODE);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformProductCode() {
	return reqInformProperty(EPC_PRODUCT_CODE);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformSerialNumber() {
	return reqInformProperty(EPC_SERIAL_NUMBER);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformDateOfManufacture() {
	return reqInformProperty(EPC_DATE_OF_MANUFACTURE);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformStatusChangeAnnouncementPropertyMap() {
	return reqInformProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformSetPropertyMap() {
	return reqInformProperty(EPC_SET_PROPERTY_MAP);
}

ProfileObject::Informer& ProfileObject::Informer::reqInformGetPropertyMap() {
	return reqInformProperty(EPC_GET_PROPERTY_MAP);
}
