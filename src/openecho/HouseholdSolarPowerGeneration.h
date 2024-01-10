// #ifndef HOUSEHOLDSOLARPOWERGENERATION_H_
// #define HOUSEHOLDSOLARPOWERGENERATION_H_
// #include "EchoObject.h"
// namespace sonycsl_openecho
// {

//     class HouseholdSolarPowerGeneration : public EchoObject
//     {

//     public:
//         class Receiver;
//         class Setter;
//         class Getter;
//         class Informer;
//         class InformerC;
//         class Proxy;

//     public:
//         static const unsigned char EPC_OPERATION_STATUS;
// 		static const unsigned char EPC_INSTALLATION_LOCATION;
// 		static const unsigned char EPC_STANDARD_VERSION_INFORMATION;
// 		static const unsigned char EPC_IDENTIFICATION_NUMBER;
// 		static const unsigned char EPC_MEASURED_INSTANTANEOUS_POWER_CONSUMPTION;
// 		static const unsigned char EPC_MEASURED_CUMULATIVE_POWER_CONSUMPTION;
// 		static const unsigned char EPC_MANUFACTURERS_FAULT_CODE;
// 		static const unsigned char EPC_CURRENT_LIMIT_SETTING;
// 		static const unsigned char EPC_FAULT_STATUS;
// 		static const unsigned char EPC_FAULT_DESCRIPTION;
// 		static const unsigned char EPC_MANUFACTURER_CODE;
// 		static const unsigned char EPC_BUSINESS_FACILITY_CODE;
// 		static const unsigned char EPC_PRODUCT_CODE;
// 		static const unsigned char EPC_PRODUCTION_NUMBER;
// 		static const unsigned char EPC_PRODUCTION_DATE;
// 		static const unsigned char EPC_POWER_SAVING_OPERATION_SETTING;
// 		static const unsigned char EPC_REMOTE_CONTROL_SETTING;
// 		static const unsigned char EPC_CURRENT_TIME_SETTING;
// 		static const unsigned char EPC_CURRENT_DATE_SETTING;
// 		static const unsigned char EPC_POWER_LIMIT_SETTING;
// 		static const unsigned char EPC_CUMULATIVE_OPERATING_TIME;
// 		static const unsigned char EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP;
// 		static const unsigned char EPC_SET_PROPERTY_MAP;
// 		static const unsigned char EPC_GET_PROPERTY_MAP;
// 		static const unsigned char EPC_OUTPUT_POWER_CONTROL_SETTING_1;
// 		static const unsigned char EPC_OUTPUT_POWER_CONTROL_SETTING_2;
// 		static const unsigned char EPC_CONTROL_PURCHASE_OF_EXCWSS_ELECTRICITY_SETTING;
// 		static const unsigned char EPC_OUTPUT_POWER_COTROLLING_SCHEDULE;
// 		static const unsigned char EPC_NEXT_ACCESS_DATE_AND_TIME;
// 		static const unsigned char EPC_OUTPUT_POWER_CHANGE_TIME_SETTING_VALUE;
// 		static const unsigned char EPC_UPPER_LIMIT_CLIP_SETTING_VALUE;
// 		static const unsigned char EPC_OPERATION_POWER_FACTOR_SETTING_VALUE;
// 		static const unsigned char EPC_FIT_CONTRACT_TYPE;
// 		static const unsigned char EPC_SELF_CONSUMPTION_MODE;
// 		static const unsigned char EPC_CAPACITY_APPROVED_BY_EQUIPMENT;
// 		static const unsigned char EPC_CONVERSION_COEFFICIENT;
//         static const unsigned char EPC_SYSTEM_INTERCONNECTION_INFORMATION;
//         static const unsigned char EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION;
//         static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION;
//         static const unsigned char EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION;
//         static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD;
//         static const unsigned char EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD;
//         static const unsigned char EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1;
//         static const unsigned char EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2;
//         static const unsigned char EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD;
//         static const unsigned char EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED;
//         static const unsigned char EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT;

//     protected:
//         unsigned char mEchoInstanceCode;
//         std::shared_ptr<std::vector<unsigned char>> mStandardVersionInformation;

