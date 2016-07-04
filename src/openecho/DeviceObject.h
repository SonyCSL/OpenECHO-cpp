/*
 * DeviceObject.h
 *
 *  Created on: 2013/10/29
 *      Author: Fumiaki
 */

#ifndef DEVICEOBJECT_H_
#define DEVICEOBJECT_H_

#include "EchoObject.h"

namespace sonycsl_openecho {

class DeviceObject: public EchoObject {
public:
	class Receiver;
	class Setter;
	class Getter;
	class Informer;
	class InformerC;
	class Proxy;
public:
	static const unsigned char EPC_OPERATION_STATUS;
	static const unsigned char EPC_INSTALLATION_LOCATION;
	static const unsigned char EPC_STANDARD_VERSION_INFORMATION;
	static const unsigned char EPC_IDENTIFICATION_NUMBER;
	static const unsigned char EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION;
	static const unsigned char EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION;
	static const unsigned char EPC_MANUFACTURERS_FAULT_CODE;
	static const unsigned char EPC_CURRENT_LIMIT_SETTING;
	static const unsigned char EPC_FAULT_STATUS;
	static const unsigned char EPC_FAULT_DESCRIPTION;
	static const unsigned char EPC_MANUFACTURER_CODE;
	static const unsigned char EPC_BUSINESS_FACILITY_CODE;
	static const unsigned char EPC_PRODUCT_CODE;
	static const unsigned char EPC_PRODUCTION_NUMBER;
	static const unsigned char EPC_PRODUCTION_DATE;
	static const unsigned char EPC_POWER_SAVING_OPERATION_SETTING;
	static const unsigned char EPC_REMOTE_CONTROL_SETTING;
	static const unsigned char EPC_CURRENT_TIME_SETTING;
	static const unsigned char EPC_CURRENT_DATE_SETTING;
	static const unsigned char EPC_POWER_LIMIT_SETTING;
	static const unsigned char EPC_CUMULATIVE_OPERATING_TIME;
	static const unsigned char EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP;
	static const unsigned char EPC_SET_PROPERTY_MAP;
	static const unsigned char EPC_GET_PROPERTY_MAP;

protected:
	unsigned char mEchoInstanceCode;
	std::shared_ptr<std::vector<unsigned char> > mStandardVersionInformation;
public:
	DeviceObject();
	virtual ~DeviceObject();

public:
	virtual unsigned char getInstanceCode();

	virtual void onNew(std::shared_ptr<EchoObject> eoj);

	virtual void allocateSelfDeviceInstanceCode();

	virtual bool setProperty(EchoProperty& property);
	virtual std::shared_ptr<std::vector<unsigned char> > getProperty(unsigned char epc);
	virtual bool isValidProperty(EchoProperty& property);

	DeviceObject::Setter set();
	DeviceObject::Setter set(bool responseRequired);
	DeviceObject::Getter get();
	DeviceObject::Informer inform();

protected:
	DeviceObject::Informer inform(bool multicast);
	DeviceObject::InformerC informC(std::string address);

	virtual void setupPropertyMaps();

