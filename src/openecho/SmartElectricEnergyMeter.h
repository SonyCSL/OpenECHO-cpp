#ifndef SmartElectricEnergyMeter_H_
#define SmartElectricEnergyMeter_H_

#include "EchoObject.h"
#include "DeviceObject.h"
namespace sonycsl_openecho
{
    class SmartElectricEnergyMeter : public DeviceObject
    {
    public:
        class Receiver;
        class Setter;
        class Getter;
        class Informer;
        class InformerC;
        class Proxy;

    public:
        static const short ECHO_CLASS_CODE;
        static const unsigned char EPC_OPERATION_STATUS;
        static const unsigned char EPC_ELECTRIC_ENERGY_METER_CLASSIFICATION;
        static const unsigned char EPC_OWNER_CLASSIFICATION;
        static const unsigned char EPC_PHASES_AND_WIRES_SETTING_STATUS;
        static const unsigned char EPC_COMPOSITE_TRANSFORMATION_RATIO;
        static const unsigned char EPC_MULTIPLYING_FACTOR_FOR_COMPOSITE_TRANSFORMATION_RATIO;
        static const unsigned char EPC_METER_TYPE_CERTIFICATION_NUMBER;
        static const unsigned char EPC_YEAR_AND_MONTH_OF_INSPECTION_EXPIRY;
        static const unsigned char EPC_NUMBER_OF_EFFECTIVE_DIGITS_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY;
        static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUNT_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION;
        static const unsigned char EPC_UNIT_FOR_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_AND_REVERSE_DIRECTIONS;
        static const unsigned char EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_NORMAL_DIRECTION;
        static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION;
        static const unsigned char EPC_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_REVERSE_DIRECTION;
        static const unsigned char EPC_DAY_FOR_WHICH_THE_HISTORICAL_DATA_OF_MEASURED_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_IS_TO_BE_RETRIEVED;
        static const unsigned char EPC_MEASURED_INSTANTANEOUS_ELECTRIC_ENERGY;
        static const unsigned char EPC_MEASURED_INSTANTANEOUS_CURRENTS;
        static const unsigned char EPC_MEASURED_INSTANTANEOUS_VOLTAGES;
        static const unsigned char EPC_GET_PROPERTY_MAP;
        static const unsigned char EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_NORMAL_DIRECTION;
        static const unsigned char EPC_CUMULATIVE_AMOUNTS_OF_ELECTRIC_ENERGY_MEASURED_AT_FIXED_TIME_REVERSE_DIRECTION;

    protected:
        unsigned char mEchoClassCode;
        std::shared_ptr<std::vector<unsigned char>> mStandardVersionInformation;

    public:
        SmartElectricEnergyMeter();
        virtual ~SmartElectricEnergyMeter();

    public:
        virtual unsigned char getInstanceCode();
        virtual void onNew(std::shared_ptr<DeviceObject> eoj);
        virtual void allocateSelfDeviceInstanceCode();

        virtual bool setProperty(EchoProperty &property);
        virtual std::shared_ptr<std::vector<unsigned char>> getProperty(unsigned char epc);
        virtual bool isValidProperty(EchoProperty &property);
        SmartElectricEnergyMeter::Setter set();
        SmartElectricEnergyMeter::Setter set(bool responseRequired);
        SmartElectricEnergyMeter::Getter get();
        SmartElectricEnergyMeter::Informer inform();

