/*
 * NodeProfile.cpp
 *
 *  Created on: 2013/10/29
 *      Author: Fumiaki
 */

#include "NodeProfile.h"
#include "OpenECHO.h"
#include <algorithm>

namespace sonycsl_openecho {

const unsigned short NodeProfile::ECHO_CLASS_CODE = 0x0EF0;
const unsigned char NodeProfile::INSTANCE_CODE = 0x01;
const unsigned char NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY = 0x02;

const unsigned char NodeProfile::EPC_OPERATING_STATUS = 0x80;
const unsigned char NodeProfile::EPC_VERSION_INFORMATION = 0x82;
const unsigned char NodeProfile::EPC_IDENTIFICATION_NUMBER = 0x83;
const unsigned char NodeProfile::EPC_FAULT_CONTENT = 0x89;
const unsigned char NodeProfile::EPC_UNIQUE_IDENTIFIER_DATA = 0xBF;
const unsigned char NodeProfile::EPC_NUMBER_OF_SELF_NODE_INSTANCES = 0xD3;
const unsigned char NodeProfile::EPC_NUMBER_OF_SELF_NODE_CLASSES = 0xD4;
const unsigned char NodeProfile::EPC_INSTANCE_LIST_NOTIFICATION = 0xD5;
const unsigned char NodeProfile::EPC_SELF_NODE_INSTANCE_LIST_S = 0xD6;
const unsigned char NodeProfile::EPC_SELF_NODE_CLASS_LIST = 0xD7;

NodeProfile::NodeProfile() : ProfileObject() {
	mVersionInformation = std::shared_ptr<std::vector<unsigned char> > (new std::vector<unsigned char>());
	mVersionInformation.get()->resize(4);
	(*(mVersionInformation.get()))[0] = 1;
	(*(mVersionInformation.get()))[1] = 10;
	(*(mVersionInformation.get()))[2] = 1;
	(*(mVersionInformation.get()))[3] = 0;


}

NodeProfile::~NodeProfile() {
	// TODO Auto-generated destructor stub
}

unsigned char NodeProfile::getInstanceCode() {
	return INSTANCE_CODE;
}

unsigned short NodeProfile::getEchoClassCode() {
	return ECHO_CLASS_CODE;
}

bool NodeProfile::setProperty(EchoProperty& property) {
	bool success = ProfileObject::setProperty(property);
	if(success) return true;

	switch(property.epc) {
	case EPC_OPERATING_STATUS : return setOperatingStatus(property.edt);
	case EPC_UNIQUE_IDENTIFIER_DATA: return setUniqueIdentifierData(property.edt);
	default : return false;
	}
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getProperty(
		unsigned char epc) {

	std::shared_ptr<std::vector<unsigned char> > edt = ProfileObject::getProperty(epc);
	if(edt.get() != nullptr) return edt;

	switch(epc) {
	case EPC_OPERATING_STATUS : return getOperatingStatus();
	case EPC_VERSION_INFORMATION : return getVersionInformation();
	case EPC_IDENTIFICATION_NUMBER : return getIdentificationNumber();
	case EPC_FAULT_CONTENT : return getFaultContent();
	case EPC_UNIQUE_IDENTIFIER_DATA : return getUniqueIdentifierData();
	case EPC_NUMBER_OF_SELF_NODE_INSTANCES : return getNumberOfSelfNodeInstances();
	case EPC_NUMBER_OF_SELF_NODE_CLASSES : return getNumberOfSelfNodeClasses();
	case EPC_INSTANCE_LIST_NOTIFICATION : return getInstanceListNotification();
	case EPC_SELF_NODE_INSTANCE_LIST_S : return getSelfNodeInstanceListS();
	case EPC_SELF_NODE_CLASS_LIST : return getSelfNodeClassList();
	default : return std::shared_ptr<std::vector<unsigned char> >();
	}
}

bool NodeProfile::isValidProperty(EchoProperty& property) {

	bool valid = ProfileObject::isValidProperty(property);
	if(valid) return true;

	switch(property.epc) {
	case EPC_OPERATING_STATUS : return isValidOperatingStatus(property.edt);
	case EPC_VERSION_INFORMATION : return isValidVersionInformation(property.edt);
	case EPC_IDENTIFICATION_NUMBER : return isValidIdentificationNumber(property.edt);
	case EPC_FAULT_CONTENT : return isValidFaultContent(property.edt);
	case EPC_UNIQUE_IDENTIFIER_DATA : return isValidUniqueIdentifierData(property.edt);
	case EPC_NUMBER_OF_SELF_NODE_INSTANCES : return isValidNumberOfSelfNodeInstances(property.edt);
	case EPC_NUMBER_OF_SELF_NODE_CLASSES : return isValidNumberOfSelfNodeClasses(property.edt);
	case EPC_INSTANCE_LIST_NOTIFICATION : return isValidInstanceListNotification(property.edt);
	case EPC_SELF_NODE_INSTANCE_LIST_S : return isValidSelfNodeInstanceListS(property.edt);
	case EPC_SELF_NODE_CLASS_LIST : return isValidSelfNodeClassList(property.edt);
	default : return false;
	}
}

NodeProfile::Setter NodeProfile::set() {
	return NodeProfile::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), true);
}

