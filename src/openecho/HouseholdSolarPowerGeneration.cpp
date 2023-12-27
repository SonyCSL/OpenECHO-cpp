#include <iostream>
#include "OpenECHO.h"

namespace sonycsl_openecho
{
    static const short ECHO_CLASS_CODE = 0x0279;
    const unsigned char HouseholdSolarPowerGeneration::EPC_OPERATION_STATUS = 0x80;
    const unsigned char HouseholdSolarPowerGeneration::EPC_INSTALLATION_LOCATION = 0x81;
    const unsigned char HouseholdSolarPowerGeneration::EPC_STANDARD_VERSION_INFORMATION = 0x82;
    const unsigned char HouseholdSolarPowerGeneration::EPC_IDENTIFICATION_NUMBER = 0x83;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION = 0x84;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION = 0x85;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MANUFACTURERS_FAULT_CODE = 0x86;
    const unsigned char HouseholdSolarPowerGeneration::EPC_CURRENT_LIMIT_SETTING = 0x87;
    const unsigned char HouseholdSolarPowerGeneration::EPC_FAULT_STATUS = 0x88;
    const unsigned char HouseholdSolarPowerGeneration::EPC_FAULT_DESCRIPTION = 0x89;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MANUFACTURER_CODE = 0x8A;
    const unsigned char HouseholdSolarPowerGeneration::EPC_BUSINESS_FACILITY_CODE = 0x8B;
    const unsigned char HouseholdSolarPowerGeneration::EPC_PRODUCT_CODE = 0x8C;
    const unsigned char HouseholdSolarPowerGeneration::EPC_PRODUCTION_NUMBER = 0x8D;
    const unsigned char HouseholdSolarPowerGeneration::EPC_PRODUCTION_DATE = 0x8E;
    const unsigned char HouseholdSolarPowerGeneration::EPC_POWER_SAVING_OPERATION_SETTING = 0x8F;
    const unsigned char HouseholdSolarPowerGeneration::EPC_REMOTE_CONTROL_SETTING = 0x93;
    const unsigned char HouseholdSolarPowerGeneration::EPC_CURRENT_TIME_SETTING = 0x97;
    const unsigned char HouseholdSolarPowerGeneration::EPC_CURRENT_DATE_SETTING = 0x98;
    const unsigned char HouseholdSolarPowerGeneration::EPC_POWER_LIMIT_SETTING = 0x99;
    const unsigned char HouseholdSolarPowerGeneration::EPC_CUMULATIVE_OPERATING_TIME = 0x9A;
    const unsigned char HouseholdSolarPowerGeneration::EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP = 0x9D;
    const unsigned char HouseholdSolarPowerGeneration::EPC_SET_PROPERTY_MAP = 0x9E;
    const unsigned char HouseholdSolarPowerGeneration::EPC_GET_PROPERTY_MAP = 0x9F;
    const unsigned char HouseholdSolarPowerGeneration::EPC_SYSTEM_INTERCONNECTION_INFORMATION = 0xD0;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION = 0xE0;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION = 0xE1;
    const unsigned char HouseholdSolarPowerGeneration::EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION = 0xE2;
    const unsigned char HouseholdSolarPowerGeneration::EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD = 0xE3;
    const unsigned char HouseholdSolarPowerGeneration::EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD = 0xE4;
    const unsigned char HouseholdSolarPowerGeneration::EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1 = 0xE5;
    const unsigned char HouseholdSolarPowerGeneration::EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2 = 0xE6;
    const unsigned char HouseholdSolarPowerGeneration::EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD = 0xE7;
    const unsigned char HouseholdSolarPowerGeneration::EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED = 0xE8;
    const unsigned char HouseholdSolarPowerGeneration::EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT = 0xE9;