    protected:
        SmartElectricEnergyMeter::Informer inform(bool multicast);
        SmartElectricEnergyMeter::InformerC informC(std::string address);
        virtual void setupPropertyMaps();
        virtual bool setOperationStatus(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getOperationStatus() = 0;
        virtual bool setElectricEnergyMeterClassification(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getElectricEnergyMeterClassification() = 0;
        virtual bool isValidElectricEnergyMeterClassification(std::vector<unsigned char> &edt);
        virtual bool setOwnerClassification(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getOwnerClassification() = 0;
        virtual bool isValidOwnerClassification(std::vector<unsigned char> &edt);
        virtual bool isValidPhasesAndWiresSettingStatus(std::vector<unsigned char> &edt);
        virtual bool isValidCompositeTransformationRatio(std::vector<unsigned char> &edt);
        virtual bool isValidMultiplyingFactorForCompositeTransformationRatio(std::vector<unsigned char> &edt);
        virtual bool isValidMeterTypeCertificationNumber(std::vector<unsigned char> &edt);
        virtual bool setYearAndMonthOfInspectionExpiry(std::vector<unsigned char> &edt);
        virtual bool isValidYearAndMonthOfInspectionExpiry(std::vector<unsigned char> &edt);
        virtual bool isValidNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy(std::vector<unsigned char> &edt);
        virtual bool isValidMeasuredCumulativeAmountOfElectricEnergyNormalDirection(std::vector<unsigned char> &edt);
        virtual bool isValidUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections(std::vector<unsigned char> &edt);
        virtual bool isValidHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection(std::vector<unsigned char> &edt);
        virtual bool isValidMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(std::vector<unsigned char> &edt);
        virtual bool isValidHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(std::vector<unsigned char> &edt);
        virtual bool isValidDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::vector<unsigned char> &edt);
        virtual bool isValidMeasuredInstantaneousElectricEnergy(std::vector<unsigned char> &edt);
        virtual bool isValidMeasuredInstantaneousCurrents(std::vector<unsigned char> &edt);
        virtual bool isValidMeasuredInstantaneousVoltages(std::vector<unsigned char> &edt);
        virtual bool isValidCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection(std::vector<unsigned char> &edt);
        virtual bool isValidCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getPhasesAndWiresSettingStatus() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getCompositeTransformationRatio() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getMultiplyingFactorForCompositeTransformationRatio() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getMeterTypeCertificationNumber() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getYearAndMonthOfInspectionExpiry() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy();
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountOfElectricEnergyNormalDirection();
        virtual std::shared_ptr<std::vector<unsigned char>> getUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections();
        virtual std::shared_ptr<std::vector<unsigned char>> getHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountsOfElectricEnergyReverseDirection() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection() = 0;
        virtual bool setDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredInstantaneousElectricEnergy() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredInstantaneousCurrents() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredInstantaneousVoltages() = 0;
        virtual std::shared_ptr<std::vector<unsigned char>> getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection();
        virtual std::shared_ptr<std::vector<unsigned char>> getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection() = 0;

    public:
        class Receiver : public EchoObject::Receiver
        {
        public:
            Receiver();
            virtual ~Receiver();

        protected:
            virtual bool onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetElectricEnergyMeterClassification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetOwnerClassification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetYearAndMonthOfInspectionExpiry(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetElectricEnergyMeterClassification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetOwnerClassification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetPhasesAndWiresSettingStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetCompositeTransformationRatio(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMultiplyingFactorForCompositeTransformationRatio(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeterTypeCertificationNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetYearAndMonthOfInspectionExpiry(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredCumulativeAmountOfElectricEnergyNormalDirection(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredInstantaneousElectricEnergy(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredInstantaneousCurrents(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredInstantaneousVoltages(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
        };
        class Setter : public EchoObject::Setter
        {
        public:
            Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode, std::string dstEchoAddress, bool responseRequired);
            virtual ~Setter();
            virtual SmartElectricEnergyMeter::Setter& reqSetOperationStatus(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetInstallationLocation(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetCurrentLimitSetting(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetPowerSavingOperationSetting(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetRemoteControlSetting(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetCurrentTimeSetting(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetCurrentDateSetting(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetPowerLimitSetting(std::vector<unsigned char> edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetOwnerClassification(std::vector<unsigned char> &edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetElectricEnergyMeterClassification(std::vector<unsigned char> &edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetYearAndMonthOfInspectionExpiry(std::vector<unsigned char> &edt);
            virtual SmartElectricEnergyMeter::Setter& reqSetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved(std::vector<unsigned char> &edt);
        };
        class Getter : public EchoObject::Getter
        {
        public:
            Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode, std::string dstEchoAddress);
            virtual ~Getter();
            virtual SmartElectricEnergyMeter::Getter &reqGetProperty(unsigned char epc);
            virtual SmartElectricEnergyMeter::Getter &reqGetOperationStatus();
            virtual SmartElectricEnergyMeter::Getter &reqGetInstallationLocation();
            virtual SmartElectricEnergyMeter::Getter &reqGetStandardVersionInformation();
            virtual SmartElectricEnergyMeter::Getter &reqGetIdentificationNumber();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredInstantaneousPowerConsumption();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredCumulativePowerConsumption();
            virtual SmartElectricEnergyMeter::Getter &reqGetManufacturersFaultCode();
            virtual SmartElectricEnergyMeter::Getter &reqGetCurrentLimitSetting();
            virtual SmartElectricEnergyMeter::Getter &reqGetFaultStatus();
            virtual SmartElectricEnergyMeter::Getter &reqGetFaultDescription();
            virtual SmartElectricEnergyMeter::Getter &reqGetManufacturerCode();
            virtual SmartElectricEnergyMeter::Getter &reqGetBusinessFacilityCode();
            virtual SmartElectricEnergyMeter::Getter &reqGetProductCode();
            virtual SmartElectricEnergyMeter::Getter &reqGetProductionNumber();
            virtual SmartElectricEnergyMeter::Getter &reqGetProductionDate();
            virtual SmartElectricEnergyMeter::Getter &reqGetPowerSavingOperationSetting();
            virtual SmartElectricEnergyMeter::Getter &reqGetRemoteControlSetting();
            virtual SmartElectricEnergyMeter::Getter &reqGetCurrentTimeSetting();
            virtual SmartElectricEnergyMeter::Getter &reqGetCurrentDateSetting();
            virtual SmartElectricEnergyMeter::Getter &reqGetPowerLimitSetting();
            virtual SmartElectricEnergyMeter::Getter &reqGetCumulativeOperatingTime();
            virtual SmartElectricEnergyMeter::Getter &reqGetStatusChangeAnnouncementPropertyMap();
            virtual SmartElectricEnergyMeter::Getter &reqGetSetPropertyMap();
            virtual SmartElectricEnergyMeter::Getter &reqGetGetPropertyMap();
            virtual SmartElectricEnergyMeter::Getter &reqGetElectricEnergyMeterClassification();
            virtual SmartElectricEnergyMeter::Getter &reqGetOwnerClassification();
            virtual SmartElectricEnergyMeter::Getter &reqGetPhasesAndWiresSettingStatus();
            virtual SmartElectricEnergyMeter::Getter &reqGetCompositeTransformationRatio();
            virtual SmartElectricEnergyMeter::Getter &reqGetMultiplyingFactorForCompositeTransformationRatio();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeterTypeCertificationNumber();
            virtual SmartElectricEnergyMeter::Getter &reqGetYearAndMonthOfInspectionExpiry();
            virtual SmartElectricEnergyMeter::Getter &reqGetNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredCumulativeAmountOfElectricEnergyNormalDirection();
            virtual SmartElectricEnergyMeter::Getter &reqGetUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections();
            virtual SmartElectricEnergyMeter::Getter &reqGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredCumulativeAmountsOfElectricEnergyReverseDirection();
            virtual SmartElectricEnergyMeter::Getter &reqGetHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection();
            virtual SmartElectricEnergyMeter::Getter &reqGetDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredInstantaneousElectricEnergy();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredInstantaneousCurrents();
            virtual SmartElectricEnergyMeter::Getter &reqGetMeasuredInstantaneousVoltages();
            virtual SmartElectricEnergyMeter::Getter &reqGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection();
            virtual SmartElectricEnergyMeter::Getter &reqGetCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection();
        };
        class Informer : public EchoObject::Informer
        {
        public:
            Informer(unsigned short echoClassCode, unsigned char echoInstanceCode, std::string dstEchoAddress, bool isSelfObject);
            virtual ~Informer();
            virtual SmartElectricEnergyMeter::Informer &reqInformProperty(unsigned char epc);
            virtual SmartElectricEnergyMeter::Informer &reqInformOperationStatus();
            virtual SmartElectricEnergyMeter::Informer &reqInformInstallationLocation();
            virtual SmartElectricEnergyMeter::Informer &reqInformStandardVersionInformation();
            virtual SmartElectricEnergyMeter::Informer &reqInformIdentificationNumber();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredInstantaneousPowerConsumption();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredCumulativePowerConsumption();
            virtual SmartElectricEnergyMeter::Informer &reqInformManufacturersFaultCode();
            virtual SmartElectricEnergyMeter::Informer &reqInformCurrentLimitSetting();
            virtual SmartElectricEnergyMeter::Informer &reqInformFaultStatus();
            virtual SmartElectricEnergyMeter::Informer &reqInformFaultDescription();
            virtual SmartElectricEnergyMeter::Informer &reqInformManufacturerCode();
            virtual SmartElectricEnergyMeter::Informer &reqInformBusinessFacilityCode();
            virtual SmartElectricEnergyMeter::Informer &reqInformProductCode();
            virtual SmartElectricEnergyMeter::Informer &reqInformProductionNumber();
            virtual SmartElectricEnergyMeter::Informer &reqInformGetPropertyMap();
            virtual SmartElectricEnergyMeter::Informer &reqInformProductionDate();
            virtual SmartElectricEnergyMeter::Informer &reqInformPowerSavingOperationSetting();
            virtual SmartElectricEnergyMeter::Informer &reqInformRemoteControlSetting();
            virtual SmartElectricEnergyMeter::Informer &reqInformCurrentTimeSetting();
            virtual SmartElectricEnergyMeter::Informer &reqInformCurrentDateSetting();
            virtual SmartElectricEnergyMeter::Informer &reqInformPowerLimitSetting();
            virtual SmartElectricEnergyMeter::Informer &reqInformCumulativeOperatingTime();
            virtual SmartElectricEnergyMeter::Informer &reqInformStatusChangeAnnouncementPropertyMap();
            virtual SmartElectricEnergyMeter::Informer &reqInformSetPropertyMap();
            virtual SmartElectricEnergyMeter::Informer &reqInformInformPropertyMap();
            virtual SmartElectricEnergyMeter::Informer &reqInformElectricEnergyMeterClassification();
            virtual SmartElectricEnergyMeter::Informer &reqInformOwnerClassification();
            virtual SmartElectricEnergyMeter::Informer &reqInformPhasesAndWiresSettingStatus();
            virtual SmartElectricEnergyMeter::Informer &reqInformCompositeTransformationRatio();
            virtual SmartElectricEnergyMeter::Informer &reqInformMultiplyingFactorForCompositeTransformationRatio();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeterTypeCertificationNumber();
            virtual SmartElectricEnergyMeter::Informer &reqInformYearAndMonthOfInspectionExpiry();
            virtual SmartElectricEnergyMeter::Informer &reqInformNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredCumulativeAmountOfElectricEnergyNormalDirection();
            virtual SmartElectricEnergyMeter::Informer &reqInformUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections();
            virtual SmartElectricEnergyMeter::Informer &reqInformHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyNormalDirection();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredCumulativeAmountsOfElectricEnergyReverseDirection();
            virtual SmartElectricEnergyMeter::Informer &reqInformHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyReverseDirection();
            virtual SmartElectricEnergyMeter::Informer &reqInformDayForWhichTheHistoricalDataOfMeasuredCumulativeAmountsOfElectricEnergyIsToBeRetrieved();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredInstantaneousElectricEnergy();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredInstantaneousCurrents();
            virtual SmartElectricEnergyMeter::Informer &reqInformMeasuredInstantaneousVoltages();
            virtual SmartElectricEnergyMeter::Informer &reqInformCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection();
            virtual SmartElectricEnergyMeter::Informer &reqInformCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeReverseDirection();
        };
        class InformerC : public EchoObject::InformerC
        {
        public:
            InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode, std::string dstEchoAddress);
            virtual ~InformerC();
        };
    };
    class SmartElectricEnergyMeter::Proxy : public SmartElectricEnergyMeter
    {
    protected:
        unsigned short mEchoClassCode;
        virtual std::shared_ptr<std::vector<unsigned char>> getOperationStatus();
        virtual bool setInstallationLocation(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getInstallationLocation();
        virtual std::shared_ptr<std::vector<unsigned char>> getStandardVersionInformation();
        virtual std::shared_ptr<std::vector<unsigned char>> getFaultStatus();
        virtual std::shared_ptr<std::vector<unsigned char>> getManufacturerCode();
        virtual std::shared_ptr<std::vector<unsigned char>> getNumberOfEffectiveDigitsForCumulativeAmountsOfElectricEnergy();
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountOfElectricEnergyNormalDirection();
        virtual std::shared_ptr<std::vector<unsigned char>> getUnitForCumulativeAmountsOfElectricEnergyNormalAndReverseDirections();
        virtual std::shared_ptr<std::vector<unsigned char>> getCumulativeAmountsOfElectricEnergyMeasuredAtFixedTimeNormalDirection();

    public:
        Proxy(unsigned short echoClassCode, unsigned char echoInstanceCode);
        virtual ~Proxy();
        virtual unsigned char getInstanceCode();
        virtual unsigned short getEchoClassCode();
    };
};
#endif /*SmartElectricEnergyMeter_H_*/