NodeProfile::Setter NodeProfile::set(bool responseRequired) {

	return NodeProfile::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), responseRequired);
}

NodeProfile::Getter NodeProfile::get() {

	return NodeProfile::Getter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress());
}

NodeProfile::Informer NodeProfile::inform() {

	std::string address;
	if(isProxy()) {
		address = getNode().get()->getAddress();
	} else {
		address = EchoSocket::MULTICAST_ADDRESS;
	}

	return NodeProfile::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

NodeProfile::Informer NodeProfile::inform(bool multicast) {

	std::string address;
	if(multicast) {
		address = EchoSocket::MULTICAST_ADDRESS;
	} else {
		address = getNode().get()->getAddress();
	}
	return NodeProfile::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

NodeProfile::InformerC NodeProfile::informC(std::string address) {

	return NodeProfile::InformerC(getEchoClassCode(), getInstanceCode()
			, address);
}

void NodeProfile::setupPropertyMaps() {

	ProfileObject::setupPropertyMaps();
	addStatusChangeAnnouncementProperty(EPC_OPERATING_STATUS);
	addStatusChangeAnnouncementProperty(EPC_INSTANCE_LIST_NOTIFICATION);

	addSetProperty(EPC_UNIQUE_IDENTIFIER_DATA);

	addGetProperty(EPC_OPERATING_STATUS);
	addGetProperty(EPC_VERSION_INFORMATION);
	addGetProperty(EPC_IDENTIFICATION_NUMBER);
	addGetProperty(EPC_NUMBER_OF_SELF_NODE_INSTANCES);
	addGetProperty(EPC_NUMBER_OF_SELF_NODE_CLASSES);
	addGetProperty(EPC_SELF_NODE_INSTANCE_LIST_S);
	addGetProperty(EPC_SELF_NODE_CLASS_LIST);

}

NodeProfile::Receiver::Receiver() : ProfileObject::Receiver()  {
}

NodeProfile::Receiver::~Receiver() {
}

bool NodeProfile::Receiver::onSetProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {

	bool ret = ProfileObject::Receiver::onSetProperty(eoj, tid, esv, property, success);
	if(ret) return true;
	switch(property.epc) {
	case EPC_OPERATING_STATUS:
		onSetOperatingStatus(eoj, tid, esv, property, success);
		return true;
	case EPC_UNIQUE_IDENTIFIER_DATA:
		onSetUniqueIdentifierData(eoj, tid, esv, property, success);
		return true;
	default :
		return false;
	}
}

bool NodeProfile::Receiver::onGetProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {

	bool ret = ProfileObject::Receiver::onGetProperty(eoj, tid, esv, property, success);
	if(ret) return true;

	switch(property.epc) {
	case EPC_OPERATING_STATUS:
		onGetOperatingStatus(eoj, tid, esv, property, success);
		return true;
	case EPC_VERSION_INFORMATION:
		onGetVersionInformation(eoj, tid, esv, property, success);
		return true;
	case EPC_IDENTIFICATION_NUMBER:
		onGetIdentificationNumber(eoj, tid, esv, property, success);
		return true;
	case EPC_FAULT_CONTENT:
		onGetFaultContent(eoj, tid, esv, property, success);
		return true;
	case EPC_UNIQUE_IDENTIFIER_DATA:
		onGetUniqueIdentifierData(eoj, tid, esv, property, success);
		return true;
	case EPC_NUMBER_OF_SELF_NODE_INSTANCES:
		onGetNumberOfSelfNodeInstances(eoj, tid, esv, property, success);
		return true;
	case EPC_NUMBER_OF_SELF_NODE_CLASSES:
		onGetNumberOfSelfNodeClasses(eoj, tid, esv, property, success);
		return true;
	case EPC_INSTANCE_LIST_NOTIFICATION:
		onGetInstanceListNotification(eoj, tid, esv, property, success);
		return true;
	case EPC_SELF_NODE_INSTANCE_LIST_S:
		onGetSelfNodeInstanceListS(eoj, tid, esv, property, success);
		return true;
	case EPC_SELF_NODE_CLASS_LIST:
		onGetSelfNodeClassList(eoj, tid, esv, property, success);
		return true;
	default :
		return false;
	}
}

bool NodeProfile::Receiver::onInformProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property) {
	bool ret = ProfileObject::Receiver::onInformProperty(eoj, tid, esv, property);
	if(ret) return true;

	switch(property.epc) {
	case EPC_INSTANCE_LIST_NOTIFICATION:
		onInformInstanceListNotification(eoj, tid, esv, property);
		return true;
	default :
		return false;
	}
}

NodeProfile::Setter::Setter(unsigned short dstEchoClassCode,
		unsigned char dstEchoInstanceCode, std::string dstEchoAddress,
		bool responseRequired)
	: ProfileObject::Setter(dstEchoClassCode
	, dstEchoInstanceCode ,dstEchoAddress, responseRequired){
}

NodeProfile::Setter::~Setter() {
}

NodeProfile::Setter& NodeProfile::Setter::reqSetProperty(unsigned char epc,
		std::vector<unsigned char> edt) {
	return dynamic_cast<NodeProfile::Setter&>(ProfileObject::Setter::reqSetProperty(epc, edt));

}

NodeProfile::Getter::Getter(unsigned short dstEchoClassCode,
		unsigned char dstEchoInstanceCode, std::string dstEchoAddress)
	: ProfileObject::Getter(dstEchoClassCode
	, dstEchoInstanceCode, dstEchoAddress)  {
}

NodeProfile::Getter::~Getter() {
}

NodeProfile::Getter& NodeProfile::Getter::reqGetProperty(unsigned char epc) {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetProperty(epc));
}