//     public:
//         HouseholdSolarPowerGeneration();
//         virtual ~HouseholdSolarPowerGeneration();

//     public:
//         virtual unsigned char getInstanceCode();
//         virtual void onNew(std::shared_ptr<EchoObject> eoj);
// 		virtual void allocateSelfDeviceInstanceCode();

//         virtual bool setProperty(EchoProperty &property);
//         virtual std::shared_ptr<std::vector<unsigned char>> getProperty(unsigned char epc);
//         virtual bool isValidProperty(EchoProperty &property);
//         HouseholdSolarPowerGeneration::Setter set();
//         HouseholdSolarPowerGeneration::Setter set(bool responseRequired);
//         HouseholdSolarPowerGeneration::Getter get();
//         HouseholdSolarPowerGeneration::Informer inform();

//     protected:
//         HouseholdSolarPowerGeneration::Informer inform(bool multicast);
//         HouseholdSolarPowerGeneration::InformerC informC(std::string address);
//         virtual void setupPropertyMaps();
//         virtual bool setOperationStatus(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getOperationStatus() = 0;
// 		virtual bool isValidOperationStatus(std::vector<unsigned char> &edt);
// 		virtual bool setInstallationLocation(std::vector<unsigned char> &edt) = 0;
// 		virtual std::shared_ptr<std::vector<unsigned char>> getInstallationLocation() = 0;
// 		virtual bool isValidInstallationLocation(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getStandardVersionInformation();
// 		virtual bool isValidStandardVersionInformation(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getIdentificationNumber();
// 		virtual bool isValidIdentificationNumber(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredInstantaneousPowerConsumption();
// 		virtual bool isValidMeasuredInstantaneousPowerConsumption(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativePowerConsumption();
// 		virtual bool isValidMeasuredCumulativePowerConsumption(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getManufacturersFaultCode();
// 		virtual bool isValidManufacturersFaultCode(std::vector<unsigned char> &edt);
// 		virtual bool setCurrentLimitSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getCurrentLimitSetting();
// 		virtual bool isValidCurrentLimitSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getFaultStatus() = 0;
// 		virtual bool isValidFaultStatus(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getFaultDescription();
// 		virtual bool isValidFaultDescription(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getManufacturerCode() = 0;
// 		virtual bool isValidManufacturerCode(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getBusinessFacilityCode();
// 		virtual bool isValidBusinessFacilityCode(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getProductCode();
// 		virtual bool isValidProductCode(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getProductionNumber();
// 		virtual bool isValidProductionNumber(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getProductionDate();
// 		virtual bool isValidProductionDate(std::vector<unsigned char> &edt);
// 		virtual bool setPowerSavingOperationSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getPowerSavingOperationSetting();
// 		virtual bool isValidPowerSavingOperationSetting(std::vector<unsigned char> &edt);
// 		virtual bool setRemoteControlSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getRemoteControlSetting();
// 		virtual bool isValidRemoteControlSetting(std::vector<unsigned char> &edt);
// 		virtual bool setCurrentTimeSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getCurrentTimeSetting();
// 		virtual bool isValidCurrentTimeSetting(std::vector<unsigned char> &edt);
// 		virtual bool setCurrentDateSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getCurrentDateSetting();
// 		virtual bool isValidCurrentDateSetting(std::vector<unsigned char> &edt);
// 		virtual bool setPowerLimitSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getPowerLimitSetting();
// 		virtual bool isValidPowerLimitSetting(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getCumulativeOperatingTime();
// 		virtual bool isValidCumulativeOperatingTime(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getStatusChangeAnnouncementPropertyMap();
// 		virtual bool isValidStatusChangeAnnouncementPropertyMap(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getSetPropertyMap();
// 		virtual bool isValidSetPropertyMap(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getGetPropertyMap();
// 		virtual bool isValidGetPropertyMap(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getSystemInterconnectedType();
//         virtual bool isValidSystemInterconnEctedType(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountOfElectricityGenerated()=0;
//         virtual bool isValidMeasuredCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredInstantaneousAmountOfElectricityGenerated()=0;
//         virtual bool isValidMeasuredInstantaneousAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
//         virtual bool isValidResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
//         virtual bool isValidResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountOfElectricitySold();
//         virtual bool isValidMeasuredCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getPowerGenerationOutputLimitSetting1();
//         virtual std::shared_ptr<std::vector<unsigned char>> getPowerGenerationOutputLimitSetting2();
//         std::shared_ptr<std::vector<unsigned char>> getLimitSettingForTheAmountOfElectricitySold();
//         virtual std::shared_ptr<std::vector<unsigned char>> getRatedPowerGenerationOutputSystemInterconnected();
//         virtual bool isValidPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt);
//         virtual bool isValidPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt);
//         virtual bool isValidRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt);
//         virtual bool isValidLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getRatedPowerGenerationOutputIndependent();
//         virtual bool isValidRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt);
//         virtual std::shared_ptr<std::vector<unsigned char>> getRatedPowerGenerationOutputIndependent();
//         virtual bool setResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
//         virtual bool setResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
//         virtual bool setPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt); 
//         virtual bool setPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt);
//         virtual bool setLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
//         virtual bool setRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt);
//         virtual bool setRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt);

