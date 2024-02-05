#include "SmartElectricEnergyMeter.h"
#include "OpenECHO.h"
#include "Echo.h"
namespace sonycsl_openecho
{
    static const short ECHO_CLASS_CODE = 0x0288;
    const unsigned char SmartElectricEnergyMeter::EPC_OPERATION_STATUS = 0x80;
    const unsigned char SmartElectricEnergyMeter::EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION = 0xD0;
    const unsigned char SmartElectricEnergyMeter::EPC_OWNER_CLASSIFICATION = 0xD1;
    const unsigned char SmartElectricEnergyMeter::EPC_PHASES_AND_WIRES_SETTING_STATUS = D2;
    const unsigned char SmartElectricEnergyMeter::EPC_COMPOSITE_TRANSFORMATION_RATIO = D3;
    const unsigned char SmartElectricEnergyMeter::EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO = D4;
    const unsigned char SmartElectricEnergyMeter::EPC_METER_TYPE_CERTIFICATION_NUMBER = D5;
    const unsigned char SmartElectricEnergyMeter::EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY = D6;
    const unsigned char SmartElectricEnergyMeter::EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY = D7;
    const unsigned char SmartElectricEnergyMeter::EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION = E0;
    const unsigned char SmartElectricEnergyMeter::EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS = E1;
    const unsigned char SmartElectricEnergyMeter::EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION = E2;
    const unsigned char SmartElectricEnergyMeter::EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION = E3;
    const unsigned char SmartElectricEnergyMeter::EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION = E4;
    const unsigned char SmartElectricEnergyMeter::EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED = E5;
    const unsigned char SmartElectricEnergyMeter::EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY = E7;
    const unsigned char SmartElectricEnergyMeter::EPC_MEASURED_INSTANTANEOUS_CURRENTS = E8;
    const unsigned char SmartElectricEnergyMeter::EPC_MEASURED_INSTANTANEOUS_VOLTAGES = E9;
    const unsigned char SmartElectricEnergyMeter::EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION = EA;
    const unsigned char SmartElectricEnergyMeter::EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION = EB;
    const unsigned char SmartElectricEnergyMeter::EPC_GET_PROPERTY_MAP = 0x9F;
    SmartElectricEnergyMeter::SmartElectricEnergyMeter() : DeviceObject()
    {
        mEchoInstanceCode = 0;
        mStandardVersionInformation = std::shared_ptr<std::vector<unsigned char>>(new std::vector<unsigned char>());
        mStandardVersionInformation.get()->resize(4);
        (*(mStandardVersionInformation.get()))[0] = 0;
        (*(mStandardVersionInformation.get()))[1] = 0;
        (*(mStandardVersionInformation.get()))[2] = 0x43;
        (*(mStandardVersionInformation.get()))[3] = 0;
    }
    SmartElectricEnergyMeter::~SmartElectricEnergyMeter()
    {
        // TODO Auto-generated destructor stub
    }
    unsigned char SmartElectricEnergyMeter::getInstanceCode()
    {
        return mEchoInstanceCode;
    }