    HouseholdSolarPowerGeneration::HouseholdSolarPowerGeneration() : EchoObject()
    {
        mEchoInstanceCode = 0;

        mStandardVersionInformation = std::shared_ptr<std::vector<unsigned char>>(new std::vector<unsigned char>());
        mStandardVersionInformation.get()->resize(4);
        (*(mStandardVersionInformation.get()))[0] = 0;
        (*(mStandardVersionInformation.get()))[1] = 0;
        (*(mStandardVersionInformation.get()))[2] = 0x43;
        (*(mStandardVersionInformation.get()))[3] = 0;
    }
    HouseholdSolarPowerGeneration::~HouseholdSolarPowerGeneration()
    {
        // TODO Auto-generated destructor stub
    }
    unsigned char HouseholdSolarPowerGeneration::getInstanceCode()
    {
        return mEchoInstanceCode;
    }
    void HouseholdSolarPowerGeneration::onNew(std::shared_ptr<EchoObject> eoj)
    {
        EchoObject::onNew(eoj);
        std::shared_ptr<HouseholdSolarPowerGeneration> device = std::dynamic_pointer_cast<HouseholdSolarPowerGeneration>(eoj);
        Echo::getEventListenerDelegate().onNewHouseholdSolarPowerGeneration(device);
    }
    bool HouseholdSolarPowerGeneration::setProperty(EchoProperty &property)
    {
        bool success = EchoObject::setProperty(property);
        if (success)
            return true;

        switch (property.epc)
        {
        case EPC_OPERATION_STATUS:
            return setOperationStatus(property.edt);
        case EPC_INSTALLATION_LOCATION:
            return setInstallationLocation(property.edt);
        case EPC_CURRENT_LIMIT_SETTING:
            return setCurrentLimitSetting(property.edt);
        case EPC_POWER_SAVING_OPERATION_SETTING:
            return setPowerSavingOperationSetting(property.edt);
        case EPC_REMOTE_CONTROL_SETTING:
            return setRemoteControlSetting(property.edt);
        case EPC_CURRENT_TIME_SETTING:
            return setCurrentTimeSetting(property.edt);
        case EPC_CURRENT_DATE_SETTING:
            return setCurrentDateSetting(property.edt);
        case EPC_POWER_LIMIT_SETTING:
            return setPowerLimitSetting(property.edt);

        case EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            return setResettingCumulativeAmountOfElectricityGenerated(property.edt);
        case EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD:
            return setResettingCumulativeAmountOfElectricitySold(property.edt);
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1:
            return setPowerGenerationOutputLimitSetting1(property.edt);
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2:
            return setPowerGenerationOutputLimitSetting2(property.edt);
        case EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD:
            return setLimitSettingForTheAmountOfElectricitySold(property.edt);
        case EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED:
            return setRatedPowerGenerationOutputSystemInterconnected(property.edt);
        case EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT:
            return setRatedPowerGenerationOutputIndependent(property.edt);
        default:
            return false;
        }
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getProperty(
        unsigned char epc)
    {

        std::shared_ptr<std::vector<unsigned char>> edt = EchoObject::getProperty(epc);
        if (edt.get() != nullptr)
            return edt;

        switch (epc)
        {
        case EPC_OPERATION_STATUS:
            return getOperationStatus();
        case EPC_INSTALLATION_LOCATION:
            return getInstallationLocation();
        case EPC_STANDARD_VERSION_INFORMATION:
            return getStandardVersionInformation();
        case EPC_IDENTIFICATION_NUMBER:
            return getIdentificationNumber();
        case EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION:
            return getMeasuredInstantaneousPowerConsumption();
        case EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION:
            return getMeasuredCumulativePowerConsumption();
        case EPC_MANUFACTURERS_FAULT_CODE:
            return getManufacturersFaultCode();
        case EPC_CURRENT_LIMIT_SETTING:
            return getCurrentLimitSetting();
        case EPC_FAULT_STATUS:
            return getFaultStatus();
        case EPC_FAULT_DESCRIPTION:
            return getFaultDescription();
        case EPC_MANUFACTURER_CODE:
            return getManufacturerCode();
        case EPC_BUSINESS_FACILITY_CODE:
            return getBusinessFacilityCode();
        case EPC_PRODUCT_CODE:
            return getProductCode();
        case EPC_PRODUCTION_NUMBER:
            return getProductionNumber();
        case EPC_PRODUCTION_DATE:
            return getProductionDate();
        case EPC_POWER_SAVING_OPERATION_SETTING:
            return getPowerSavingOperationSetting();
        case EPC_REMOTE_CONTROL_SETTING:
            return getRemoteControlSetting();
        case EPC_CURRENT_TIME_SETTING:
            return getCurrentTimeSetting();
        case EPC_CURRENT_DATE_SETTING:
            return getCurrentDateSetting();
        case EPC_POWER_LIMIT_SETTING:
            return getPowerLimitSetting();
        case EPC_CUMULATIVE_OPERATING_TIME:
            return getCumulativeOperatingTime();
        case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP:
            return getStatusChangeAnnouncementPropertyMap();
        case EPC_SET_PROPERTY_MAP:
            return getSetPropertyMap();
        case EPC_GET_PROPERTY_MAP:
            return getGetPropertyMap();
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1:
            return getPowerGenerationOutputLimitSetting1();
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2:
            return getPowerGenerationOutputLimitSetting2();
        case EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD:
            return getLimitSettingForTheAmountOfElectricitySold();
        case EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED:
            return getRatedPowerGenerationOutputSystemInterconnected();
        case EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT:
            return getRatedPowerGenerationOutputIndependent();
        case EPC_SYSTEM_INTERCONNECTION_INFORMATION:
            return getSystemInterconnectedType();
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            return getMeasuredCumulativeAmountOfElectricityGenerated();
        case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
            return getMeasuredInstantaneousAmountOfElectricityGenerated();
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD:
            return getMeasuredCumulativeAmountOfElectricitySold();

        default:
            return std::shared_ptr<std::vector<unsigned char>>();
        }
    }

    bool HouseholdSolarPowerGeneration::isValidProperty(EchoProperty &property)
    {

        bool valid = EchoObject::isValidProperty(property);
        if (valid)
            return true;

        switch (property.epc)
        {
        case EPC_OPERATION_STATUS:
			return isValidOperationStatus(property.edt);
		case EPC_INSTALLATION_LOCATION:
			return isValidInstallationLocation(property.edt);
		case EPC_STANDARD_VERSION_INFORMATION:
			return isValidStandardVersionInformation(property.edt);
		case EPC_IDENTIFICATION_NUMBER:
			return isValidIdentificationNumber(property.edt);
		case EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION:
			return isValidMeasuredInstantaneousPowerConsumption(property.edt);
		case EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION:
			return isValidMeasuredCumulativePowerConsumption(property.edt);
		case EPC_MANUFACTURERS_FAULT_CODE:
			return isValidManufacturersFaultCode(property.edt);
		case EPC_CURRENT_LIMIT_SETTING:
			return isValidCurrentLimitSetting(property.edt);
		case EPC_FAULT_STATUS:
			return isValidFaultStatus(property.edt);
		case EPC_FAULT_DESCRIPTION:
			return isValidFaultDescription(property.edt);
		case EPC_MANUFACTURER_CODE:
			return isValidManufacturerCode(property.edt);
		case EPC_BUSINESS_FACILITY_CODE:
			return isValidBusinessFacilityCode(property.edt);
		case EPC_PRODUCT_CODE:
			return isValidProductCode(property.edt);
		case EPC_PRODUCTION_NUMBER:
			return isValidProductionNumber(property.edt);
		case EPC_PRODUCTION_DATE:
			return isValidProductionDate(property.edt);
		case EPC_POWER_SAVING_OPERATION_SETTING:
			return isValidPowerSavingOperationSetting(property.edt);
		case EPC_REMOTE_CONTROL_SETTING:
			return isValidRemoteControlSetting(property.edt);
		case EPC_CURRENT_TIME_SETTING:
			return isValidCurrentTimeSetting(property.edt);
		case EPC_CURRENT_DATE_SETTING:
			return isValidCurrentDateSetting(property.edt);
		case EPC_POWER_LIMIT_SETTING:
			return isValidPowerLimitSetting(property.edt);
		case EPC_CUMULATIVE_OPERATING_TIME:
			return isValidCumulativeOperatingTime(property.edt);
		case EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP:
			return isValidStatusChangeAnnouncementPropertyMap(property.edt);
		case EPC_SET_PROPERTY_MAP:
			return isValidSetPropertyMap(property.edt);
		case EPC_GET_PROPERTY_MAP:
			return isValidGetPropertyMap(property.edt);
        case EPC_SYSTEM_INTERCONNECTION_INFORMATION:
            return isValidSystemInterconnEctedType(property.edt);
        case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
            return isValidMeasuredInstantaneousAmountOfElectricityGenerated(property.edt);
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            return isValidMeasuredCumulativeAmountOfElectricityGenerated(property.edt);
        case EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            return isValidResettingCumulativeAmountOfElectricityGenerated(property.edt);
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD:
            return isValidMeasuredCumulativeAmountOfElectricitySold(property.edt);
        case EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD:
            return isValidResettingCumulativeAmountOfElectricitySold(property.edt);
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1:
            return isValidPowerGenerationOutputLimitSetting1(property.edt);
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2:
            return isValidPowerGenerationOutputLimitSetting2(property.edt);
        case EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD:
            return isValidLimitSettingForTheAmountOfElectricitySold(property.edt);
        case EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED:
            return isValidRatedPowerGenerationOutputSystemInterconnected(property.edt);
        case EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT:
            return isValidRatedPowerGenerationOutputIndependent(property.edt);

        default:
            return false;
        }
    }
    HouseholdSolarPowerGeneration::Setter HouseholdSolarPowerGeneration::set()
    {
        return HouseholdSolarPowerGeneration::Setter(getEchoClassCode(), getInstanceCode(), getNode().get()->getAddress(), true);
    }
    HouseholdSolarPowerGeneration::Setter HouseholdSolarPowerGeneration::set(bool responseRequired)
    {
        return HouseholdSolarPowerGeneration::Setter(getEchoClassCode(), getInstanceCode(), getNode().get()->getAddress(), responseRequired);
    }
    HouseholdSolarPowerGeneration::Getter HouseholdSolarPowerGeneration::get()
    {
        return HouseholdSolarPowerGeneration::Getter(getEchoClassCode(), getInstanceCode(), getNode().get()->getAddress());
    }
    HouseholdSolarPowerGeneration::Informer HouseholdSolarPowerGeneration::inform()
    {
        std::string address;
        if (isProxy)
        {
            address = getNode().get()->getAddress();
        }
        else
        {
            address = EchoSocket::MULTICAST_ADDRESS;
        }
        return HouseholdSolarPowerGeneration::Informer(getEchoClassCode(), getInstanceCode(), address, isSelfObject());
    }
    HouseholdSolarPowerGeneration::Informer HouseholdSolarPowerGeneration::inform(bool multicast)
    {
        std::string address;
        if (multicast)
        {
            address = EchoSocket::MULTICAST_ADDRESS;
        }
        else
        {
            address = getNode().get()->getAddress();
        }
        return HouseholdSolarPowerGeneration::Informer(getEchoClassCode(), getInstanceCode(), address, isSelfObject());
    }
    HouseholdSolarPowerGeneration::InformerC HouseholdSolarPowerGeneration::informC(std::string address)
    {
        return HouseholdSolarPowerGeneration::InformerC(getEchoClassCode(), getInstanceCode(), address);
    }
    void HouseholdSolarPowerGeneration::allocateSelfDeviceInstanceCode()
    {
        mEchoInstanceCode = EchoUtils::allocateSelfDeviceInstanceCode(getEchoClassCode());
    }
    void HouseholdSolarPowerGeneration::setupPropertyMaps()
    {
        EchoObject::setupPropertyMaps();
        addStatusChangeAnnouncementProperty(EPC_OPERATION_STATUS);
        addStatusChangeAnnouncementProperty(EPC_INSTALLATION_LOCATION);
		addStatusChangeAnnouncementProperty(EPC_FAULT_STATUS);
        removeSetProperty(EPC_OPERATION_STATUS);
        addGetProperty(EPC_OPERATION_STATUS);
        addGetProperty(EPC_INSTALLATION_LOCATION);
		addGetProperty(EPC_STANDARD_VERSION_INFORMATION);
		addGetProperty(EPC_FAULT_STATUS);
		addGetProperty(EPC_MANUFACTURER_CODE);
		addGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
		addGetProperty(EPC_SET_PROPERTY_MAP);
		addGetProperty(EPC_GET_PROPERTY_MAP);
        addGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);
        addGetProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION);
    }
    HouseholdSolarPowerGeneration::Receiver::Receiver() : EchoObject::Receiver()
    {
    }
    HouseholdSolarPowerGeneration::Receiver::~Receiver()
    {
    }

    bool HouseholdSolarPowerGeneration::Receiver::onSetProperty(std::shared_ptr<EchoObject> eoj,
                                                                unsigned short tid, unsigned char esv, EchoProperty &property,
                                                                bool success)
    {
        bool ret = EchoObject::Receiver::onSetProperty(eoj, tid, esv, property, success);
        if (ret)
            return true;

        switch (property.epc)
        {
            case EPC_OPERATION_STATUS:
			onSetOperationStatus(eoj, tid, esv, property, success);
			return true;
		case EPC_INSTALLATION_LOCATION:
			onSetInstallationLocation(eoj, tid, esv, property, success);
			return true;
		case EPC_CURRENT_LIMIT_SETTING:
			onSetCurrentLimitSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_POWER_SAVING_OPERATION_SETTING:
			onSetPowerSavingOperationSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_REMOTE_CONTROL_SETTING:
			onSetRemoteControlSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_CURRENT_TIME_SETTING:
			onSetCurrentTimeSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_CURRENT_DATE_SETTING:
			onSetCurrentDateSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_POWER_LIMIT_SETTING:
			onSetPowerLimitSetting(eoj, tid, esv, property, success);
			return true;
        case EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            onSetResettingCumulativeAmountOfElectricityGenerated(eoj, tid, esv, property, success);
            return true;
        case EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD:
            onSetResettingCumulativeAmountOfElectricitySold(eoj, tid, esv, property, success);
            return true;
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1:
            onSetPowerGenerationOutputLimitSetting1(eoj, tid, esv, property, success);
            return true;
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2:
            onSetPowerGenerationOutputLimitSetting2(eoj, tid, esv, property, success);
            return true;
        case EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD:
            onSetLimitSettingForTheAmountOfElectricitySold(eoj, tid, esv, property, success);
            return true;
        case EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED:
            onSetRatedPowerGenerationOutputSystemInterconnected(eoj, tid, esv, property, success);
            return true;
        case EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT:
            onSetRatedPowerGenerationOutputIndependent(eoj, tid, esv, property, success);
            return true;
        default:
            return false;
        }
    }

    bool HouseholdSolarPowerGeneration::Receiver::onGetProperty(std::shared_ptr<EchoObject> eoj,
                                                                unsigned short tid, unsigned char esv, EchoProperty &property,
                                                                bool success)
    {
        bool ret = EchoObject::Receiver::onGetProperty(eoj, tid, esv, property, success);
        if (ret)
            return true;
        switch (property.epc)
        {
            case EPC_OPERATION_STATUS:
			onGetOperationStatus(eoj, tid, esv, property, success);
			return true;
		case EPC_INSTALLATION_LOCATION:
			onGetInstallationLocation(eoj, tid, esv, property, success);
			return true;
		case EPC_STANDARD_VERSION_INFORMATION:
			onGetStandardVersionInformation(eoj, tid, esv, property, success);
			return true;
		case EPC_IDENTIFICATION_NUMBER:
			onGetIdentificationNumber(eoj, tid, esv, property, success);
			return true;
		case EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION:
			onGetMeasuredInstantaneousPowerConsumption(eoj, tid, esv, property, success);
			return true;
		case EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION:
			onGetMeasuredCumulativePowerConsumption(eoj, tid, esv, property, success);
			return true;
		case EPC_MANUFACTURERS_FAULT_CODE:
			onGetManufacturersFaultCode(eoj, tid, esv, property, success);
			return true;
		case EPC_CURRENT_LIMIT_SETTING:
			onGetCurrentLimitSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_FAULT_STATUS:
			onGetFaultStatus(eoj, tid, esv, property, success);
			return true;
		case EPC_FAULT_DESCRIPTION:
			onGetFaultDescription(eoj, tid, esv, property, success);
			return true;
		case EPC_MANUFACTURER_CODE:
			onGetManufacturerCode(eoj, tid, esv, property, success);
			return true;
		case EPC_BUSINESS_FACILITY_CODE:
			onGetBusinessFacilityCode(eoj, tid, esv, property, success);
			return true;
		case EPC_PRODUCT_CODE:
			onGetProductCode(eoj, tid, esv, property, success);
			return true;
		case EPC_PRODUCTION_NUMBER:
			onGetProductionNumber(eoj, tid, esv, property, success);
			return true;
		case EPC_PRODUCTION_DATE:
			onGetProductionDate(eoj, tid, esv, property, success);
			return true;
		case EPC_POWER_SAVING_OPERATION_SETTING:
			onGetPowerSavingOperationSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_REMOTE_CONTROL_SETTING:
			onGetRemoteControlSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_CURRENT_TIME_SETTING:
			onGetCurrentTimeSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_CURRENT_DATE_SETTING:
			onGetCurrentDateSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_POWER_LIMIT_SETTING:
			onGetPowerLimitSetting(eoj, tid, esv, property, success);
			return true;
		case EPC_CUMULATIVE_OPERATING_TIME:
			onGetCumulativeOperatingTime(eoj, tid, esv, property, success);
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
        case EPC_SYSTEM_INTERCONNECTION_INFORMATION:
            onGetSystemInterconnEctedType(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
            onGetMeasuredInstantaneousAmountOfElectricityGenerated(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            onGetMeasuredCumulativeAmountOfElectricityGenerated(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD:
            onGetMeasuredCumulativeAmountOfElectricitySold(eoj, tid, esv, property, success);
            return true;
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1:
            onGetPowerGenerationOutputLimitSetting1(eoj, tid, esv, property, success);
            return true;
        case EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2:
            onGetPowerGenerationOutputLimitSetting2(eoj, tid, esv, property, success);
            return true;
        case EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD:
            onGetLimitSettingForTheAmountOfElectricitySold(eoj, tid, esv, property, success);
            return true;
        case EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED:
            onGetRatedPowerGenerationOutputSystemInterconnected(eoj, tid, esv, property, success);
            return true;
        case EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT:
            onGetRatedPowerGenerationOutputIndependent(eoj, tid, esv, property, success);
            return true;
        default:
            return false;
        }
    }

    bool HouseholdSolarPowerGeneration::Receiver::onInformProperty(std::shared_ptr<EchoObject> eoj,
                                                                   unsigned short tid, unsigned char esv, EchoProperty &property)
    {
        bool ret = EchoObject::Receiver::onInformProperty(eoj, tid, esv, property);
        if (ret)
            return true;
        return false;
    }

    HouseholdSolarPowerGeneration::Setter::Setter(unsigned short dstEchoClassCode,
                                                  unsigned char dstEchoInstanceCode, std::string dstEchoAddress,
                                                  bool responseRequired)
        : EchoObject::Setter(dstEchoClassCode, dstEchoInstanceCode, dstEchoAddress, responseRequired)
    {
    }

    HouseholdSolarPowerGeneration::Setter::~Setter()
    {
    }

    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetProperty(unsigned char epc,
                                                                                                 std::vector<unsigned char> edt)
    {
        return dynamic_cast<HouseholdSolarPowerGeneration::Setter &>(EchoObject::Setter::reqSetProperty(epc, edt));
    }

    HouseholdSolarPowerGeneration::Getter::Getter(unsigned short dstEchoClassCode,
                                                  unsigned char dstEchoInstanceCode, std::string dstEchoAddress)
        : EchoObject::Getter(dstEchoClassCode, dstEchoInstanceCode, dstEchoAddress)
    {
    }

    HouseholdSolarPowerGeneration::Getter::~Getter()
    {
    }

    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetProperty(unsigned char epc)
    {
        return dynamic_cast<HouseholdSolarPowerGeneration::Getter &>(EchoObject::Getter::reqGetProperty(epc));
    }

    HouseholdSolarPowerGeneration::Informer::Informer(unsigned short echoClassCode,
                                                      unsigned char echoInstanceCode, std::string dstEchoAddress,
                                                      bool isSelfObject)
        : EchoObject::Informer(echoClassCode, echoInstanceCode, dstEchoAddress, isSelfObject)
    {
    }

    HouseholdSolarPowerGeneration::Informer::~Informer()
    {
    }

    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProperty(
        unsigned char epc)
    {
        return dynamic_cast<HouseholdSolarPowerGeneration::Informer &>(EchoObject::Informer::reqInformProperty(epc));
    }

    HouseholdSolarPowerGeneration::InformerC::InformerC(unsigned short srcEchoClassCode,
                                                        unsigned char srcEchoInstanceCode, std::string dstEchoAddress)
        : EchoObject::InformerC(srcEchoClassCode, srcEchoInstanceCode, dstEchoAddress)
    {
    }

    HouseholdSolarPowerGeneration::InformerC::~InformerC()
    {
    }
    HouseholdSolarPowerGeneration::Proxy::Proxy(unsigned short echoClassCode,
							   unsigned char echoInstanceCode) : HouseholdSolarPowerGeneration()
	{
		mEchoClassCode = echoClassCode;
		mEchoInstanceCode = echoInstanceCode;
	}

	HouseholdSolarPowerGeneration::Proxy::~Proxy()
	{
	}

    unsigned char HouseholdSolarPowerGeneration::Proxy::getInstanceCode()
    {
        return mEchoInstanceCode;
    }

    unsigned short HouseholdSolarPowerGeneration::Proxy::getEchoClassCode()
    {
        return mEchoClassCode;
    }
    bool HouseholdSolarPowerGeneration::isValidOperationStatus(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 1)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::isValidInstallationLocation(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 1 && edt.size() != 17)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getStandardVersionInformation()
	{
		return mStandardVersionInformation;
	}

	bool HouseholdSolarPowerGeneration::isValidStandardVersionInformation(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 4)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getIdentificationNumber()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidIdentificationNumber(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 9 && edt.size() != 17)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getMeasuredInstantaneousPowerConsumption()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidMeasuredInstantaneousPowerConsumption(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 2)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getMeasuredCumulativePowerConsumption()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidMeasuredCumulativePowerConsumption(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 4)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getManufacturersFaultCode()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidManufacturersFaultCode(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() > 225)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::setCurrentLimitSetting(std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getCurrentLimitSetting()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidCurrentLimitSetting(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 1)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::isValidFaultStatus(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 1)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getFaultDescription()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidFaultDescription(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 2)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::isValidManufacturerCode(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 3)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getBusinessFacilityCode()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidBusinessFacilityCode(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 3)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getProductCode()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidProductCode(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 12)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getProductionNumber()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidProductionNumber(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 12)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getProductionDate()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidProductionDate(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 4)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::setPowerSavingOperationSetting(
		std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getPowerSavingOperationSetting()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidPowerSavingOperationSetting(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 1)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::setRemoteControlSetting(std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getRemoteControlSetting()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidRemoteControlSetting(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 1)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::setCurrentTimeSetting(std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getCurrentTimeSetting()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidCurrentTimeSetting(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 2)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::setCurrentDateSetting(std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getCurrentDateSetting()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidCurrentDateSetting(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 4)
			return false;
		return true;
	}

	bool HouseholdSolarPowerGeneration::setPowerLimitSetting(std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getPowerLimitSetting()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidPowerLimitSetting(std::vector<unsigned char> &edt)
	{
		if (edt.size() != 2)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getCumulativeOperatingTime()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::isValidCumulativeOperatingTime(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() != 5)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getStatusChangeAnnouncementPropertyMap()
	{
		return EchoUtils::convertPropertiesToPropertyMap(getStatusChangeAnnouncementProperties());
	}

	bool HouseholdSolarPowerGeneration::isValidStatusChangeAnnouncementPropertyMap(
		std::vector<unsigned char> &edt)
	{
		if (edt.size() > 17)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getSetPropertyMap()
	{
		return EchoUtils::convertPropertiesToPropertyMap(getSetProperties());
	}

	bool HouseholdSolarPowerGeneration::isValidSetPropertyMap(std::vector<unsigned char> &edt)
	{
		if (edt.size() > 17)
			return false;
		return true;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getGetPropertyMap()
	{
		return EchoUtils::convertPropertiesToPropertyMap(getGetProperties());
	}

	bool HouseholdSolarPowerGeneration::isValidGetPropertyMap(std::vector<unsigned char> &edt)
	{
		if (edt.size() > 17)
			return false;
		return true;
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetOperationStatus(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetInstallationLocation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetCurrentLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetPowerSavingOperationSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetRemoteControlSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetCurrentTimeSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetCurrentDateSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onSetPowerLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetOperationStatus(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetInstallationLocation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetStandardVersionInformation(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetIdentificationNumber(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetMeasuredInstantaneousPowerConsumption(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetMeasuredCumulativePowerConsumption(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetManufacturersFaultCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetCurrentLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetFaultStatus(std::shared_ptr<EchoObject> eoj,
												  unsigned short tid, unsigned char esv, EchoProperty &property,
												  bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetFaultDescription(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetManufacturerCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetBusinessFacilityCode(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetProductCode(std::shared_ptr<EchoObject> eoj,
												  unsigned short tid, unsigned char esv, EchoProperty &property,
												  bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetProductionNumber(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetProductionDate(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetPowerSavingOperationSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetRemoteControlSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetCurrentTimeSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetCurrentDateSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetPowerLimitSetting(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetCumulativeOperatingTime(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetStatusChangeAnnouncementPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetSetPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	void HouseholdSolarPowerGeneration::Receiver::onGetGetPropertyMap(
		std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
		EchoProperty &property, bool success)
	{
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetOperationStatus(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_OPERATION_STATUS, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetInstallationLocation(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_INSTALLATION_LOCATION, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetCurrentLimitSetting(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_CURRENT_LIMIT_SETTING, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetPowerSavingOperationSetting(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_POWER_SAVING_OPERATION_SETTING, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetRemoteControlSetting(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_REMOTE_CONTROL_SETTING, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetCurrentTimeSetting(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_CURRENT_TIME_SETTING, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetCurrentDateSetting(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_CURRENT_DATE_SETTING, edt);
	}

	HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetPowerLimitSetting(
		std::vector<unsigned char> edt)
	{
		return reqSetProperty(EPC_POWER_LIMIT_SETTING, edt);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetOperationStatus()
	{
		return reqGetProperty(EPC_OPERATION_STATUS);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetInstallationLocation()
	{
		return reqGetProperty(EPC_INSTALLATION_LOCATION);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetStandardVersionInformation()
	{
		return reqGetProperty(EPC_STANDARD_VERSION_INFORMATION);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetIdentificationNumber()
	{
		return reqGetProperty(EPC_IDENTIFICATION_NUMBER);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetMeasuredInstantaneousPowerConsumption()
	{
		return reqGetProperty(EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetMeasuredCumulativePowerConsumption()
	{
		return reqGetProperty(EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetManufacturersFaultCode()
	{
		return reqGetProperty(EPC_MANUFACTURERS_FAULT_CODE);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetCurrentLimitSetting()
	{
		return reqGetProperty(EPC_CURRENT_LIMIT_SETTING);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetFaultStatus()
	{
		return reqGetProperty(EPC_FAULT_STATUS);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetFaultDescription()
	{
		return reqGetProperty(EPC_FAULT_DESCRIPTION);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetManufacturerCode()
	{
		return reqGetProperty(EPC_MANUFACTURER_CODE);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetBusinessFacilityCode()
	{
		return reqGetProperty(EPC_BUSINESS_FACILITY_CODE);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetProductCode()
	{
		return reqGetProperty(EPC_PRODUCT_CODE);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetProductionNumber()
	{
		return reqGetProperty(EPC_PRODUCTION_NUMBER);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetProductionDate()
	{
		return reqGetProperty(EPC_PRODUCTION_DATE);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetPowerSavingOperationSetting()
	{
		return reqGetProperty(EPC_POWER_SAVING_OPERATION_SETTING);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetRemoteControlSetting()
	{
		return reqGetProperty(EPC_REMOTE_CONTROL_SETTING);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetCurrentTimeSetting()
	{
		return reqGetProperty(EPC_CURRENT_TIME_SETTING);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetCurrentDateSetting()
	{
		return reqGetProperty(EPC_CURRENT_DATE_SETTING);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetPowerLimitSetting()
	{
		return reqGetProperty(EPC_POWER_LIMIT_SETTING);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetCumulativeOperatingTime()
	{
		return reqGetProperty(EPC_CUMULATIVE_OPERATING_TIME);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetStatusChangeAnnouncementPropertyMap()
	{
		return reqGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetSetPropertyMap()
	{
		return reqGetProperty(EPC_SET_PROPERTY_MAP);
	}

	HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetGetPropertyMap()
	{
		return reqGetProperty(EPC_GET_PROPERTY_MAP);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformOperationStatus()
	{
		return reqInformProperty(EPC_OPERATION_STATUS);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformInstallationLocation()
	{
		return reqInformProperty(EPC_INSTALLATION_LOCATION);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformStandardVersionInformation()
	{
		return reqInformProperty(EPC_STANDARD_VERSION_INFORMATION);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformIdentificationNumber()
	{
		return reqInformProperty(EPC_IDENTIFICATION_NUMBER);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredInstantaneousPowerConsumption()
	{
		return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredCumulativePowerConsumption()
	{
		return reqInformProperty(EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformManufacturersFaultCode()
	{
		return reqInformProperty(EPC_MANUFACTURERS_FAULT_CODE);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCurrentLimitSetting()
	{
		return reqInformProperty(EPC_CURRENT_LIMIT_SETTING);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformFaultStatus()
	{
		return reqInformProperty(EPC_FAULT_STATUS);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformFaultDescription()
	{
		return reqInformProperty(EPC_FAULT_DESCRIPTION);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformManufacturerCode()
	{
		return reqInformProperty(EPC_MANUFACTURER_CODE);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformBusinessFacilityCode()
	{
		return reqInformProperty(EPC_BUSINESS_FACILITY_CODE);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProductCode()
	{
		return reqInformProperty(EPC_PRODUCT_CODE);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProductionNumber()
	{
		return reqInformProperty(EPC_PRODUCTION_NUMBER);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProductionDate()
	{
		return reqInformProperty(EPC_PRODUCTION_DATE);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformPowerSavingOperationSetting()
	{
		return reqInformProperty(EPC_POWER_SAVING_OPERATION_SETTING);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformRemoteControlSetting()
	{
		return reqInformProperty(EPC_REMOTE_CONTROL_SETTING);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCurrentTimeSetting()
	{
		return reqInformProperty(EPC_CURRENT_TIME_SETTING);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCurrentDateSetting()
	{
		return reqInformProperty(EPC_CURRENT_DATE_SETTING);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformPowerLimitSetting()
	{
		return reqInformProperty(EPC_POWER_LIMIT_SETTING);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCumulativeOperatingTime()
	{
		return reqInformProperty(EPC_CUMULATIVE_OPERATING_TIME);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformStatusChangeAnnouncementPropertyMap()
	{
		return reqInformProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformSetPropertyMap()
	{
		return reqInformProperty(EPC_SET_PROPERTY_MAP);
	}

	HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformGetPropertyMap()
	{
		return reqInformProperty(EPC_GET_PROPERTY_MAP);
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::Proxy::getOperationStatus()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	bool HouseholdSolarPowerGeneration::Proxy::setInstallationLocation(
		std::vector<unsigned char> &edt)
	{
		return false;
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::Proxy::getInstallationLocation()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::Proxy::getFaultStatus()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

	std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::Proxy::getManufacturerCode()
	{
		return std::shared_ptr<std::vector<unsigned char>>();
	}

    bool HouseholdSolarPowerGeneration::isValidSystemInterconnEctedType(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 1)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidMeasuredInstantaneousAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 2)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidMeasuredCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 4)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 1)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidMeasuredCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 4)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 1)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 1)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 2)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 2)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 2)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::isValidRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 2)
            return false;
        return true;
    }
    bool HouseholdSolarPowerGeneration::setResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
    {
        return false;
    }

    bool HouseholdSolarPowerGeneration::setResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool HouseholdSolarPowerGeneration::setRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool HouseholdSolarPowerGeneration::setPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool HouseholdSolarPowerGeneration::setPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool HouseholdSolarPowerGeneration::setLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool HouseholdSolarPowerGeneration::setRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt)
    {
        return false;
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetResettingCumulativeAmountOfElectricitySold(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetResettingCumulativeAmountOfElectricityGenerated(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetPowerGenerationOutputLimitSetting1(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetPowerGenerationOutputLimitSetting2(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetLimitSettingForTheAmountOfElectricitySold(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetRatedPowerGenerationOutputSystemInterconnected(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onSetRatedPowerGenerationOutputIndependent(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetSystemInterconnEctedType(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetMeasuredInstantaneousAmountOfElectricityGenerated(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetMeasuredCumulativeAmountOfElectricityGenerated(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetMeasuredCumulativeAmountOfElectricitySold(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetPowerGenerationOutputLimitSetting1(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetPowerGenerationOutputLimitSetting2(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetLimitSettingForTheAmountOfElectricitySold(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetRatedPowerGenerationOutputSystemInterconnected(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void HouseholdSolarPowerGeneration::Receiver::onGetRatedPowerGenerationOutputIndependent(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }

    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getSystemInterconnectedType()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getMeasuredCumulativeAmountOfElectricitySold()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getPowerGenerationOutputLimitSetting1()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getPowerGenerationOutputLimitSetting2()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getLimitSettingForTheAmountOfElectricitySold()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getRatedPowerGenerationOutputSystemInterconnected()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> HouseholdSolarPowerGeneration::getRatedPowerGenerationOutputIndependent()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetLimitSettingForTheAmountOfElectricitySold(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD, edt);
    }
    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetResettingCumulativeAmountOfElectricityGenerated(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION, edt);
    }
    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetResettingCumulativeAmountOfElectricitySold(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD, edt);
    }
    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetPowerGenerationOutputLimitSetting1(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1, edt);
    }
    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetPowerGenerationOutputLimitSetting2(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2, edt);
    }
    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetRatedPowerGenerationOutputSystemInterconnected(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED, edt);
    }
    HouseholdSolarPowerGeneration::Setter &HouseholdSolarPowerGeneration::Setter::reqSetRatedPowerGenerationOutputIndependent(
        std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT, edt);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetSystemInterconnEctedType()
    {
        return reqGetProperty(EPC_SYSTEM_INTERCONNECTION_INFORMATION);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetMeasuredInstantaneousAmountOfElectricityGenerated()
    {
        return reqGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetMeasuredCumulativeAmountOfElectricityGenerated()
    {
        return reqGetProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetMeasuredCumulativeAmountOfElectricitySold()
    {
        return reqGetProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetPowerGenerationOutputLimitSetting1()
    {
        return reqGetProperty(EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetPowerGenerationOutputLimitSetting2()
    {
        return reqGetProperty(EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetLimitSettingForTheAmountOfElectricitySold()
    {
        return reqGetProperty(EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetRatedPowerGenerationOutputSystemInterconnected()
    {
        return reqGetProperty(EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED);
    }
    HouseholdSolarPowerGeneration::Getter &HouseholdSolarPowerGeneration::Getter::reqGetRatedPowerGenerationOutputIndependent()
    {
        return reqGetProperty(EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformSystemInterconnEctedType()
    {
        return reqInformProperty(EPC_SYSTEM_INTERCONNECTION_INFORMATION);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformLimitSettingForTheAmountOfElectricitySold()
    {
        return reqInformProperty(EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredCumulativeAmountOfElectricityGenerated()
    {
        return reqInformProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredCumulativeAmountOfElectricitySold()
    {
        return reqInformProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredInstantaneousAmountOfElectricityGenerated()
    {
        return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformPowerGenerationOutputLimitSetting1()
    {
        return reqInformProperty(EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformPowerGenerationOutputLimitSetting2()
    {
        return reqInformProperty(EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformRatedPowerGenerationOutputSystemInterconnected()
    {
        return reqInformProperty(EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED);
    }
    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformRatedPowerGenerationOutputIndependent()
    {
        return reqInformProperty(EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT);
    }

};
