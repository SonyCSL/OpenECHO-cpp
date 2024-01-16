#include <iostream>
#include <memory>
#include "../openecho/OpenECHO.h"
#include "../openecho/HouseholdSolarPowerGeneration.h"
#include "../openecho/EchoProperty.h"

using namespace std;
using namespace sonycsl_openecho;
class DefaultNodeProfile : public NodeProfile
{

public:
    DefaultNodeProfile() : NodeProfile() {}
    virtual ~DefaultNodeProfile() {}

protected:
    virtual shared_ptr<vector<unsigned char>> getManufacturerCode()
    {
        return shared_ptr<vector<unsigned char>>();
    }
    virtual shared_ptr<vector<unsigned char>> getOperatingStatus()
    {
        return shared_ptr<vector<unsigned char>>();
    }
    virtual shared_ptr<vector<unsigned char>> getIdentificationNumber()
    {
        return shared_ptr<vector<unsigned char>>();
    }
};
class Household : public HouseholdSolarPowerGeneration
{
protected:
    shared_ptr<vector<unsigned char>> mStatus;
    shared_ptr<vector<unsigned char>> mLocation;
    shared_ptr<vector<unsigned char>> mFaultStatus;
    shared_ptr<vector<unsigned char>> mManufacturerCode;
    static const unsigned char EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION = 0xE0;
    static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION = 0xE1;

public:
    Household() : HouseholdSolarPowerGeneration()
    {
        mStatus = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
        mStatus.get()->push_back(0x30);
        mLocation = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
        mLocation.get()->push_back(0x00);
        mFaultStatus = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
        mFaultStatus.get()->push_back(0x42);
        mManufacturerCode = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
        mManufacturerCode.get()->push_back(0x00);
        mManufacturerCode.get()->push_back(0x00);
        mManufacturerCode.get()->push_back(0x00);
    }
    virtual ~Household() {}
    virtual unsigned short getEchoClassCode()
    {
        return 0x0279;
    }

protected:
    virtual void setupPropertyMaps()
    {
        HouseholdSolarPowerGeneration::setupPropertyMaps();
        addSetProperty(EPC_OPERATION_STATUS);
        addGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);
        addGetProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION);
    }
    virtual bool setProperty(EchoProperty& property) {

		bool success = DeviceObject::setProperty(property);
		if(success) return true;

		switch(property.epc) {
		default : return false;
		}
	}

    virtual std::shared_ptr<std::vector<unsigned char>> getProperty(
        unsigned char epc)
    {

        std::shared_ptr<std::vector<unsigned char>> edt = HouseholdSolarPowerGeneration::getProperty(epc);
        if (edt.get() != nullptr)
            return edt;

        switch (epc)
        {
        case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
            return getMeasuredInstantaneousAmountOfElectricityGenerated();
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            return getMeasuredCumulativeAmountOfElectricityGenerated();
        default:
            return std::shared_ptr<std::vector<unsigned char>>();
        }
    }

    virtual shared_ptr<vector<unsigned char>> getMeasuredInstantaneousAmountOfElectricityGenerated()
    {
        cout << "getMeasuredInstantaneousAmountOfElectricityGenerated function call" << endl;
        return NULL;
    }
    virtual shared_ptr<vector<unsigned char>> getMeasuredCumulativeAmountOfElectricityGenerated()
    {
        cout << "getMeasuredCumulativeAmountOfElectricityGenerated function call" << endl;

        return NULL;
    }

    virtual bool isValidProperty(EchoProperty &property)
    {

        bool valid = HouseholdSolarPowerGeneration::isValidProperty(property);
        if (valid)
            return true;

        switch (property.epc)
        {
        case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
            return isValidMeasuredInstantaneousAmountOfElectricityGenerated(property.edt);
        case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
            return isValidMeasuredCumulativeAmountOfElectricityGenerated(property.edt);
        default:
            return false;
        }
    }
    bool setOperationStatus(vector<unsigned char> &edt)
    {
        (*(mStatus.get()))[0] = edt.at(0);
        if (mStatus.get()->at(0) == 0x30)
        {
            cout << "ON" << endl;
        }
        else
        {
            cout << "OFF" << endl;
        }
        HouseholdSolarPowerGeneration::inform().reqInformOperationStatus().send();
        return true;
    }
    virtual shared_ptr<vector<unsigned char>> getOperationStatus()
    {
        return mStatus;
    }
    virtual bool setInstallationLocation(vector<unsigned char> &edt)
    {
        return false;
    }
    virtual shared_ptr<vector<unsigned char>> getInstallationLocation()
    {
        return mLocation;
    }
    virtual shared_ptr<vector<unsigned char>> getFaultStatus()
    {
        return mFaultStatus;
    }
    virtual shared_ptr<vector<unsigned char>> getManufacturerCode()
    {
        return mManufacturerCode;
    }
};

int main()
{

    shared_ptr<DefaultNodeProfile> profile(new DefaultNodeProfile());
    vector<shared_ptr<DeviceObject>> devices;
    devices.push_back(shared_ptr<DeviceObject>(new Household()));

    // Echo::addEventListener(std::shared_ptr<Echo::EventListener>(new Echo::Logger()));

    Echo::start(profile, devices);

    while (true)
    {
        NodeProfile::Getter(NodeProfile::ECHO_CLASS_CODE, NodeProfile::INSTANCE_CODE, EchoSocket::MULTICAST_ADDRESS).reqGetSelfNodeInstanceListS().send();

        sleep(100);
    }

    return 0;
}