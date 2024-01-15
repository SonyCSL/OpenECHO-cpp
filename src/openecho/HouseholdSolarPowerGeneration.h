#ifndef HouseholdSolarPowerGeneration_H_
#define HouseholdSolarPowerGeneration_H_

#include "EchoObject.h"
#include "DeviceObject.h"
namespace sonycsl_openecho
{

    class HouseholdSolarPowerGeneration : public DeviceObject
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
        static const unsigned char EPC_SYSTEM_INTERCONNECTION_INFORMATION;
        static const unsigned char EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION;
        static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION;
        static const unsigned char EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION;
        static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD;
        static const unsigned char EPC_RESETTING_CUMULATIVE_AMOUT_OF_ELECTRICITY_SOLD;
        static const unsigned char EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_1;
        static const unsigned char EPC_POWER_GENERATION_OUTPUT_LIMIT_SETTING_2;
        static const unsigned char EPC_LIMIT_SETTING_FOR_AMOUNT_OF_ELECTRICITY_SOLD;
        static const unsigned char EPC_RATED_POWER_GENERATION_OUTPUT_INTERCONNECTED;
        static const unsigned char EPC_RATED_POWER_GENERATION_OUTPUT_INDEPENDENT;

    protected:
        unsigned char mEchoInstanceCode;
        std::shared_ptr<std::vector<unsigned char>> mStandardVersionInformation;

    public:
        HouseholdSolarPowerGeneration();
        virtual ~HouseholdSolarPowerGeneration();

    public:
        virtual unsigned char getInstanceCode();
        virtual void onNew(std::shared_ptr<DeviceObject> eoj);
        virtual void allocateSelfDeviceInstanceCode();

        virtual bool setProperty(EchoProperty &property);
        virtual std::shared_ptr<std::vector<unsigned char>> getProperty(unsigned char epc);
        virtual bool isValidProperty(EchoProperty &property);
        HouseholdSolarPowerGeneration::Setter set();
        HouseholdSolarPowerGeneration::Setter set(bool responseRequired);
        HouseholdSolarPowerGeneration::Getter get();
        HouseholdSolarPowerGeneration::Informer inform();

