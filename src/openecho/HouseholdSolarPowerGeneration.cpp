
#include "HouseholdSolarPowerGeneration.h"
#include "OpenECHO.h"
#include "Echo.h"

namespace sonycsl_openecho
{
    static const short ECHO_CLASS_CODE = 0x0279;
    const unsigned char DeviceObject::EPC_OPERATION_STATUS = 0x80;
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

    HouseholdSolarPowerGeneration::HouseholdSolarPowerGeneration() : DeviceObject()
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

    void HouseholdSolarPowerGeneration::setupPropertyMaps()
    {
        EchoObject::setupPropertyMaps();
        addStatusChangeAnnouncementProperty(EPC_OPERATION_STATUS);
        // addStatusChangeAnnouncementProperty(EPC_INSTALLATION_LOCATION);
        // addStatusChangeAnnouncementProperty(EPC_FAULT_STATUS);
        removeSetProperty(EPC_OPERATION_STATUS);
        addGetProperty(EPC_OPERATION_STATUS);
        // addGetProperty(EPC_INSTALLATION_LOCATION);
        // addGetProperty(EPC_STANDARD_VERSION_INFORMATION);
        // addGetProperty(EPC_FAULT_STATUS);
        // addGetProperty(EPC_MANUFACTURER_CODE);
        // addGetProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
        // addGetProperty(EPC_SET_PROPERTY_MAP);
        // addGetProperty(EPC_GET_PROPERTY_MAP);
        addGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);
        addGetProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION);
    }
    void HouseholdSolarPowerGeneration::onNew(std::shared_ptr<DeviceObject> eoj)
    {
        DeviceObject::onNew(eoj);
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

    // HouseholdSolarPowerGeneration::Informer HouseholdSolarPowerGeneration::inform()
    // {
    //     std::string address;
    //     if (isProxy)
    //     {
    //         address = getNode().get()->getAddress();
    //     }
    //     else
    //     {
    //         address = EchoSocket::MULTICAST_ADDRESS;
    //     }
    //     return HouseholdSolarPowerGeneration::Informer(getEchoClassCode(), getInstanceCode(), address, isSelfObject());
    // }
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

    bool HouseholdSolarPowerGeneration::setOperationStatus(std::vector<unsigned char> &edt)
    {
        return false;
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

    HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformOperationStatus()
    {
    	return reqInformProperty(EPC_OPERATION_STATUS);
    }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformInstallationLocation()
    // {
    // 	return reqInformProperty(EPC_INSTALLATION_LOCATION);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformStandardVersionInformation()
    // {
    // 	return reqInformProperty(EPC_STANDARD_VERSION_INFORMATION);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformIdentificationNumber()
    // {
    // 	return reqInformProperty(EPC_IDENTIFICATION_NUMBER);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredInstantaneousPowerConsumption()
    // {
    // 	return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformMeasuredCumulativePowerConsumption()
    // {
    // 	return reqInformProperty(EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformManufacturersFaultCode()
    // {
    // 	return reqInformProperty(EPC_MANUFACTURERS_FAULT_CODE);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCurrentLimitSetting()
    // {
    // 	return reqInformProperty(EPC_CURRENT_LIMIT_SETTING);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformFaultStatus()
    // {
    // 	return reqInformProperty(EPC_FAULT_STATUS);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformFaultDescription()
    // {
    // 	return reqInformProperty(EPC_FAULT_DESCRIPTION);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformManufacturerCode()
    // {
    // 	return reqInformProperty(EPC_MANUFACTURER_CODE);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformBusinessFacilityCode()
    // {
    // 	return reqInformProperty(EPC_BUSINESS_FACILITY_CODE);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProductCode()
    // {
    // 	return reqInformProperty(EPC_PRODUCT_CODE);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProductionNumber()
    // {
    // 	return reqInformProperty(EPC_PRODUCTION_NUMBER);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformProductionDate()
    // {
    // 	return reqInformProperty(EPC_PRODUCTION_DATE);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformPowerSavingOperationSetting()
    // {
    // 	return reqInformProperty(EPC_POWER_SAVING_OPERATION_SETTING);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformRemoteControlSetting()
    // {
    // 	return reqInformProperty(EPC_REMOTE_CONTROL_SETTING);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCurrentTimeSetting()
    // {
    // 	return reqInformProperty(EPC_CURRENT_TIME_SETTING);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCurrentDateSetting()
    // {
    // 	return reqInformProperty(EPC_CURRENT_DATE_SETTING);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformPowerLimitSetting()
    // {
    // 	return reqInformProperty(EPC_POWER_LIMIT_SETTING);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformCumulativeOperatingTime()
    // {
    // 	return reqInformProperty(EPC_CUMULATIVE_OPERATING_TIME);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformStatusChangeAnnouncementPropertyMap()
    // {
    // 	return reqInformProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformSetPropertyMap()
    // {
    // 	return reqInformProperty(EPC_SET_PROPERTY_MAP);
    // }

    // HouseholdSolarPowerGeneration::Informer &HouseholdSolarPowerGeneration::Informer::reqInformGetPropertyMap()
    // {
    // 	return reqInformProperty(EPC_GET_PROPERTY_MAP);
    // }

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