NodeProfile::Informer::Informer(unsigned short echoClassCode,
		unsigned char echoInstanceCode, std::string dstEchoAddress,
		bool isSelfObject)
	: ProfileObject::Informer(echoClassCode, echoInstanceCode
	, dstEchoAddress, isSelfObject) {
}

NodeProfile::Informer::~Informer() {
}

NodeProfile::Informer& NodeProfile::Informer::reqInformProperty(
		unsigned char epc) {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformProperty(epc));

}

NodeProfile::InformerC::InformerC(unsigned short srcEchoClassCode,
		unsigned char srcEchoInstanceCode, std::string dstEchoAddress)
	: ProfileObject::InformerC(srcEchoClassCode
	, srcEchoInstanceCode, dstEchoAddress)  {
}

NodeProfile::InformerC::~InformerC() {
}

NodeProfile::InformerC& NodeProfile::InformerC::reqInformProperty(
		unsigned char epc) {
	return dynamic_cast<NodeProfile::InformerC&>(ProfileObject::InformerC::reqInformProperty(epc));
}

NodeProfile::Proxy::Proxy() : NodeProfile() {
	mEchoInstanceCode = INSTANCE_CODE;
}

NodeProfile::Proxy::~Proxy() {
}

void NodeProfile::Proxy::setInstanceCode(unsigned char instanceCode) {
	mEchoInstanceCode = instanceCode;
}

unsigned char NodeProfile::Proxy::getInstanceCode() {
	return mEchoInstanceCode;
}

bool NodeProfile::setOperatingStatus(std::vector<unsigned char>& edt) {
	return false;
}