    protected:
        HouseholdSolarPowerGeneration::Informer inform(bool multicast);
        HouseholdSolarPowerGeneration::InformerC informC(std::string address);
        virtual void setupPropertyMaps();
        virtual bool setOperationStatus(std::vector<unsigned char> &edt);
		virtual std::shared_ptr<std::vector<unsigned char>> getOperationStatus() = 0;
        virtual bool isValidSystemInterconnEctedType(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountOfElectricityGenerated()=0;
        virtual bool isValidMeasuredCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredInstantaneousAmountOfElectricityGenerated()=0;
        virtual bool isValidMeasuredInstantaneousAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
        virtual bool isValidResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
        virtual bool isValidResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getMeasuredCumulativeAmountOfElectricitySold();
        virtual bool isValidMeasuredCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getPowerGenerationOutputLimitSetting1();
        virtual std::shared_ptr<std::vector<unsigned char>> getPowerGenerationOutputLimitSetting2();
		virtual std::shared_ptr<std::vector<unsigned char>> getSystemInterconnectedType();
        virtual std::shared_ptr<std::vector<unsigned char>> getLimitSettingForTheAmountOfElectricitySold();
        virtual std::shared_ptr<std::vector<unsigned char>> getRatedPowerGenerationOutputSystemInterconnected();
        virtual bool isValidPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt);
        virtual bool isValidPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt);
        virtual bool isValidRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt);
        virtual bool isValidLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
        virtual std::shared_ptr<std::vector<unsigned char>> getRatedPowerGenerationOutputIndependent();
        virtual bool isValidRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt);
        virtual bool setResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
        virtual bool setResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
        virtual bool setPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt); 
        virtual bool setPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt);
        virtual bool setLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
        virtual bool setRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt);
        virtual bool setRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt);

    public:
        class Receiver : public EchoObject::Receiver
        {
        public:
            Receiver();
            virtual ~Receiver();

        protected:
            virtual bool onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
            virtual void onSetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
            virtual void onSetResettingCumulativeAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetResettingCumulativeAmountOfElectricityGenerated(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetPowerGenerationOutputLimitSetting1(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);  
            virtual void onSetPowerGenerationOutputLimitSetting2(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onSetLimitSettingForTheAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);  
            virtual void onSetRatedPowerGenerationOutputSystemInterconnected(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success); 
            virtual void onSetRatedPowerGenerationOutputIndependent(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success); 
            virtual void onGetSystemInterconnEctedType(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredInstantaneousAmountOfElectricityGenerated(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredCumulativeAmountOfElectricityGenerated(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetMeasuredCumulativeAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetPowerGenerationOutputLimitSetting1(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetPowerGenerationOutputLimitSetting2(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetLimitSettingForTheAmountOfElectricitySold(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetRatedPowerGenerationOutputSystemInterconnected(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);
            virtual void onGetRatedPowerGenerationOutputIndependent(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty &property, bool success);

        };

        class Setter : public EchoObject::Setter
        {
        public:
            Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode, std::string dstEchoAddress, bool responseRequired);
			virtual ~Setter();
            virtual HouseholdSolarPowerGeneration::Setter& reqSetLimitSettingForTheAmountOfElectricitySold(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetResettingCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetResettingCumulativeAmountOfElectricitySold(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetPowerGenerationOutputLimitSetting1(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetPowerGenerationOutputLimitSetting2(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetRatedPowerGenerationOutputSystemInterconnected(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetRatedPowerGenerationOutputIndependent(std::vector<unsigned char> &edt);
            virtual HouseholdSolarPowerGeneration::Setter& reqSetOperationStatus(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetInstallationLocation(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetCurrentLimitSetting(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetPowerSavingOperationSetting(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetRemoteControlSetting(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetCurrentTimeSetting(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetCurrentDateSetting(std::vector<unsigned char> edt);
			virtual HouseholdSolarPowerGeneration::Setter& reqSetPowerLimitSetting(std::vector<unsigned char> edt);
        };
        class Getter : public EchoObject::Getter
        {
            public:
            Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode, std::string dstEchoAddress);
			virtual ~Getter();
			virtual HouseholdSolarPowerGeneration::Getter& reqGetProperty(unsigned char epc);
            virtual HouseholdSolarPowerGeneration::Getter& reqGetOperationStatus();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetSystemInterconnEctedType();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetMeasuredInstantaneousAmountOfElectricityGenerated();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetMeasuredCumulativeAmountOfElectricityGenerated();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetMeasuredCumulativeAmountOfElectricitySold();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetPowerGenerationOutputLimitSetting1();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetPowerGenerationOutputLimitSetting2();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetLimitSettingForTheAmountOfElectricitySold();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetRatedPowerGenerationOutputSystemInterconnected();
            virtual HouseholdSolarPowerGeneration::Getter& reqGetRatedPowerGenerationOutputIndependent();
        };
        class Informer : public EchoObject::Informer
		{
		public:
			Informer(unsigned short echoClassCode, unsigned char echoInstanceCode, std::string dstEchoAddress, bool isSelfObject);
			virtual ~Informer();
			virtual HouseholdSolarPowerGeneration::Informer& reqInformProperty(unsigned char epc);
            virtual HouseholdSolarPowerGeneration::Informer& reqInformOperationStatus();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformSystemInterconnEctedType();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformMeasuredInstantaneousAmountOfElectricityGenerated();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformMeasuredCumulativeAmountOfElectricityGenerated();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformMeasuredCumulativeAmountOfElectricitySold();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformPowerGenerationOutputLimitSetting1();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformPowerGenerationOutputLimitSetting2();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformLimitSettingForTheAmountOfElectricitySold();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformRatedPowerGenerationOutputSystemInterconnected();
            virtual HouseholdSolarPowerGeneration::Informer& reqInformRatedPowerGenerationOutputIndependent();
            
        };
        class InformerC : public EchoObject::InformerC
		{
		public:
			InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode, std::string dstEchoAddress);
			virtual ~InformerC();
			// virtual HouseholdSolarPowerGeneration::InformerC &reqInformProperty(unsigned char epc);
		};


    };
    class HouseholdSolarPowerGeneration::Proxy : public HouseholdSolarPowerGeneration
	{
	protected:
		unsigned short mEchoClassCode;

	public:
		Proxy(unsigned short echoClassCode, unsigned char echoInstanceCode);
		virtual ~Proxy();

		virtual unsigned char getInstanceCode();
		virtual unsigned short getEchoClassCode();

		virtual std::shared_ptr<std::vector<unsigned char>> getOperationStatus();
		virtual bool setInstallationLocation(std::vector<unsigned char> &edt);
		virtual std::shared_ptr<std::vector<unsigned char>> getInstallationLocation();
		virtual std::shared_ptr<std::vector<unsigned char>> getFaultStatus();
		virtual std::shared_ptr<std::vector<unsigned char>> getManufacturerCode();
	};

};
#endif /* HouseholdSolarPowerGeneration_H_ */