    void SmartElectricEnergyMeter::setupPropertyMaps()
    {
        EchoObject::setupPropertyMaps();
        addStatusChangeAnnouncementProperty(EPC_OPERATION_STATUS);
        removeSetProperty(EPC_OPERATION_STATUS);
        addGetProperty(EPC_OPERATION_STATUS);
        addGetProperty(EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY);
        addGetProperty(EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION);
        addGetProperty(EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS);
        addGetProperty(EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION);
    }
    void SmartElectricEnergyMeter::onNew(std::shared_ptr<DeviceObject> eoj)
    {
        DeviceObject::onNew(eoj);
        std::shared_ptr<SmartElectricEnergyMeter> device = std::dynamic_pointer_cast<SmartElectricEnergyMeter>(eoj);
        Echo::getEventListenerDelegate().onNewSmartElectricEnergyMeter(device);
    }
    bool SmartElectricEnergyMeter::setProperty(EchoProperty &property)
    {
        bool success = EchoObject::setProperty(property);
        if (success)
            return true;

        switch (property.epc)
        {
        case EPC_OPERATION_STATUS:
            return setOperationStatus(property.edt);
        case EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION:
            return setElectricEnergyMeterClassification(property.edt);
        case EPC_OWNER_CLASSIFICATION:
            return setOwnerClassification(property.edt);
        case EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY:
            return setYearAndMonthOfInspectionExpiry(property.edt);
        case EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED:
            return setDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(property.edt);
        default:
            return false;
        }
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getProperty(
        unsigned char epc)
    {

        std::shared_ptr<std::vector<unsigned char>> edt = EchoObject::getProperty(epc);
        if (edt.get() != nullptr)
            return edt;

        switch (epc)
        {
        case EPC_OPERATION_STATUS:
            return getOperationStatus();
        case EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION:
            return getElectricEnergyMeterClassification();
        case EPC_OWNER_CLASSIFICATION:
            return getOwnerClassification();
        case EPC_PHASES_AND_WIRES_SETTING_STATUS:
            return getPhasesAndWiresSettingStatus();
        case EPC_COMPOSITE_TRANSFORMATION_RATIO:
            return getCompositeTransformationRatio();
        case EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO:
            return getMultiplyingFactorForCompositeTransformationRatio();
        case EPC_METER_TYPE_CERTIFICATION_NUMBER:
            return getMeterTypeCertificationNumber();
        case EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY:
            return getYearAndMonthOfInspectionExpiry();
        case EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY:
            return getNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy();
        case EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION:
            return getMeasuredCumulativeAmountOfElectricEnergyNormalDirection();
        case EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS:
            return getUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections();
        case EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION:
            return getHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection();
        case EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION:
            return getMeasuredCumulativeAmountsOfElectricEnergyReverseDirection();
        case EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION:
            return getHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection();
        case EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED:
            return getDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved();
        case EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY:
            return getMeasuredInstantaneousElectricEnergy();
        case EPC_MEASURED_INSTANTANEOUS_CURRENTS:
            return getMeasuredInstantaneousCurrents();
        case EPC_MEASURED_INSTANTANEOUS_VOLTAGES:
            return getMeasuredInstantaneousVoltages();
        case EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION:
            return getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection();
        case EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION:
            return getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection();

        default:
            return std::shared_ptr<std::vector<unsigned char>>();
        }
    }
    bool SmartElectricEnergyMeter::isValidProperty(EchoProperty &property)
    {

        bool valid = EchoObject::isValidProperty(property);
        if (valid)
            return true;

        switch (property.epc)
        {
        case EPC_OPERATION_STATUS:
            return isValidOperationStatus(property.edt);
        case EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION:
            return isValidElectricEnergyMeterClassification(property.edt);
        case EPC_OWNER_CLASSIFICATION:
            return isValidOwnerClassification(property.edt);
        case EPC_PHASES_AND_WIRES_SETTING_STATUS:
            return isValidPhasesAndWiresSettingStatus(property.edt);
        case EPC_COMPOSITE_TRANSFORMATION_RATIO:
            return isValidCompositeTransformationRatio(property.edt);
        case EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO:
            return isValidMultiplyingFactorForCompositeTransformationRatio(property.edt);
        case EPC_METER_TYPE_CERTIFICATION_NUMBER:
            return isValidMeterTypeCertificationNumber(property.edt);
        case EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY:
            return isValidYearAndMonthOfInspectionExpiry(property.edt);
        case EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY:
            return isValidNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy(property.edt);
        case EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION:
            return isValidMeasuredCumulativeAmountOfElectricEnergyNormalDirection(property.edt);
        case EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS:
            return isValidUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections(property.edt);
        case EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION:
            return isValidHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection(property.edt);
        case EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION:
            return isValidMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(property.edt);
        case EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION:
            return isValidHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(property.edt);
        case EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED:
            return isValidDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(property.edt);
        case EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY:
            return isValidMeasuredInstantaneousElectricEnergy(property.edt);
        case EPC_MEASURED_INSTANTANEOUS_CURRENTS:
            return isValidMeasuredInstantaneousCurrents(property.edt);
        case EPC_MEASURED_INSTANTANEOUS_VOLTAGES:
            return isValidMeasuredInstantaneousVoltages(property.edt);
        case EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION:
            return isValidCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection(property.edt);
        case EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION:
            return isValidCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection(property.edt);

        default:
            return false;
        }
    }
    SmartElectricEnergyMeter::Setter SmartElectricEnergyMeter::set()
    {
        return SmartElectricEnergyMeter::Setter(getEchoClassCode(), getInstanceCode(), getNode().get()->getAddress(), true);
    }
    SmartElectricEnergyMeter::Setter SmartElectricEnergyMeter::set(bool responseRequired)
    {
        return SmartElectricEnergyMeter::Setter(getEchoClassCode(), getInstanceCode(), getNode().get()->getAddress(), responseRequired);
    }
    SmartElectricEnergyMeter::Getter SmartElectricEnergyMeter::get()
    {
        return SmartElectricEnergyMeter::Getter(getEchoClassCode(), getInstanceCode(), getNode().get()->getAddress());
    }

    SmartElectricEnergyMeter::Informer SmartElectricEnergyMeter::inform()
    {
        std::string address;
        if (isProxy())
        {
            address = getNode().get()->getAddress();
        }
        else
        {
            address = EchoSocket::MULTICAST_ADDRESS;
        }
        return SmartElectricEnergyMeter::Informer(getEchoClassCode(), getInstanceCode(), address, isSelfObject());
    }
    SmartElectricEnergyMeter::Informer SmartElectricEnergyMeter::inform(bool multicast)
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
        return SmartElectricEnergyMeter::Informer(getEchoClassCode(), getInstanceCode(), address, isSelfObject());
    }
    SmartElectricEnergyMeter::InformerC SmartElectricEnergyMeter::informC(std::string address)
    {
        return SmartElectricEnergyMeter::InformerC(getEchoClassCode(), getInstanceCode(), address);
    }
    void SmartElectricEnergyMeter::allocateSelfDeviceInstanceCode()
    {
        mEchoInstanceCode = EchoUtils::allocateSelfDeviceInstanceCode(getEchoClassCode());
    }