	virtual bool setOperationStatus(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getOperationStatus() = 0;
	virtual bool isValidOperationStatus(std::vector<unsigned char>& edt);
	virtual bool setInstallationLocation(std::vector<unsigned char>& edt) = 0;
	virtual std::shared_ptr<std::vector<unsigned char> > getInstallationLocation() = 0;
	virtual bool isValidInstallationLocation(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getStandardVersionInformation();
	virtual bool isValidStandardVersionInformation(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getIdentificationNumber();
	virtual bool isValidIdentificationNumber(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getMeasuredInstantaneousPowerConsumption();
	virtual bool isValidMeasuredInstantaneousPowerConsumption(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getMeasuredCumulativePowerConsumption();
	virtual bool isValidMeasuredCumulativePowerConsumption(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturersFaultCode();
	virtual bool isValidManufacturersFaultCode(std::vector<unsigned char>& edt);
	virtual bool setCurrentLimitSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getCurrentLimitSetting();
	virtual bool isValidCurrentLimitSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getFaultStatus() = 0;
	virtual bool isValidFaultStatus(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getFaultDescription();
	virtual bool isValidFaultDescription(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturerCode() = 0;
	virtual bool isValidManufacturerCode(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getBusinessFacilityCode();
	virtual bool isValidBusinessFacilityCode(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getProductCode();
	virtual bool isValidProductCode(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getProductionNumber();
	virtual bool isValidProductionNumber(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getProductionDate();
	virtual bool isValidProductionDate(std::vector<unsigned char>& edt);
	virtual bool setPowerSavingOperationSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getPowerSavingOperationSetting();
	virtual bool isValidPowerSavingOperationSetting(std::vector<unsigned char>& edt);
	virtual bool setRemoteControlSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getRemoteControlSetting();
	virtual bool isValidRemoteControlSetting(std::vector<unsigned char>& edt);
	virtual bool setCurrentTimeSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getCurrentTimeSetting();
	virtual bool isValidCurrentTimeSetting(std::vector<unsigned char>& edt);
	virtual bool setCurrentDateSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getCurrentDateSetting();
	virtual bool isValidCurrentDateSetting(std::vector<unsigned char>& edt);
	virtual bool setPowerLimitSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getPowerLimitSetting();
	virtual bool isValidPowerLimitSetting(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getCumulativeOperatingTime();
	virtual bool isValidCumulativeOperatingTime(std::vector<unsigned char>& edt);
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

		virtual void onSetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetInstallationLocation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetCurrentLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetPowerSavingOperationSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetRemoteControlSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetCurrentTimeSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetCurrentDateSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onSetPowerLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);

		virtual void onGetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetInstallationLocation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetStandardVersionInformation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetIdentificationNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetMeasuredInstantaneousPowerConsumption(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetMeasuredCumulativePowerConsumption(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetManufacturersFaultCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetCurrentLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetFaultStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetFaultDescription(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetManufacturerCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetBusinessFacilityCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetProductCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetProductionNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetProductionDate(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetPowerSavingOperationSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetRemoteControlSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetCurrentTimeSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetCurrentDateSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetPowerLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetCumulativeOperatingTime(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetStatusChangeAnnouncementPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetSetPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual void onGetGetPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);

	};

	class Setter : public EchoObject::Setter {
	public:
		Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress, bool responseRequired);
		virtual ~Setter();
		virtual DeviceObject::Setter& reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);

		virtual DeviceObject::Setter& reqSetOperationStatus(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetInstallationLocation(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetCurrentLimitSetting(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetPowerSavingOperationSetting(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetRemoteControlSetting(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetCurrentTimeSetting(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetCurrentDateSetting(std::vector<unsigned char> edt);
		virtual DeviceObject::Setter& reqSetPowerLimitSetting(std::vector<unsigned char> edt);

	};

	class Getter : public EchoObject::Getter {
	public:
		Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~Getter();
		virtual DeviceObject::Getter& reqGetProperty(unsigned char epc);

		virtual DeviceObject::Getter& reqGetOperationStatus();
		virtual DeviceObject::Getter& reqGetInstallationLocation();
		virtual DeviceObject::Getter& reqGetStandardVersionInformation();
		virtual DeviceObject::Getter& reqGetIdentificationNumber();
		virtual DeviceObject::Getter& reqGetMeasuredInstantaneousPowerConsumption();
		virtual DeviceObject::Getter& reqGetMeasuredCumulativePowerConsumption();
		virtual DeviceObject::Getter& reqGetManufacturersFaultCode();
		virtual DeviceObject::Getter& reqGetCurrentLimitSetting();
		virtual DeviceObject::Getter& reqGetFaultStatus();
		virtual DeviceObject::Getter& reqGetFaultDescription();
		virtual DeviceObject::Getter& reqGetManufacturerCode();
		virtual DeviceObject::Getter& reqGetBusinessFacilityCode();
		virtual DeviceObject::Getter& reqGetProductCode();
		virtual DeviceObject::Getter& reqGetProductionNumber();
		virtual DeviceObject::Getter& reqGetProductionDate();
		virtual DeviceObject::Getter& reqGetPowerSavingOperationSetting();
		virtual DeviceObject::Getter& reqGetRemoteControlSetting();
		virtual DeviceObject::Getter& reqGetCurrentTimeSetting();
		virtual DeviceObject::Getter& reqGetCurrentDateSetting();
		virtual DeviceObject::Getter& reqGetPowerLimitSetting();
		virtual DeviceObject::Getter& reqGetCumulativeOperatingTime();
		virtual DeviceObject::Getter& reqGetStatusChangeAnnouncementPropertyMap();
		virtual DeviceObject::Getter& reqGetSetPropertyMap();
		virtual DeviceObject::Getter& reqGetGetPropertyMap();
	};

	class Informer : public EchoObject::Informer {
	public:
		Informer(unsigned short echoClassCode, unsigned char echoInstanceCode
				, std::string dstEchoAddress, bool isSelfObject);
		virtual ~Informer();
		virtual DeviceObject::Informer& reqInformProperty(unsigned char epc);

		virtual DeviceObject::Informer& reqInformOperationStatus();
		virtual DeviceObject::Informer& reqInformInstallationLocation();
		virtual DeviceObject::Informer& reqInformStandardVersionInformation();
		virtual DeviceObject::Informer& reqInformIdentificationNumber();
		virtual DeviceObject::Informer& reqInformMeasuredInstantaneousPowerConsumption();
		virtual DeviceObject::Informer& reqInformMeasuredCumulativePowerConsumption();
		virtual DeviceObject::Informer& reqInformManufacturersFaultCode();
		virtual DeviceObject::Informer& reqInformCurrentLimitSetting();
		virtual DeviceObject::Informer& reqInformFaultStatus();
		virtual DeviceObject::Informer& reqInformFaultDescription();
		virtual DeviceObject::Informer& reqInformManufacturerCode();
		virtual DeviceObject::Informer& reqInformBusinessFacilityCode();
		virtual DeviceObject::Informer& reqInformProductCode();
		virtual DeviceObject::Informer& reqInformProductionNumber();
		virtual DeviceObject::Informer& reqInformProductionDate();
		virtual DeviceObject::Informer& reqInformPowerSavingOperationSetting();
		virtual DeviceObject::Informer& reqInformRemoteControlSetting();
		virtual DeviceObject::Informer& reqInformCurrentTimeSetting();
		virtual DeviceObject::Informer& reqInformCurrentDateSetting();
		virtual DeviceObject::Informer& reqInformPowerLimitSetting();
		virtual DeviceObject::Informer& reqInformCumulativeOperatingTime();
		virtual DeviceObject::Informer& reqInformStatusChangeAnnouncementPropertyMap();
		virtual DeviceObject::Informer& reqInformSetPropertyMap();
		virtual DeviceObject::Informer& reqInformGetPropertyMap();

	};

	class InformerC : public EchoObject::InformerC {
	public:
		InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~InformerC();
		virtual DeviceObject::InformerC& reqInformProperty(unsigned char epc);
	};

};

class DeviceObject::Proxy : public DeviceObject {
protected:
	unsigned short mEchoClassCode;
public:
	Proxy(unsigned short echoClassCode, unsigned char echoInstanceCode);
	virtual ~Proxy();

	virtual unsigned char getInstanceCode();
	virtual unsigned short getEchoClassCode();

	virtual std::shared_ptr<std::vector<unsigned char> > getOperationStatus();
	virtual bool setInstallationLocation(std::vector<unsigned char>& edt);
	virtual std::shared_ptr<std::vector<unsigned char> > getInstallationLocation();
	virtual std::shared_ptr<std::vector<unsigned char> > getFaultStatus();
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturerCode();
};

};

#endif /* DEVICEOBJECT_H_ */