//     public:
//         class Receiver : public EchoObject::Receiver
//         {
//         public:
//             Receiver();
//             virtual ~Receiver();

//         protected:
//             virtual bool onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual bool onInformProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property);
//             virtual void onSetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetInstallationLocation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetCurrentLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetPowerSavingOperationSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetRemoteControlSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetCurrentTimeSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetCurrentDateSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onSetPowerLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetInstallationLocation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetStandardVersionInformation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetIdentificationNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetMeasuredInstantaneousPowerConsumption(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetMeasuredCumulativePowerConsumption(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetManufacturersFaultCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetCurrentLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetFaultStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetFaultDescription(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetManufacturerCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetBusinessFacilityCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetProductCode(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetProductionNumber(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetProductionDate(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetPowerSavingOperationSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetRemoteControlSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetCurrentTimeSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetCurrentDateSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetPowerLimitSetting(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetCumulativeOperatingTime(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetStatusChangeAnnouncementPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetSetPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
// 			virtual void onGetGetPropertyMap(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onSetResettingCumulativeAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onSetResettingCumulativeAmountOfElectricityGenerated(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onSetPowerGenerationOutputLimitSetting1(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);  
//             virtual void onSetPowerGenerationOutputLimitSetting2(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onSetLimitSettingForTheAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);  
//             virtual void onSetRatedPowerGenerationOutputSystemInterconnected(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success); 
//             virtual void onSetRatedPowerGenerationOutputIndependent(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success); 
//             virtual void onGetSystemInterconnEctedType(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetMeasuredInstantaneousAmountOfElectricityGenerated(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetMeasuredCumulativeAmountOfElectricityGenerated(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetMeasuredCumulativeAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetPowerGenerationOutputLimitSetting1(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetPowerGenerationOutputLimitSetting2(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetLimitSettingForTheAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetRatedPowerGenerationOutputSystemInterconnected(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
//             virtual void onGetRatedPowerGenerationOutputIndependent(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);

//         };