    bool SmartElectricEnergyMeter::setOperationStatus(std::vector<unsigned char> &edt)
    {
        return false;
    }
    SmartElectricEnergyMeter::Receiver::Receiver() : EchoObject::Receiver()
    {
    }
    SmartElectricEnergyMeter::Receiver::~Receiver()
    {
    }

    bool SmartElectricEnergyMeter::Receiver::onSetProperty(std::shared_ptr<EchoObject> eoj,
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
        case EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION:
            onSetElectricEnergyMeterClassification(eoj, tid, esv, property, success);
            return true;
        case EPC_OWNER_CLASSIFICATION:
            onSetOwnerClassification(eoj, tid, esv, property, success);
            return true;
        case EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY:
            onSetYearAndMonthOfInspectionExpiry(eoj, tid, esv, property, success);
            return true;
        case EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED:
            onSetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(eoj, tid, esv, property, success);
            return true;
        default:
            return false;
        }
    }
    bool SmartElectricEnergyMeter::Receiver::onGetProperty(std::shared_ptr<EchoObject> eoj,
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
        case EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION:
            onGetElectricEnergyMeterClassification(eoj, tid, esv, property, success);
            return true;
        case EPC_OWNER_CLASSIFICATION:
            onGetOwnerClassification(eoj, tid, esv, property, success);
            return true;
        case EPC_PHASES_AND_WIRES_SETTING_STATUS:
            onGetPhasesAndWiresSettingStatus(eoj, tid, esv, property, success);
            return true;
        case EPC_COMPOSITE_TRANSFORMATION_RATIO:
            onGetCompositeTransformationRatio(eoj, tid, esv, property, success);
            return true;
        case EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO:
            onGetMultiplyingFactorForCompositeTransformationRatio(eoj, tid, esv, property, success);
            return true;
        case EPC_METER_TYPE_CERTIFICATION_NUMBER:
            onGetMeterTypeCertificationNumber(eoj, tid, esv, property, success);
            return true;
        case EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY:
            onGetYearAndMonthOfInspectionExpiry(eoj, tid, esv, property, success);
            return true;
        case EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY:
            onGetNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION:
            onGetMeasuredCumulativeAmountOfElectricEnergyNormalDirection(eoj, tid, esv, property, success);
            return true;
        case EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS:
            onGetUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections(eoj, tid, esv, property, success);
            return true;
        case EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION:
            onGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION:
            onGetMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(eoj, tid, esv, property, success);
            return true;
        case EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION:
            onGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(eoj, tid, esv, property, success);
            return true;
        case EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED:
            onGetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY:
            onGetMeasuredInstantaneousElectricEnergy(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_INSTANTANEOUS_CURRENTS:
            onGetMeasuredInstantaneousCurrents(eoj, tid, esv, property, success);
            return true;
        case EPC_MEASURED_INSTANTANEOUS_VOLTAGES:
            onGetMeasuredInstantaneousVoltages(eoj, tid, esv, property, success);
            return true;
        case EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION:
            onGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection(eoj, tid, esv, property, success);
            return true;
        case EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION:
            onGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection(eoj, tid, esv, property, success);
            return true;
        default:
            return false;
        }
    }
    SmartElectricEnergyMeter::Setter::Setter(unsigned short dstEchoClassCode,
                                             unsigned char dstEchoInstanceCode, std::string dstEchoAddress,
                                             bool responseRequired)
        : EchoObject::Setter(dstEchoClassCode, dstEchoInstanceCode, dstEchoAddress, responseRequired)
    {
    }

    SmartElectricEnergyMeter::Setter::~Setter()
    {
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetProperty(unsigned char epc,
                                                                                       std::vector<unsigned char> edt)
    {
        return dynamic_cast<SmartElectricEnergyMeter::Setter &>(EchoObject::Setter::reqSetProperty(epc, edt));
    }

    SmartElectricEnergyMeter::Getter::Getter(unsigned short dstEchoClassCode,
                                             unsigned char dstEchoInstanceCode, std::string dstEchoAddress)
        : EchoObject::Getter(dstEchoClassCode, dstEchoInstanceCode, dstEchoAddress)
    {
    }

    SmartElectricEnergyMeter::Getter::~Getter()
    {
    }

    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetProperty(unsigned char epc)
    {
        return dynamic_cast<SmartElectricEnergyMeter::Getter &>(EchoObject::Getter::reqGetProperty(epc));
    }

    SmartElectricEnergyMeter::Informer::Informer(unsigned short echoClassCode,
                                                 unsigned char echoInstanceCode, std::string dstEchoAddress,
                                                 bool isSelfObject)
        : EchoObject::Informer(echoClassCode, echoInstanceCode, dstEchoAddress, isSelfObject)
    {
    }

    SmartElectricEnergyMeter::Informer::~Informer()
    {
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformProperty(
        unsigned char epc)
    {
        return dynamic_cast<SmartElectricEnergyMeter::Informer &>(EchoObject::Informer::reqInformProperty(epc));
    }

    SmartElectricEnergyMeter::InformerC::InformerC(unsigned short srcEchoClassCode,
                                                   unsigned char srcEchoInstanceCode, std::string dstEchoAddress)
        : EchoObject::InformerC(srcEchoClassCode, srcEchoInstanceCode, dstEchoAddress)
    {
    }

    SmartElectricEnergyMeter::InformerC::~InformerC()
    {
    }

    SmartElectricEnergyMeter::Proxy::Proxy(unsigned short echoClassCode, unsigned char echoInstanceCode) : SmartElectricEnergyMeter()
    {
        mEchoClassCode = echoClassCode;
        mEchoInstanceCode = echoInstanceCode;
    }

    SmartElectricEnergyMeter::Proxy::~Proxy()
    {
    }

    unsigned char SmartElectricEnergyMeter::Proxy::getInstanceCode()
    {
        return mEchoInstanceCode;
    }

    unsigned short SmartElectricEnergyMeter::Proxy::getEchoClassCode()
    {
        return mEchoClassCode;
    }
    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetOperationStatus(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_OPERATION_STATUS, edt);
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetInstallationLocation(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_INSTALLATION_LOCATION, edt);
    }
    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetCurrentLimitSetting(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_CURRENT_LIMIT_SETTING, edt);
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetPowerSavingOperationSetting(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_POWER_SAVING_OPERATION_SETTING, edt);
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetRemoteControlSetting(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_REMOTE_CONTROL_SETTING, edt);
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetCurrentTimeSetting(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_CURRENT_TIME_SETTING, edt);
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetCurrentDateSetting(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_CURRENT_DATE_SETTING, edt);
    }

    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetPowerLimitSetting(
        std::vector<unsigned char> edt)
    {
        return reqSetProperty(EPC_POWER_LIMIT_SETTING, edt);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformOperationStatus()
    {
        return reqInformProperty(EPC_OPERATION_STATUS);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetOperationStatus()
    {
        return reqGetProperty(EPC_OPERATION_STATUS);
    }
    void SmartElectricEnergyMeter::Receiver::onGetOperationStatus(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onSetOperationStatus(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv,
        EchoProperty &property, bool success)
    {
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getOperationStatus()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    bool SmartElectricEnergyMeter::Proxy::setInstallationLocation(
        std::vector<unsigned char> &edt)
    {
        return false;
    }

    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getInstallationLocation()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getFaultStatus()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getFaultStatus()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getManufacturerCode()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getMeasuredCumulativeAmountOfElectricEnergyNormalDirection()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::Proxy::getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }

    /********************************************************************************************************/
    /*******************************************************************************************************/
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformInstallationLocation()
    {
        return reqInformProperty(EPC_INSTALLATION_LOCATION);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformStandardVersionInformation()
    {
        return reqInformProperty(EPC_STANDARD_VERSION_INFORMATION);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformIdentificationNumber()
    {
        return reqInformProperty(EPC_IDENTIFICATION_NUMBER);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredInstantaneousPowerConsumption()
    {
        return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredCumulativePowerConsumption()
    {
        return reqInformProperty(EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformManufacturersFaultCode()
    {
        return reqInformProperty(EPC_MANUFACTURERS_FAULT_CODE);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCurrentLimitSetting()
    {
        return reqInformProperty(EPC_CURRENT_LIMIT_SETTING);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformFaultStatus()
    {
        return reqInformProperty(EPC_FAULT_STATUS);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformFaultDescription()
    {
        return reqInformProperty(EPC_FAULT_DESCRIPTION);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformManufacturerCode()
    {
        return reqInformProperty(EPC_MANUFACTURER_CODE);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformBusinessFacilityCode()
    {
        return reqInformProperty(EPC_BUSINESS_FACILITY_CODE);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformProductCode()
    {
        return reqInformProperty(EPC_PRODUCT_CODE);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformProductionNumber()
    {
        return reqInformProperty(EPC_PRODUCTION_NUMBER);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformProductionDate()
    {
        return reqInformProperty(EPC_PRODUCTION_DATE);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformPowerSavingOperationSetting()
    {
        return reqInformProperty(EPC_POWER_SAVING_OPERATION_SETTING);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformRemoteControlSetting()
    {
        return reqInformProperty(EPC_REMOTE_CONTROL_SETTING);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCurrentTimeSetting()
    {
        return reqInformProperty(EPC_CURRENT_TIME_SETTING);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCurrentDateSetting()
    {
        return reqInformProperty(EPC_CURRENT_DATE_SETTING);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformPowerLimitSetting()
    {
        return reqInformProperty(EPC_POWER_LIMIT_SETTING);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCumulativeOperatingTime()
    {
        return reqInformProperty(EPC_CUMULATIVE_OPERATING_TIME);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformStatusChangeAnnouncementPropertyMap()
    {
        return reqInformProperty(EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformSetPropertyMap()
    {
        return reqInformProperty(EPC_SET_PROPERTY_MAP);
    }

    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformGetPropertyMap()
    {
        return reqInformProperty(EPC_GET_PROPERTY_MAP);
    }
    bool SmartElectricEnergyMeter::isValidElectricEnergyMeterClassification(std::vector<unsigned char> &edt)
    {
        if (edt.empty() || edt.size() != 1)
            return false;
        return true;
    }

    bool SmartElectricEnergyMeter::isValidOwnerClassification(std::vector<unsigned char> &edt)
    {
        // if(edt.empty() || edt.size()!=1)
        //     return false;
        // return true;
        return (edt.empty() || edt.size() != 1) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidPhasesAndWiresSettingStatus(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 1) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidCompositeTransformationRatio(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 4) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMultiplyingFactorForCompositeTransformationRatio(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 1) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMeterTypeCertificationNumber(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 10) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidYearAndMonthOfInspectionExpiry(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 6) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 1) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMeasuredCumulativeAmountOfElectricEnergyNormalDirection(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 4) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 1) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 194) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 4) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 194) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 1) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMeasuredInstantaneousElectricEnergy(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 4) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMeasuredInstantaneousCurrents(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 4) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidMeasuredInstantaneousVoltages(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 4) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 11) ? false : true;
    }
    bool SmartElectricEnergyMeter::isValidCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection(std::vector<unsigned char> &edt)
    {
        return (edt.empty() || edt.size() != 11) ? false : true;
    }
    bool SmartElectricEnergyMeter::setElectricEnergyMeterClassification(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool SmartElectricEnergyMeter::setOwnerClassification(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool SmartElectricEnergyMeter::setYearAndMonthOfInspectionExpiry(std::vector<unsigned char> &edt)
    {
        return false;
    }
    bool SmartElectricEnergyMeter::setDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::vector<unsigned char> &edt)
    {
        return false;
    }
    void SmartElectricEnergyMeter::Receiver::onSetElectricEnergyMeterClassification(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onSetOwnerClassification(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onSetYearAndMonthOfInspectionExpiry(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onSetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetElectricEnergyMeterClassification(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetOwnerClassification(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetPhasesAndWiresSettingStatus(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetCompositeTransformationRatio(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMultiplyingFactorForCompositeTransformationRatio(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMeterTypeCertificationNumber(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetYearAndMonthOfInspectionExpiry(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMeasuredCumulativeAmountOfElectricEnergyNormalDirection(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMeasuredInstantaneousElectricEnergy(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMeasuredInstantaneousCurrents(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetMeasuredInstantaneousVoltages(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    void SmartElectricEnergyMeter::Receiver::onGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection(
        std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success)
    {
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getPhasesAndWiresSettingStatus()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getCompositeTransformationRatio()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMultiplyingFactorForCompositeTransformationRatio()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMeterTypeCertificationNumber()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getYearAndMonthOfInspectionExpiry()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMeasuredCumulativeAmountOfElectricEnergyNormalDirection()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMeasuredCumulativeAmountsOfElectricEnergyReverseDirection()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMeasuredInstantaneousElectricEnergy()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMeasuredInstantaneousCurrents()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getMeasuredInstantaneousVoltages()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection()
    {
        return std::shared_ptr<std::vector<unsigned char>>();
    }
    // std::shared_ptr<std::vector<unsigned char>> SmartElectricEnergyMeter::getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection()
    // {
    //     return std::shared_ptr<std::vector<unsigned char>>();
    // }
    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetElectricEnergyMeterClassification(std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION, edt);
    }
    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetOwnerClassification(std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_OWNER_CLASSIFICATION, edt);
    }
    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetYearAndMonthOfInspectionExpiry(std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY, edt);
    }
    SmartElectricEnergyMeter::Setter &SmartElectricEnergyMeter::Setter::reqSetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::vector<unsigned char> &edt)
    {
        return reqSetProperty(EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED, edt);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetElectricEnergyMeterClassification()
    {
        return reqGetProperty(EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetOwnerClassification()
    {
        return reqGetProperty(EPC_OWNER_CLASSIFICATION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetPhasesAndWiresSettingStatus()
    {
        return reqGetProperty(EPC_PHASES_AND_WIRES_SETTING_STATUS);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetCompositeTransformationRatio()
    {
        return reqGetProperty(EPC_COMPOSITE_TRANSFORMATION_RATIO);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMultiplyingFactorForCompositeTransformationRatio()
    {
        return reqGetProperty(EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMeterTypeCertificationNumber()
    {
        return reqGetProperty(EPC_METER_TYPE_CERTIFICATION_NUMBER);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetYearAndMonthOfInspectionExpiry()
    {
        return reqGetProperty(EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy()
    {
        return reqGetProperty(EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMeasuredCumulativeAmountOfElectricEnergyNormalDirection()
    {
        return reqGetProperty(EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections()
    {
        return reqGetProperty(EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection()
    {
        return reqGetProperty(EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMeasuredCumulativeAmountsOfElectricEnergyReverseDirection()
    {
        return reqGetProperty(EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection()
    {
        return reqGetProperty(EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved()
    {
        return reqGetProperty(EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMeasuredInstantaneousElectricEnergy()
    {
        return reqGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMeasuredInstantaneousCurrents()
    {
        return reqGetProperty(EPC_MEASURED_INSTANTANEOUS_CURRENTS);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetMeasuredInstantaneousVoltages()
    {
        return reqGetProperty(EPC_MEASURED_INSTANTANEOUS_VOLTAGES);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection()
    {
        return reqGetProperty(EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION);
    }
    SmartElectricEnergyMeter::Getter &SmartElectricEnergyMeter::Getter::reqGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection()
    {
        return reqGetProperty(EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformElectricEnergyMeterClassification()
    {
        return reqInformProperty(EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformOwnerClassification()
    {
        return reqInformProperty(EPC_OWNER_CLASSIFICATION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformPhasesAndWiresSettingStatus()
    {
        return reqInformProperty(EPC_PHASES_AND_WIRES_SETTING_STATUS);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCompositeTransformationRatio()
    {
        return reqInformProperty(EPC_COMPOSITE_TRANSFORMATION_RATIO);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMultiplyingFactorForCompositeTransformationRatio()
    {
        return reqInformProperty(EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeterTypeCertificationNumber()
    {
        return reqInformProperty(EPC_METER_TYPE_CERTIFICATION_NUMBER);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformYearAndMonthOfInspectionExpiry()
    {
        return reqInformProperty(EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy()
    {
        return reqInformProperty(EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredCumulativeAmountOfElectricEnergyNormalDirection()
    {
        return reqInformProperty(EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections()
    {
        return reqInformProperty(EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection()
    {
        return reqInformProperty(EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredCumulativeAmountsOfElectricEnergyReverseDirection()
    {
        return reqInformProperty(EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection()
    {
        return reqInformProperty(EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved()
    {
        return reqInformProperty(EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredInstantaneousElectricEnergy()
    {
        return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredInstantaneousCurrents()
    {
        return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_CURRENTS);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformMeasuredInstantaneousVoltages()
    {
        return reqInformProperty(EPC_MEASURED_INSTANTANEOUS_VOLTAGES);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection()
    {
        return reqInformProperty(EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION);
    }
    SmartElectricEnergyMeter::Informer &SmartElectricEnergyMeter::Informer::reqInformCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection()
    {
        return reqInformProperty(EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION);
    }

};