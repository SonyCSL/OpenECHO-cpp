/*
 * DeviceObject.cpp
 *
 *  Created on: 2013/10/29
 *      Author: Fumiaki
 */

#include "DeviceObject.h"
#include "OpenECHO.h"


namespace sonycsl_openecho {

const unsigned char DeviceObject::EPC_OPERATION_STATUS = 0x80;
const unsigned char DeviceObject::EPC_INSTALLATION_LOCATION = 0x81;
const unsigned char DeviceObject::EPC_STANDARD_VERSION_INFORMATION = 0x82;
const unsigned char DeviceObject::EPC_IDENTIFICATION_NUMBER = 0x83;
const unsigned char DeviceObject::EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION = 0x84;
const unsigned char DeviceObject::EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION = 0x85;
const unsigned char DeviceObject::EPC_MANUFACTURERS_FAULT_CODE = 0x86;
const unsigned char DeviceObject::EPC_CURRENT_LIMIT_SETTING = 0x87;
const unsigned char DeviceObject::EPC_FAULT_STATUS = 0x88;
const unsigned char DeviceObject::EPC_FAULT_DESCRIPTION = 0x89;
const unsigned char DeviceObject::EPC_MANUFACTURER_CODE = 0x8A;
const unsigned char DeviceObject::EPC_BUSINESS_FACILITY_CODE = 0x8B;
const unsigned char DeviceObject::EPC_PRODUCT_CODE =  0x8C;
const unsigned char DeviceObject::EPC_PRODUCTION_NUMBER = 0x8D;
const unsigned char DeviceObject::EPC_PRODUCTION_DATE = 0x8E;
const unsigned char DeviceObject::EPC_POWER_SAVING_OPERATION_SETTING = 0x8F;
const unsigned char DeviceObject::EPC_REMOTE_CONTROL_SETTING = 0x93;
const unsigned char DeviceObject::EPC_CURRENT_TIME_SETTING = 0x97;
const unsigned char DeviceObject::EPC_CURRENT_DATE_SETTING = 0x98;
const unsigned char DeviceObject::EPC_POWER_LIMIT_SETTING = 0x99;
const unsigned char DeviceObject::EPC_CUMULATIVE_OPERATING_TIME = 0x9A;
const unsigned char DeviceObject::EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP = 0x9D;
const unsigned char DeviceObject::EPC_SET_PROPERTY_MAP = 0x9E;
const unsigned char DeviceObject::EPC_GET_PROPERTY_MAP = 0x9F;

DeviceObject::DeviceObject() : EchoObject() {
	//mEchoInstanceCode = Echo::getStorage().get()->allocateSelfDeviceInstanceCode(getEchoClassCode());
	mEchoInstanceCode = 0;

	mStandardVersionInformation = std::shared_ptr<std::vector<unsigned char> > (new std::vector<unsigned char>());
	mStandardVersionInformation.get()->resize(4);
	(*(mStandardVersionInformation.get()))[0] = 0;
	(*(mStandardVersionInformation.get()))[1] = 0;
	(*(mStandardVersionInformation.get()))[2] = 0x43;
	(*(mStandardVersionInformation.get()))[3] = 0;

}

DeviceObject::~DeviceObject() {
	// TODO Auto-generated destructor stub
}

unsigned char DeviceObject::getInstanceCode() {
	return mEchoInstanceCode;
}

void DeviceObject::onNew(std::shared_ptr<EchoObject> eoj) {
	EchoObject::onNew(eoj);
	std::shared_ptr<DeviceObject> device = std::dynamic_pointer_cast<DeviceObject>(eoj);
	Echo::getEventListenerDelegate().onNewDeviceObject(device);
}

bool DeviceObject::setProperty(EchoProperty& property) {

	bool success = EchoObject::setProperty(property);
	if(success) return true;

	switch(property.epc) {
	case EPC_OPERATION_STATUS : return setOperationStatus(property.edt);
	case EPC_INSTALLATION_LOCATION : return setInstallationLocation(property.edt);
	case EPC_CURRENT_LIMIT_SETTING : return setCurrentLimitSetting(property.edt);
	case EPC_POWER_SAVING_OPERATION_SETTING : return setPowerSavingOperationSetting(property.edt);
	case EPC_REMOTE_CONTROL_SETTING : return setRemoteControlSetting(property.edt);
	case EPC_CURRENT_TIME_SETTING : return setCurrentTimeSetting(property.edt);
	case EPC_CURRENT_DATE_SETTING : return setCurrentDateSetting(property.edt);
	case EPC_POWER_LIMIT_SETTING : return setPowerLimitSetting(property.edt);
	default : return false;
	}
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getProperty(
		unsigned char epc) {

	std::shared_ptr<std::vector<unsigned char> > edt = EchoObject::getProperty(epc);
	if(edt.get() != nullptr) return edt;

	switch(epc) {
	case EPC_OPERATION_STATUS : return getOperationStatus();
	case EPC_INSTALLATION_LOCATION : return getInstallationLocation();
	case EPC_STANDARD_VERSION_INFORMATION : return getStandardVersionInformation();
	case EPC_IDENTIFICATION_NUMBER : return getIdentificationNumber();
	case EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION : return getMeasuredInstantaneousPowerConsumption();
	case EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION : return getMeasuredCumulativePowerConsumption();
	case EPC_MANUFACTURERS_FAULT_CODE : return getManufacturersFaultCode();
	case EPC_CURRENT_LIMIT_SETTING : return getCurrentLimitSetting();
	case EPC_FAULT_STATUS : return getFaultStatus();
	case EPC_FAULT_DESCRIPTION :return getFaultDescription();
	case EPC_MANUFACTURER_CODE :return getManufacturerCode();
	case EPC_BUSINESS_FACILITY_CODE : return getBusinessFacilityCode();
	case EPC_PRODUCT_CODE : return getProductCode();
	case EPC_PRODUCTION_NUMBER : return getProductionNumber();
	case EPC_PRODUCTION_DATE : return getProductionDate();
	case EPC_POWER_SAVING_OPERATION_SETTING : return getPowerSavingOperationSetting();
	case EPC_REMOTE_CONTROL_SETTING : return getRemoteControlSetting();
	case EPC_CURRENT_TIME_SETTING : return getCurrentTimeSetting();
	case EPC_CURRENT_DATE_SETTING : return getCurrentDateSetting();
	case EPC_POWER_LIMIT_SETTING : return getPowerLimitSetting();
	case EPC_CUMULATIVE_OPERATING_TIME : return getCumulativeOperatingTime();
	case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP : return getStatusChangeAnnouncementPropertyMap();
	case EPC_SET_PROPERTY_MAP : return getSetPropertyMap();
	case EPC_GET_PROPERTY_MAP : return getGetPropertyMap();
	default : return std::shared_ptr<std::vector<unsigned char> >();
	}
}

bool DeviceObject::isValidProperty(EchoProperty& property) {

	bool valid = EchoObject::isValidProperty(property);
	if(valid) return true;

	switch(property.epc) {
	case EPC_OPERATION_STATUS : return isValidOperationStatus(property.edt);
	case EPC_INSTALLATION_LOCATION : return isValidInstallationLocation(property.edt);
	case EPC_STANDARD_VERSION_INFORMATION : return isValidStandardVersionInformation(property.edt);
	case EPC_IDENTIFICATION_NUMBER : return isValidIdentificationNumber(property.edt);
	case EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION : return isValidMeasuredInstantaneousPowerConsumption(property.edt);
	case EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION : return isValidMeasuredCumulativePowerConsumption(property.edt);
	case EPC_MANUFACTURERS_FAULT_CODE : return isValidManufacturersFaultCode(property.edt);
	case EPC_CURRENT_LIMIT_SETTING : return isValidCurrentLimitSetting(property.edt);
	case EPC_FAULT_STATUS : return isValidFaultStatus(property.edt);
	case EPC_FAULT_DESCRIPTION : return isValidFaultDescription(property.edt);
	case EPC_MANUFACTURER_CODE : return isValidManufacturerCode(property.edt);
	case EPC_BUSINESS_FACILITY_CODE : return isValidBusinessFacilityCode(property.edt);
	case EPC_PRODUCT_CODE :  return isValidProductCode(property.edt);
	case EPC_PRODUCTION_NUMBER : return isValidProductionNumber(property.edt);
	case EPC_PRODUCTION_DATE : return isValidProductionDate(property.edt);
	case EPC_POWER_SAVING_OPERATION_SETTING : return isValidPowerSavingOperationSetting(property.edt);
	case EPC_REMOTE_CONTROL_SETTING : return isValidRemoteControlSetting(property.edt);
	case EPC_CURRENT_TIME_SETTING : return isValidCurrentTimeSetting(property.edt);
	case EPC_CURRENT_DATE_SETTING : return isValidCurrentDateSetting(property.edt);
	case EPC_POWER_LIMIT_SETTING : return isValidPowerLimitSetting(property.edt);
	case EPC_CUMULATIVE_OPERATING_TIME : return isValidCumulativeOperatingTime(property.edt);
	case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP : return isValidStatusChangeAnnouncementPropertyMap(property.edt);
	case EPC_SET_PROPERTY_MAP : return isValidSetPropertyMap(property.edt);
	case EPC_GET_PROPERTY_MAP : return isValidGetPropertyMap(property.edt);
	default : return false;
	}
}

DeviceObject::Setter DeviceObject::set() {

	return DeviceObject::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), true);
}