//         class Setter : public EchoObject::Setter
//         {
//         public:
//             Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode, std::string dstEchoAddress, bool responseRequired);
// 			virtual ~Setter();
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt);
//             virtual HouseholdSolarPowerGeneration::Setter &reqSetOperationStatus(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetInstallationLocation(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetCurrentLimitSetting(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetPowerSavingOperationSetting(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetRemoteControlSetting(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetCurrentTimeSetting(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetCurrentDateSetting(std::vector<unsigned char> edt);
// 			virtual HouseholdSolarPowerGeneration::Setter &reqSetPowerLimitSetting(std::vector<unsigned char> edt);
//         };
//         class Getter : public EchoObject::Getter
//         {
//             public:
//             Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode, std::string dstEchoAddress);
// 			virtual ~Getter();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetProperty(unsigned char epc);
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetSystemInterconnEctedType();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetMeasuredInstantaneousAmountOfElectricityGenerated();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetMeasuredCumulativeAmountOfElectricityGenerated();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetMeasuredCumulativeAmountOfElectricitySold();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetPowerGenerationOutputLimitSetting1();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetPowerGenerationOutputLimitSetting2();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetLimitSettingForTheAmountOfElectricitySold();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetRatedPowerGenerationOutputSystemInterconnected();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetRatedPowerGenerationOutputIndependent();
//             virtual HouseholdSolarPowerGeneration::Getter &reqGetOperationStatus();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetInstallationLocation();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetStandardVersionInformation();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetIdentificationNumber();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetMeasuredInstantaneousPowerConsumption();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetMeasuredCumulativePowerConsumption();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetManufacturersFaultCode();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetCurrentLimitSetting();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetFaultStatus();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetFaultDescription();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetManufacturerCode();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetBusinessFacilityCode();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetProductCode();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetProductionNumber();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetProductionDate();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetPowerSavingOperationSetting();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetRemoteControlSetting();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetCurrentTimeSetting();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetCurrentDateSetting();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetPowerLimitSetting();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetCumulativeOperatingTime();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetStatusChangeAnnouncementPropertyMap();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetSetPropertyMap();
// 			virtual HouseholdSolarPowerGeneration::Getter &reqGetGetPropertyMap();
//         };
//         class Informer : public EchoObject::Informer
// 		{
// 		public:
// 			Informer(unsigned short echoClassCode, unsigned char echoInstanceCode, std::string dstEchoAddress, bool isSelfObject);
// 			virtual ~Informer();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformProperty(unsigned char epc);
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformSystemInterconnEctedType();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformMeasuredInstantaneousAmountOfElectricityGenerated();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformMeasuredCumulativeAmountOfElectricityGenerated();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformMeasuredCumulativeAmountOfElectricitySold();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformPowerGenerationOutputLimitSetting1();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformPowerGenerationOutputLimitSetting2();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformLimitSettingForTheAmountOfElectricitySold();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformRatedPowerGenerationOutputSystemInterconnected();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformRatedPowerGenerationOutputIndependent();
//             virtual HouseholdSolarPowerGeneration::Informer &reqInformOperationStatus();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformInstallationLocation();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformStandardVersionInformation();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformIdentificationNumber();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformMeasuredInstantaneousPowerConsumption();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformMeasuredCumulativePowerConsumption();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformManufacturersFaultCode();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformCurrentLimitSetting();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformFaultStatus();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformFaultDescription();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformManufacturerCode();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformBusinessFacilityCode();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformProductCode();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformProductionNumber();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformProductionDate();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformPowerSavingOperationSetting();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformRemoteControlSetting();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformCurrentTimeSetting();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformCurrentDateSetting();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformPowerLimitSetting();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformCumulativeOperatingTime();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformStatusChangeAnnouncementPropertyMap();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformSetPropertyMap();
// 			virtual HouseholdSolarPowerGeneration::Informer &reqInformGetPropertyMap();
//         };
//         class InformerC : public EchoObject::InformerC
// 		{
// 		public:
// 			InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode, std::string dstEchoAddress);
// 			virtual ~InformerC();
// 			virtual HouseholdSolarPowerGeneration::InformerC &reqInformProperty(unsigned char epc);
// 		};


//     };
//     class HouseholdSolarPowerGeneration::Proxy : public HouseholdSolarPowerGeneration
// 	{
// 	protected:
// 		unsigned short mEchoClassCode;

// 	public:
// 		Proxy(unsigned short echoClassCode, unsigned char echoInstanceCode);
// 		virtual ~Proxy();

// 		virtual unsigned char getInstanceCode();
// 		virtual unsigned short getEchoClassCode();

// 		virtual std::shared_ptr<std::vector<unsigned char>> getOperationStatus();
// 		virtual bool setInstallationLocation(std::vector<unsigned char> &edt);
// 		virtual std::shared_ptr<std::vector<unsigned char>> getInstallationLocation();
// 		virtual std::shared_ptr<std::vector<unsigned char>> getFaultStatus();
// 		virtual std::shared_ptr<std::vector<unsigned char>> getManufacturerCode();
// 	};

// };
// #endif /* HouseholdSolarPowerGeneration_H_ */