bool NodeProfile::isValidOperatingStatus(std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getVersionInformation() {
	return mVersionInformation;
}

bool NodeProfile::isValidVersionInformation(std::vector<unsigned char>& edt) {
	if(edt.size() != 4) return false;
	return true;
}

bool NodeProfile::isValidIdentificationNumber(std::vector<unsigned char>& edt) {
	if(edt.size() != 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getFaultContent() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool NodeProfile::isValidFaultContent(std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

bool NodeProfile::setUniqueIdentifierData(std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getUniqueIdentifierData() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool NodeProfile::isValidUniqueIdentifierData(std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getNumberOfSelfNodeInstances() {

	std::shared_ptr<std::vector<unsigned char> > edt(new std::vector<unsigned char>());
	if(getNode().get() != nullptr) {
		int size = getNode().get()->getDevices().size();
		edt.get()->resize(3);
		(*(edt.get()))[0] = ((size >> 16) & 0xFF);
		(*(edt.get()))[1] = ((size >> 8) & 0xFF);
		(*(edt.get()))[2] = (size & 0xFF);
	}

	return edt;
}

bool NodeProfile::isValidNumberOfSelfNodeInstances(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 3) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getNumberOfSelfNodeClasses() {

	std::shared_ptr<std::vector<unsigned char> > edt(new std::vector<unsigned char>());
	if(getNode().get() != nullptr) {
		std::vector<std::shared_ptr<DeviceObject> > devices = getNode().get()->getDevices();
		std::vector<unsigned short> classList;
		int devicesSize = devices.size();
		for(int i = 0; i < devicesSize; i++) {
			unsigned short code = devices.at(i).get()->getEchoClassCode();
			std::vector<unsigned short>::iterator itr = std::find(
					classList.begin(), classList.end(), code);
			if (itr == classList.end()) {
				classList.push_back(code);
			}
		}
		int size = classList.size() + 1;
		edt.get()->resize(2);
		(*(edt.get()))[0] = ((size >> 16) & 0xFF);
		(*(edt.get()))[1] = ((size >> 8) & 0xFF);
	}

	return edt;
}

bool NodeProfile::isValidNumberOfSelfNodeClasses(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getInstanceListNotification() {

	std::shared_ptr<std::vector<unsigned char> > edt(new std::vector<unsigned char>());
	if(getNode().get() != nullptr) {
		std::vector<std::shared_ptr<DeviceObject> > devices = getNode().get()->getDevices();

		int size = devices.size();
		edt.get()->push_back(size);
		for(int i = 0; (i < size) && (i < 84); i++) {
			edt.get()->push_back(devices.at(i).get()->getClassGroupCode());
			edt.get()->push_back(devices.at(i).get()->getClassCode());
			edt.get()->push_back(devices.at(i).get()->getInstanceCode());
		}
	}

	return edt;
}

bool NodeProfile::isValidInstanceListNotification(
		std::vector<unsigned char>& edt) {
	if(edt.size() < 1) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getSelfNodeInstanceListS() {

	std::shared_ptr<std::vector<unsigned char> > edt(new std::vector<unsigned char>());
	if(getNode().get() != nullptr) {
		std::vector<std::shared_ptr<DeviceObject> > devices = getNode().get()->getDevices();

		int size = devices.size();
		if(size > 84) {size = 84;}
		edt.get()->push_back(size);
		for(int i = 0; i < size; i++) {
			edt.get()->push_back(devices.at(i).get()->getClassGroupCode());
			edt.get()->push_back(devices.at(i).get()->getClassCode());
			edt.get()->push_back(devices.at(i).get()->getInstanceCode());
		}
	}

	return edt;
}

bool NodeProfile::isValidSelfNodeInstanceListS(
		std::vector<unsigned char>& edt) {
	if(edt.size() > 253) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::getSelfNodeClassList() {

	std::shared_ptr<std::vector<unsigned char> > edt(new std::vector<unsigned char>());
	if(getNode().get() != nullptr) {
		std::vector<std::shared_ptr<DeviceObject> > devices = getNode().get()->getDevices();
		std::vector<unsigned short> classList;
		int devicesSize = devices.size();
		for(int i = 0; i < devicesSize; i++) {
			unsigned short code = devices.at(i).get()->getEchoClassCode();
			std::vector<unsigned short>::iterator itr = std::find(
					classList.begin(), classList.end(), code);
			if (itr == classList.end()) {
				classList.push_back(code);
			}
		}
		int size = classList.size();
		edt.get()->push_back(size);
		for(int i = 0; (i < size) && (i < 8); i++) {
			edt.get()->push_back((classList.at(i) >> 8) & 0xFF);
			edt.get()->push_back(classList.at(i) & 0xFF);
		}
	}

	return edt;
}

bool NodeProfile::isValidSelfNodeClassList(std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

void NodeProfile::Receiver::onSetOperatingStatus(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onSetUniqueIdentifierData(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetOperatingStatus(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetVersionInformation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetIdentificationNumber(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetFaultContent(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
}

void NodeProfile::Receiver::onGetUniqueIdentifierData(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetNumberOfSelfNodeInstances(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetNumberOfSelfNodeClasses(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetInstanceListNotification(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetSelfNodeInstanceListS(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onGetSelfNodeClassList(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void NodeProfile::Receiver::onInformInstanceListNotification(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property) {
}

NodeProfile::Setter& NodeProfile::Setter::reqSetOperatingStatus(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_OPERATING_STATUS, edt);
}

NodeProfile::Setter& NodeProfile::Setter::reqSetUniqueIdentifierData(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_UNIQUE_IDENTIFIER_DATA, edt);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetFaultStatus() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetFaultStatus());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetManufacturerCode() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetManufacturerCode());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetPlaceOfBusinessCode() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetPlaceOfBusinessCode());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetProductCode() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetProductCode());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetSerialNumber() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetProductCode());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetDateOfManufacture() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetDateOfManufacture());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetStatusChangeAnnouncementPropertyMap() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetStatusChangeAnnouncementPropertyMap());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetSetPropertyMap() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetSetPropertyMap());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetGetPropertyMap() {
	return dynamic_cast<NodeProfile::Getter&>(ProfileObject::Getter::reqGetGetPropertyMap());
}

NodeProfile::Getter& NodeProfile::Getter::reqGetOperatingStatus() {
	return reqGetProperty(EPC_OPERATING_STATUS);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetVersionInformation() {
	return reqGetProperty(EPC_VERSION_INFORMATION);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetIdentificationNumber() {
	return reqGetProperty(EPC_IDENTIFICATION_NUMBER);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetFaultContent() {
	return reqGetProperty(EPC_FAULT_CONTENT);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetUniqueIdentifierData() {
	return reqGetProperty(EPC_UNIQUE_IDENTIFIER_DATA);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetNumberOfSelfNodeInstances() {
	return reqGetProperty(EPC_NUMBER_OF_SELF_NODE_INSTANCES);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetNumberOfSelfNodeClasses() {
	return reqGetProperty(EPC_NUMBER_OF_SELF_NODE_CLASSES);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetSelfNodeInstanceListS() {
	return reqGetProperty(EPC_SELF_NODE_INSTANCE_LIST_S);
}

NodeProfile::Getter& NodeProfile::Getter::reqGetSelfNodeClassList() {
	return reqGetProperty(EPC_SELF_NODE_CLASS_LIST);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformFaultStatus() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformFaultStatus());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformManufacturerCode() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformManufacturerCode());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformPlaceOfBusinessCode() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformPlaceOfBusinessCode());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformProductCode() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformProductCode());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformSerialNumber() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformSerialNumber());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformDateOfManufacture() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformDateOfManufacture());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformStatusChangeAnnouncementPropertyMap() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformStatusChangeAnnouncementPropertyMap());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformSetPropertyMap() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformSetPropertyMap());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformGetPropertyMap() {
	return dynamic_cast<NodeProfile::Informer&>(ProfileObject::Informer::reqInformGetPropertyMap());
}

NodeProfile::Informer& NodeProfile::Informer::reqInformOperatingStatus() {
	return reqInformProperty(EPC_OPERATING_STATUS);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformVersionInformation() {
	return reqInformProperty(EPC_VERSION_INFORMATION);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformIdentificationNumber() {
	return reqInformProperty(EPC_IDENTIFICATION_NUMBER);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformFaultContent() {
	return reqInformProperty(EPC_FAULT_CONTENT);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformUniqueIdentifierData() {
	return reqInformProperty(EPC_UNIQUE_IDENTIFIER_DATA);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformNumberOfSelfNodeInstances() {
	return reqInformProperty(EPC_NUMBER_OF_SELF_NODE_INSTANCES);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformNumberOfSelfNodeClasses() {
	return reqInformProperty(EPC_NUMBER_OF_SELF_NODE_CLASSES);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformInstanceListNotification() {
	return reqInformProperty(EPC_INSTANCE_LIST_NOTIFICATION);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformSelfNodeInstanceListS() {
	return reqInformProperty(EPC_SELF_NODE_INSTANCE_LIST_S);
}

NodeProfile::Informer& NodeProfile::Informer::reqInformSelfNodeClassList() {
	return reqInformProperty(EPC_SELF_NODE_CLASS_LIST);
}

NodeProfile::InformerC& NodeProfile::InformerC::reqInformInstanceListNotification() {
	return reqInformProperty(EPC_INSTANCE_LIST_NOTIFICATION);
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::Proxy::getManufacturerCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::Proxy::getOperatingStatus() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

std::shared_ptr<std::vector<unsigned char> > NodeProfile::Proxy::getIdentificationNumber() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

};