DeviceObject::Setter DeviceObject::set(bool responseRequired) {
	return DeviceObject::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), responseRequired);
}

DeviceObject::Getter DeviceObject::get() {

	return DeviceObject::Getter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress());
}

DeviceObject::Informer DeviceObject::inform() {

	std::string address;
	if(isProxy()) {
		address = getNode().get()->getAddress();
	} else {
		address = EchoSocket::MULTICAST_ADDRESS;
	}
	return DeviceObject::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

DeviceObject::Informer DeviceObject::inform(bool multicast) {

	std::string address;
	if(multicast) {
		address = EchoSocket::MULTICAST_ADDRESS;
	} else {
		address = getNode().get()->getAddress();
	}
	return DeviceObject::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

DeviceObject::InformerC DeviceObject::informC(std::string address) {
	return DeviceObject::InformerC(getEchoClassCode(), getInstanceCode()
			, address);
}

void DeviceObject::allocateSelfDeviceInstanceCode() {
	mEchoInstanceCode = EchoUtils::allocateSelfDeviceInstanceCode(getEchoClassCode());
}

void DeviceObject::setupPropertyMaps() {

	EchoObject::setupPropertyMaps();

	addStatusChangeAnnouncementProperty(EPC_OPERATION_STATUS);
	addStatusChangeAnnouncementProperty(EPC_INSTALLATION_LOCATION);
	addStatusChangeAnnouncementProperty(EPC_FAULT_STATUS);

	addSetProperty(EPC_INSTALLATION_LOCATION);

	addGetProperty(EPC_OPERATION_STATUS);
	addGetProperty(EPC_INSTALLATION_LOCATION);
	addGetProperty(EPC_STANDARD_VERSION_INFORMATION);
	addGetProperty(EPC_FAULT_STATUS);
	addGetProperty(EPC_MANUFACTURER_CODE);
	addGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
	addGetProperty(EPC_SET_PROPERTY_MAP);
	addGetProperty(EPC_GET_PROPERTY_MAP);
}

DeviceObject::Receiver::Receiver() : EchoObject::Receiver()  {
}

DeviceObject::Receiver::~Receiver() {
}

bool DeviceObject::Receiver::onSetProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
	bool ret = EchoObject::Receiver::onSetProperty(eoj, tid, esv, property, success);
	if(ret) return true;

	switch(property.epc) {
	case EPC_OPERATION_STATUS :
		onSetOperationStatus(eoj, tid, esv, property, success);
		return true;
	case EPC_INSTALLATION_LOCATION :
		onSetInstallationLocation(eoj, tid, esv, property, success);
		return true;
	case EPC_CURRENT_LIMIT_SETTING :
		onSetCurrentLimitSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_POWER_SAVING_OPERATION_SETTING :
		onSetPowerSavingOperationSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_REMOTE_CONTROL_SETTING :
		onSetRemoteControlSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_CURRENT_TIME_SETTING :
		onSetCurrentTimeSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_CURRENT_DATE_SETTING :
		onSetCurrentDateSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_POWER_LIMIT_SETTING :
		onSetPowerLimitSetting(eoj, tid, esv, property, success);
		return true;
	default :
		return false;
	}}

bool DeviceObject::Receiver::onGetProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {

	bool ret = EchoObject::Receiver::onGetProperty(eoj, tid, esv, property, success);
	if(ret) return true;
	switch(property.epc) {
	case EPC_OPERATION_STATUS :
		onGetOperationStatus(eoj, tid, esv, property, success);
		return true;
	case EPC_INSTALLATION_LOCATION :
		onGetInstallationLocation(eoj, tid, esv, property, success);
		return true;
	case EPC_STANDARD_VERSION_INFORMATION :
		onGetStandardVersionInformation(eoj, tid, esv, property, success);
		return true;
	case EPC_IDENTIFICATION_NUMBER :
		onGetIdentificationNumber(eoj, tid, esv, property, success);
		return true;
	case EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION :
		onGetMeasuredInstantaneousPowerConsumption(eoj, tid, esv, property, success);
		return true;
	case EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION :
		onGetMeasuredCumulativePowerConsumption(eoj, tid, esv, property, success);
		return true;
	case EPC_MANUFACTURERS_FAULT_CODE :
		onGetManufacturersFaultCode(eoj, tid, esv, property, success);
		return true;
	case EPC_CURRENT_LIMIT_SETTING :
		onGetCurrentLimitSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_FAULT_STATUS :
		onGetFaultStatus(eoj, tid, esv, property, success);
		return true;
	case EPC_FAULT_DESCRIPTION :
		onGetFaultDescription(eoj, tid, esv, property, success);
		return true;
	case EPC_MANUFACTURER_CODE :
		onGetManufacturerCode(eoj, tid, esv, property, success);
		return true;
	case EPC_BUSINESS_FACILITY_CODE :
		onGetBusinessFacilityCode(eoj, tid, esv, property, success);
		return true;
	case EPC_PRODUCT_CODE :
		onGetProductCode(eoj, tid, esv, property, success);
		return true;
	case EPC_PRODUCTION_NUMBER :
		onGetProductionNumber(eoj, tid, esv, property, success);
		return true;
	case EPC_PRODUCTION_DATE :
		onGetProductionDate(eoj, tid, esv, property, success);
		return true;
	case EPC_POWER_SAVING_OPERATION_SETTING :
		onGetPowerSavingOperationSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_REMOTE_CONTROL_SETTING :
		onGetRemoteControlSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_CURRENT_TIME_SETTING :
		onGetCurrentTimeSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_CURRENT_DATE_SETTING :
		onGetCurrentDateSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_POWER_LIMIT_SETTING :
		onGetPowerLimitSetting(eoj, tid, esv, property, success);
		return true;
	case EPC_CUMULATIVE_OPERATING_TIME :
		onGetCumulativeOperatingTime(eoj, tid, esv, property, success);
		return true;
	case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP :
		onGetStatusChangeAnnouncementPropertyMap(eoj, tid, esv, property, success);
		return true;
	case EPC_SET_PROPERTY_MAP :
		onGetSetPropertyMap(eoj, tid, esv, property, success);
		return true;
	case EPC_GET_PROPERTY_MAP :
		onGetGetPropertyMap(eoj, tid, esv, property, success);
		return true;
	default :
		return false;
	}
}

bool DeviceObject::Receiver::onInformProperty(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property) {
	bool ret = EchoObject::Receiver::onInformProperty(eoj, tid, esv, property);
	if(ret) return true;
	return false;
}

DeviceObject::Setter::Setter(unsigned short dstEchoClassCode,
		unsigned char dstEchoInstanceCode, std::string dstEchoAddress,
		bool responseRequired)
	: EchoObject::Setter(dstEchoClassCode
	, dstEchoInstanceCode ,dstEchoAddress, responseRequired) {
}

DeviceObject::Setter::~Setter() {
}

DeviceObject::Setter& DeviceObject::Setter::reqSetProperty(unsigned char epc,
		std::vector<unsigned char> edt) {
	return dynamic_cast<DeviceObject::Setter&>(EchoObject::Setter::reqSetProperty(epc, edt));
}

DeviceObject::Getter::Getter(unsigned short dstEchoClassCode,
		unsigned char dstEchoInstanceCode, std::string dstEchoAddress)
	: EchoObject::Getter(dstEchoClassCode
	, dstEchoInstanceCode, dstEchoAddress) {
}

DeviceObject::Getter::~Getter() {
}

DeviceObject::Getter& DeviceObject::Getter::reqGetProperty(unsigned char epc) {
	return dynamic_cast<DeviceObject::Getter&>(EchoObject::Getter::reqGetProperty(epc));
}

DeviceObject::Informer::Informer(unsigned short echoClassCode,
		unsigned char echoInstanceCode, std::string dstEchoAddress,
		bool isSelfObject)
	: EchoObject::Informer(echoClassCode, echoInstanceCode
	, dstEchoAddress, isSelfObject) {
}

DeviceObject::Informer::~Informer() {
}

DeviceObject::Informer& DeviceObject::Informer::reqInformProperty(
		unsigned char epc) {
	return dynamic_cast<DeviceObject::Informer&>(EchoObject::Informer::reqInformProperty(epc));
}

DeviceObject::InformerC::InformerC(unsigned short srcEchoClassCode,
		unsigned char srcEchoInstanceCode, std::string dstEchoAddress)
	: EchoObject::InformerC(srcEchoClassCode
	, srcEchoInstanceCode, dstEchoAddress) {
}

DeviceObject::InformerC::~InformerC() {
}

DeviceObject::InformerC& DeviceObject::InformerC::reqInformProperty(
		unsigned char epc) {
	return dynamic_cast<DeviceObject::InformerC&>(EchoObject::InformerC::reqInformProperty(epc));
}

DeviceObject::Proxy::Proxy(unsigned short echoClassCode,
		unsigned char echoInstanceCode) : DeviceObject() {
	mEchoClassCode = echoClassCode;
	mEchoInstanceCode = echoInstanceCode;
}

DeviceObject::Proxy::~Proxy() {
}

unsigned char DeviceObject::Proxy::getInstanceCode() {
	return mEchoInstanceCode;
}

unsigned short DeviceObject::Proxy::getEchoClassCode() {
	return mEchoClassCode;
}

bool DeviceObject::setOperationStatus(std::vector<unsigned char>& edt) {
	return false;
}

bool DeviceObject::isValidOperationStatus(std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

bool DeviceObject::isValidInstallationLocation(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 1 && edt.size() != 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getStandardVersionInformation() {
	return mStandardVersionInformation;
}

bool DeviceObject::isValidStandardVersionInformation(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 4) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getIdentificationNumber() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidIdentificationNumber(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 9 && edt.size() != 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getMeasuredInstantaneousPowerConsumption() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidMeasuredInstantaneousPowerConsumption(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getMeasuredCumulativePowerConsumption() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidMeasuredCumulativePowerConsumption(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 4) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getManufacturersFaultCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidManufacturersFaultCode(
		std::vector<unsigned char>& edt) {
	if(edt.size() > 225) return false;
	return true;
}

bool DeviceObject::setCurrentLimitSetting(std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getCurrentLimitSetting() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidCurrentLimitSetting(std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

bool DeviceObject::isValidFaultStatus(std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getFaultDescription() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidFaultDescription(std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

bool DeviceObject::isValidManufacturerCode(std::vector<unsigned char>& edt) {
	if(edt.size() != 3) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getBusinessFacilityCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidBusinessFacilityCode(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 3) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getProductCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidProductCode(std::vector<unsigned char>& edt) {
	if(edt.size() != 12) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getProductionNumber() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidProductionNumber(std::vector<unsigned char>& edt) {
	if(edt.size() != 12) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getProductionDate() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidProductionDate(std::vector<unsigned char>& edt) {
	if(edt.size() != 4) return false;
	return true;
}

bool DeviceObject::setPowerSavingOperationSetting(
		std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getPowerSavingOperationSetting() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidPowerSavingOperationSetting(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

bool DeviceObject::setRemoteControlSetting(std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getRemoteControlSetting() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidRemoteControlSetting(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 1) return false;
	return true;
}

bool DeviceObject::setCurrentTimeSetting(std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getCurrentTimeSetting() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidCurrentTimeSetting(std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

bool DeviceObject::setCurrentDateSetting(std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getCurrentDateSetting() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidCurrentDateSetting(std::vector<unsigned char>& edt) {
	if(edt.size() != 4) return false;
	return true;
}

bool DeviceObject::setPowerLimitSetting(std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getPowerLimitSetting() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidPowerLimitSetting(std::vector<unsigned char>& edt) {
	if(edt.size() != 2) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getCumulativeOperatingTime() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::isValidCumulativeOperatingTime(
		std::vector<unsigned char>& edt) {
	if(edt.size() != 5) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getStatusChangeAnnouncementPropertyMap() {
	return EchoUtils::convertPropertiesToPropertyMap(getStatusChangeAnnouncementProperties());
}

bool DeviceObject::isValidStatusChangeAnnouncementPropertyMap(
		std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getSetPropertyMap() {
	return EchoUtils::convertPropertiesToPropertyMap(getSetProperties());
}

bool DeviceObject::isValidSetPropertyMap(std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::getGetPropertyMap() {
	return EchoUtils::convertPropertiesToPropertyMap(getGetProperties());
}

bool DeviceObject::isValidGetPropertyMap(std::vector<unsigned char>& edt) {
	if(edt.size() > 17) return false;
	return true;
}

void DeviceObject::Receiver::onSetOperationStatus(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetInstallationLocation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetCurrentLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetPowerSavingOperationSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetRemoteControlSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetCurrentTimeSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetCurrentDateSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onSetPowerLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetOperationStatus(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetInstallationLocation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetStandardVersionInformation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetIdentificationNumber(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetMeasuredInstantaneousPowerConsumption(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetMeasuredCumulativePowerConsumption(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetManufacturersFaultCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetCurrentLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetFaultStatus(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
}

void DeviceObject::Receiver::onGetFaultDescription(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetManufacturerCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetBusinessFacilityCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetProductCode(std::shared_ptr<EchoObject> eoj,
		unsigned short tid, unsigned char esv, EchoProperty& property,
		bool success) {
}

void DeviceObject::Receiver::onGetProductionNumber(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetProductionDate(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetPowerSavingOperationSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetRemoteControlSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetCurrentTimeSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetCurrentDateSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetPowerLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetCumulativeOperatingTime(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetStatusChangeAnnouncementPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetSetPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

void DeviceObject::Receiver::onGetGetPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty& property, bool success) {
}

DeviceObject::Setter& DeviceObject::Setter::reqSetOperationStatus(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_OPERATION_STATUS, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetInstallationLocation(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_INSTALLATION_LOCATION, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetCurrentLimitSetting(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_CURRENT_LIMIT_SETTING, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetPowerSavingOperationSetting(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_POWER_SAVING_OPERATION_SETTING, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetRemoteControlSetting(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_REMOTE_CONTROL_SETTING, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetCurrentTimeSetting(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_CURRENT_TIME_SETTING, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetCurrentDateSetting(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_CURRENT_DATE_SETTING, edt);
}

DeviceObject::Setter& DeviceObject::Setter::reqSetPowerLimitSetting(
		std::vector<unsigned char> edt) {
	return reqSetProperty(EPC_POWER_LIMIT_SETTING, edt);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetOperationStatus() {
	return reqGetProperty(EPC_OPERATION_STATUS);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetInstallationLocation() {
	return reqGetProperty(EPC_INSTALLATION_LOCATION);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetStandardVersionInformation() {
	return reqGetProperty(EPC_STANDARD_VERSION_INFORMATION);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetIdentificationNumber() {
	return reqGetProperty(EPC_IDENTIFICATION_NUMBER);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetMeasuredInstantaneousPowerConsumption() {
	return reqGetProperty(EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetMeasuredCumulativePowerConsumption() {
	return reqGetProperty(EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetManufacturersFaultCode() {
	return reqGetProperty(EPC_MANUFACTURERS_FAULT_CODE);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetCurrentLimitSetting() {
	return reqGetProperty(EPC_CURRENT_LIMIT_SETTING);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetFaultStatus() {
	return reqGetProperty(EPC_FAULT_STATUS);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetFaultDescription() {
	return reqGetProperty(EPC_FAULT_DESCRIPTION);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetManufacturerCode() {
	return reqGetProperty(EPC_MANUFACTURER_CODE);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetBusinessFacilityCode() {
	return reqGetProperty(EPC_BUSINESS_FACILITY_CODE);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetProductCode() {
	return reqGetProperty(EPC_PRODUCT_CODE);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetProductionNumber() {
	return reqGetProperty(EPC_PRODUCTION_NUMBER);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetProductionDate() {
	return reqGetProperty(EPC_PRODUCTION_DATE);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetPowerSavingOperationSetting() {
	return reqGetProperty(EPC_POWER_SAVING_OPERATION_SETTING);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetRemoteControlSetting() {
	return reqGetProperty(EPC_REMOTE_CONTROL_SETTING);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetCurrentTimeSetting() {
	return reqGetProperty(EPC_CURRENT_TIME_SETTING);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetCurrentDateSetting() {
	return reqGetProperty(EPC_CURRENT_DATE_SETTING);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetPowerLimitSetting() {
	return reqGetProperty(EPC_POWER_LIMIT_SETTING);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetCumulativeOperatingTime() {
	return reqGetProperty(EPC_CUMULATIVE_OPERATING_TIME);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetStatusChangeAnnouncementPropertyMap() {
	return reqGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetSetPropertyMap() {
	return reqGetProperty(EPC_SET_PROPERTY_MAP);
}

DeviceObject::Getter& DeviceObject::Getter::reqGetGetPropertyMap() {
	return reqGetProperty(EPC_GET_PROPERTY_MAP);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformOperationStatus() {
	return reqInformProperty(EPC_OPERATION_STATUS);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformInstallationLocation() {
	return reqInformProperty(EPC_INSTALLATION_LOCATION);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformStandardVersionInformation() {
	return reqInformProperty(EPC_STANDARD_VERSION_INFORMATION);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformIdentificationNumber() {
	return reqInformProperty(EPC_IDENTIFICATION_NUMBER);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformMeasuredInstantaneousPowerConsumption() {
	return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformMeasuredCumulativePowerConsumption() {
	return reqInformProperty(EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformManufacturersFaultCode() {
	return reqInformProperty(EPC_MANUFACTURERS_FAULT_CODE);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformCurrentLimitSetting() {
	return reqInformProperty(EPC_CURRENT_LIMIT_SETTING);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformFaultStatus() {
	return reqInformProperty(EPC_FAULT_STATUS);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformFaultDescription() {
	return reqInformProperty(EPC_FAULT_DESCRIPTION);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformManufacturerCode() {
	return reqInformProperty(EPC_MANUFACTURER_CODE);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformBusinessFacilityCode() {
	return reqInformProperty(EPC_BUSINESS_FACILITY_CODE);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformProductCode() {
	return reqInformProperty(EPC_PRODUCT_CODE);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformProductionNumber() {
	return reqInformProperty(EPC_PRODUCTION_NUMBER);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformProductionDate() {
	return reqInformProperty(EPC_PRODUCTION_DATE);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformPowerSavingOperationSetting() {
	return reqInformProperty(EPC_POWER_SAVING_OPERATION_SETTING);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformRemoteControlSetting() {
	return reqInformProperty(EPC_REMOTE_CONTROL_SETTING);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformCurrentTimeSetting() {
	return reqInformProperty(EPC_CURRENT_TIME_SETTING);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformCurrentDateSetting() {
	return reqInformProperty(EPC_CURRENT_DATE_SETTING);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformPowerLimitSetting() {
	return reqInformProperty(EPC_POWER_LIMIT_SETTING);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformCumulativeOperatingTime() {
	return reqInformProperty(EPC_CUMULATIVE_OPERATING_TIME);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformStatusChangeAnnouncementPropertyMap() {
	return reqInformProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformSetPropertyMap() {
	return reqInformProperty(EPC_SET_PROPERTY_MAP);
}

DeviceObject::Informer& DeviceObject::Informer::reqInformGetPropertyMap() {
	return reqInformProperty(EPC_GET_PROPERTY_MAP);
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::Proxy::getOperationStatus() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool DeviceObject::Proxy::setInstallationLocation(
		std::vector<unsigned char>& edt) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::Proxy::getInstallationLocation() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::Proxy::getFaultStatus() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

std::shared_ptr<std::vector<unsigned char> > DeviceObject::Proxy::getManufacturerCode() {
	return std::shared_ptr<std::vector<unsigned char> >();
}

};
