// /*
//  * Tutorial1.cpp
//  *
//  *  Created on: 2014/05/02
//  *      Author: Fumiaki
//  */


// #include <iostream>
// #include <memory>
// #include "../openecho/OpenECHO.h"

// using namespace std;
// using namespace sonycsl_openecho;


// class DefaultNodeProfile : public NodeProfile {

// public:
// 	DefaultNodeProfile() : NodeProfile() {}
// 	virtual ~DefaultNodeProfile(){}
// protected:
// 	virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
// 		return shared_ptr<vector<unsigned char> >();
// 	}
// 	virtual shared_ptr<vector<unsigned char> > getOperatingStatus() {
// 		return shared_ptr<vector<unsigned char> >();
// 	}
// 	virtual shared_ptr<vector<unsigned char> > getIdentificationNumber() {
// 		return shared_ptr<vector<unsigned char> >();
// 	}
// };

// // class HouseholdNode : public NodeProfile {
// // protected:
// // 	shared_ptr<vector<unsigned char> > mStatus;
// // 	shared_ptr<vector<unsigned char> > mLocation;
// // 	shared_ptr<vector<unsigned char> > mFaultStatus;
// // 	shared_ptr<vector<unsigned char> > mManufacturerCode;
// //     static const unsigned char EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION = 0xE0;

// // public:
// // 	HouseholdNode() : NodeProfile() {
// // 		// mStatus = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		// mStatus.get()->push_back(0x30);
// // 		// mLocation = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		// mLocation.get()->push_back(0x00);
// // 		// mFaultStatus = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		// mFaultStatus.get()->push_back(0x42);
// // 		// mManufacturerCode = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		// mManufacturerCode.get()->push_back(0x00);
// // 		// mManufacturerCode.get()->push_back(0x00);
// // 		// mManufacturerCode.get()->push_back(0x00);
// // 	}
// // 	virtual ~HouseholdNode(){}

// // 	virtual unsigned short getEchoClassCode() {
// // 		return 0x0279;
// // 	}
// // protected:

// // 	// virtual void setupPropertyMaps() {
// // 	// 	NodeProfile::setupPropertyMaps();
// // 	// 	addGetProperty(EPC_OPERATING_STATUS);
// //     //     addGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);


// // 	// }


// // 	// virtual bool setProperty(EchoProperty& property) {

// // 	// 	bool success = NodeProfile::setProperty(property);
// // 	// 	if(success) return true;

// // 	// 	switch(property.epc) {
// // 	// 	default : return false;
// // 	// 	}
// // 	// }

// // 	// virtual std::shared_ptr<std::vector<unsigned char> > getProperty(
// // 	// 		unsigned char epc) {

// // 	// 	std::shared_ptr<std::vector<unsigned char> > edt = NodeProfile::getProperty(epc);
// // 	// 	if(edt.get() != nullptr) return edt;

// // 	// 	switch(epc) {
// //     //     case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
// //     //         return getMeasuredInstantaneousAmountOfElectricityGenerated();
// // 	// 	default : return std::shared_ptr<std::vector<unsigned char> >();
// // 	// 	}
// // 	// }

// // 	// virtual bool isValidProperty(EchoProperty& property) {

// // 	// 	bool valid = NodeProfile::isValidProperty(property);
// // 	// 	if(valid) return true;

// // 	// 	switch(property.epc) {
// //     //     case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
// //     //         return isValidMeasuredInstantaneousAmountOfElectricityGenerated(property.edt);
// // 	// 	default : return false;
// // 	// 	}
// // 	// }


// // 	// bool setOperationStatus(vector<unsigned char>& edt) {
// // 	// 	(*(mStatus.get()))[0] = edt.at(0);
// // 	// 	if(mStatus.get()->at(0) == 0x30) {
// // 	// 		cout << "ON" << endl;
// // 	// 	} else {
// // 	// 		cout << " OFF" << endl;
// // 	// 	}
// // 	// 	inform().reqInformOperationStatus().send();
// // 	// 	return true;
// // 	// }
// // 	// virtual shared_ptr<vector<unsigned char> > getOperationStatus() {
// // 	// 	return mStatus;
// // 	// }
    
// // 	// virtual bool setInstallationLocation(vector<unsigned char>& edt) {
// // 	// 	return false;
// // 	// }
// // 	// virtual shared_ptr<vector<unsigned char> > getInstallationLocation() {
// // 	// 	return mLocation;
// // 	// }
// // 	// virtual shared_ptr<vector<unsigned char> > getFaultStatus() {
// // 	// 	return mFaultStatus;
// // 	// }
// // 	// virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
// // 	// 	return mManufacturerCode;
// // 	// }
// //     // shared_ptr<vector<unsigned char> > getMeasuredInstantaneousAmountOfElectricityGenerated()
// // 	// {	
// // 	// 	cout << "getMeasuredInstantaneousAmountOfElectricityGenerated function call" << endl;
// // 	// 	return NULL;
// // 	// }
// //     // bool isValidMeasuredInstantaneousAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
// //     // {
// //     //     if (edt.empty() || edt.size() != 2)
// //     //         return false;
// //     //     return true;
// //     // }
// // 	virtual shared_ptr<vector<unsigned char>> getManufacturerCode()
// //     {
// //         return shared_ptr<vector<unsigned char>>();
// //     }
// //     virtual shared_ptr<vector<unsigned char>> getOperatingStatus()
// //     {
// //         return shared_ptr<vector<unsigned char>>();
// //     }
// //     virtual shared_ptr<vector<unsigned char>> getIdentificationNumber()
// //     {
// //         return shared_ptr<vector<unsigned char>>();
// //     }
// // };

// class Household : public DeviceObject
// {
// protected:
//     shared_ptr<vector<unsigned char>> mStatus;
//     shared_ptr<vector<unsigned char>> mLocation;
//     shared_ptr<vector<unsigned char>> mFaultStatus;
//     shared_ptr<vector<unsigned char>> mManufacturerCode;
//     static const unsigned char EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION = 0xE0;
//     static const unsigned char EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION = 0xE1;

// public:
//     Household() : DeviceObject()
//     {
//         mStatus = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
//         mStatus.get()->push_back(0x30);
//         mLocation = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
//         mLocation.get()->push_back(0x00);
//         mFaultStatus = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
//         mFaultStatus.get()->push_back(0x42);
//         mManufacturerCode = shared_ptr<vector<unsigned char>>(new vector<unsigned char>());
//         mManufacturerCode.get()->push_back(0x00);
//         mManufacturerCode.get()->push_back(0x00);
//         mManufacturerCode.get()->push_back(0x00);
//     }
//     virtual ~Household() {}
//     virtual unsigned short getEchoClassCode()
//     {
//         return 0x0279;
//     }

// protected:
//     virtual void setupPropertyMaps()
//     {
//         DeviceObject::setupPropertyMaps();
//         addSetProperty(EPC_OPERATION_STATUS);
//         addGetProperty(EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION);
//         addGetProperty(EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION);
//     }
// 	virtual bool setProperty(EchoProperty& property) {

// 		bool success = DeviceObject::setProperty(property);
// 		if(success) return true;

// 		switch(property.epc) {
// 		default : return false;
// 		}
// 	}
//     virtual std::shared_ptr<std::vector<unsigned char>> getProperty(
//         unsigned char epc)
//     {

//         std::shared_ptr<std::vector<unsigned char>> edt = DeviceObject::getProperty(epc);
//         if (edt.get() != nullptr)
//             return edt;

//         switch (epc)
//         {
//         case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
//             return getMeasuredInstantaneousAmountOfElectricityGenerated();
//         case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
//             return getMeasuredCumulativeAmountOfElectricityGenerated();
//         default:
//             return std::shared_ptr<std::vector<unsigned char>>();
//         }
//     }
// 	virtual shared_ptr<vector<unsigned char> > getMeasuredInstantaneousAmountOfElectricityGenerated() {
// 		cout << "getMeasuredInstantaneousAmountOfElectricityGenerated function call" << endl;
// 		return NULL;
// 	}
// 	virtual shared_ptr<vector<unsigned char> > getMeasuredCumulativeAmountOfElectricityGenerated() {
// 		cout << "getMeasuredCumulativeAmountOfElectricityGenerated function call" << endl;
// 		return NULL;

// 	}
//     virtual bool isValidProperty(EchoProperty &property)
//     {
//         bool valid = DeviceObject::isValidProperty(property);
//         if (valid)
//             return true;

//         switch (property.epc)
//         {
//         case EPC_MEASURED_INSTANTANEOUS_ELECTRICITY_GENERATION:
//             return isValidMeasuredInstantaneousAmountOfElectricityGenerated(property.edt);
//         case EPC_MEASURED_CUMULATIVE_AMOUT_OF_ELECTRICITY_GENERATION:
//             return isValidMeasuredCumulativeAmountOfElectricityGenerated(property.edt);
//         default:
//             return false;
//         }
//     }
// 	bool isValidMeasuredInstantaneousAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
//     {
//         if (edt.empty() || edt.size() != 2)
//             return false;
//         return true;
//     }
// 	bool isValidMeasuredCumulativeAmountOfElectricityGenerated(std::vector<unsigned char> &edt)
//     {
//         if (edt.empty() || edt.size() != 4)
//             return false;
//         return true;
//     }
//     bool setOperationStatus(vector<unsigned char> &edt)
//     {
//         (*(mStatus.get()))[0] = edt.at(0);
//         if (mStatus.get()->at(0) == 0x30)
//         {
//             cout << "ON" << endl;
//         }
//         else
//         {
//             cout << "OFF" << endl;
//         }
//         DeviceObject::inform().reqInformOperationStatus().send();
//         return true;
//     }
// 	virtual shared_ptr<vector<unsigned char> > getOperationStatus() {
// 		return mStatus;
// 	}
// 	virtual bool setInstallationLocation(vector<unsigned char>& edt) {
// 		return false;
// 	}
// 	virtual shared_ptr<vector<unsigned char> > getInstallationLocation() {
// 		return mLocation;
// 	}
// 	virtual shared_ptr<vector<unsigned char> > getFaultStatus() {
// 		return mFaultStatus;
// 	}
// 	virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
// 		return mManufacturerCode;
// 	}

// };


// int main() {

// 	shared_ptr<DefaultNodeProfile> profile(new DefaultNodeProfile());
// 	vector<shared_ptr<DeviceObject> > devices;
// 	devices.push_back(shared_ptr<DeviceObject>(new Household()));

// 	//Echo::addEventListener(std::shared_ptr<Echo::EventListener>(new Echo::Logger()));

// 	Echo::start(profile, devices);

// 	while(true) {
// 		NodeProfile::Getter(NodeProfile::ECHO_CLASS_CODE
// 				, NodeProfile::INSTANCE_CODE
// 				, EchoSocket::MULTICAST_ADDRESS).reqGetSelfNodeInstanceListS().send();

// 		vector<shared_ptr<EchoNode> > nodes = Echo::getNodes();
// 		shared_ptr<EchoNode> local = Echo::getSelfNode();

// 		for(shared_ptr<EchoNode> en : nodes) {
// 			if(en.get()->isSelfNode()) {
// 				cout << "Node id = " << en.get()->getAddress() << "(local)" << endl;
// 			} else {
// 				cout << "Node id = " << en.get()->getAddress() << endl;
// 			}

// 			cout << " Node Profile = instanceCode:" << hex << (int)en.get()->getNodeProfile().get()->getInstanceCode() << endl;

// 			cout << " Devices" << endl;
// 			vector<shared_ptr<DeviceObject> > dos = en.get()->getDevices();

// 			for(shared_ptr<DeviceObject> d : dos) {
// 				cout << "  class:" << hex << d.get()->getEchoClassCode() << ",instanceCode:" << hex << (int)d.get()->getInstanceCode() << endl;
// 			}
// 			cout << "----" << endl;
// 		}
// 		cout << "--------" << endl;


// 		sleep(10);
// 	}




// 	return 0;
// }




// // #include <iostream>
// // #include <memory>
// // #include "../openecho/OpenECHO.h"

// // using namespace std;
// // // OpenECHOのnamespaceは"sonycsl_openecho"
// // using namespace sonycsl_openecho;


// // class DefaultNodeProfile : public NodeProfile {

// // public:
// // 	DefaultNodeProfile() : NodeProfile() {}
// // 	virtual ~DefaultNodeProfile(){}
// // protected:
// // 	virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
// // 		return shared_ptr<vector<unsigned char> >();
// // 	}
// // 	virtual shared_ptr<vector<unsigned char> > getOperatingStatus() {
// // 		return shared_ptr<vector<unsigned char> >();
// // 	}
// // 	virtual shared_ptr<vector<unsigned char> > getIdentificationNumber() {
// // 		return shared_ptr<vector<unsigned char> >();
// // 	}
// // };

// // class LightEmulator : public DeviceObject {
// // protected:
// // 	shared_ptr<vector<unsigned char> > mStatus;
// // 	shared_ptr<vector<unsigned char> > mLocation;
// // 	shared_ptr<vector<unsigned char> > mFaultStatus;
// // 	shared_ptr<vector<unsigned char> > mManufacturerCode;
// // 	shared_ptr<vector<unsigned char> > mLightingMode;
// // 	shared_ptr<vector<unsigned char> > mColor;
// // 	static const unsigned char EPC_LIGHTING_MODE_SETTING = 0xB6;
// // 	static const unsigned char EPC_RGB_SETTING_FOR_COLOR_LIGHTING = 0xC0;
// // public:
// // 	LightEmulator() : DeviceObject() {
// // 		mStatus = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		mStatus.get()->push_back(0x30);
// // 		mLocation = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		mLocation.get()->push_back(0x00);
// // 		mFaultStatus = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		mFaultStatus.get()->push_back(0x42);
// // 		mManufacturerCode = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		mManufacturerCode.get()->push_back(0x00);
// // 		mManufacturerCode.get()->push_back(0x00);
// // 		mManufacturerCode.get()->push_back(0x00);
// // 		mLightingMode = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		mLightingMode.get()->push_back(0x45);
// // 		mColor = shared_ptr<vector<unsigned char> >(new vector<unsigned char>());
// // 		mColor.get()->push_back(0xFF);
// // 		mColor.get()->push_back(0xFF);
// // 		mColor.get()->push_back(0xFF);
// // 	}
// // 	virtual ~LightEmulator(){}

// // 	virtual unsigned short getEchoClassCode() {
// // 		return 0x0290;
// // 	}
// // protected:

// // 	virtual void setupPropertyMaps() {
// // 		DeviceObject::setupPropertyMaps();
// // 		addSetProperty(EPC_OPERATION_STATUS);
// // 		addSetProperty(EPC_LIGHTING_MODE_SETTING);
// // 		addSetProperty(EPC_RGB_SETTING_FOR_COLOR_LIGHTING);
// // 		addGetProperty(EPC_LIGHTING_MODE_SETTING);
// // 		addGetProperty(EPC_RGB_SETTING_FOR_COLOR_LIGHTING);

// // 	}


// // 	virtual bool setProperty(EchoProperty& property) {

// // 		bool success = DeviceObject::setProperty(property);
// // 		if(success) return true;

// // 		switch(property.epc) {
// // 		case EPC_LIGHTING_MODE_SETTING : return setLightingModeSetting(property.edt);
// // 		case EPC_RGB_SETTING_FOR_COLOR_LIGHTING : return setRgbSettingForColorLighting(property.edt);
// // 		default : return false;
// // 		}
// // 	}

// // 	virtual std::shared_ptr<std::vector<unsigned char> > getProperty(
// // 			unsigned char epc) {

// // 		std::shared_ptr<std::vector<unsigned char> > edt = DeviceObject::getProperty(epc);
// // 		if(edt.get() != nullptr) return edt;

// // 		switch(epc) {
// // 		case EPC_LIGHTING_MODE_SETTING : return getLightingModeSetting();
// // 		case EPC_RGB_SETTING_FOR_COLOR_LIGHTING : return getRgbSettingForColorLighting();
// // 		default : return std::shared_ptr<std::vector<unsigned char> >();
// // 		}
// // 	}

// // 	virtual bool isValidProperty(EchoProperty& property) {

// // 		bool valid = DeviceObject::isValidProperty(property);
// // 		if(valid) return true;

// // 		switch(property.epc) {
// // 		case EPC_LIGHTING_MODE_SETTING : return isValidLightingModeSetting(property.edt);
// // 		case EPC_RGB_SETTING_FOR_COLOR_LIGHTING : return isValidRgbSettingForColorLighting(property.edt);
// // 		default : return false;
// // 		}
// // 	}


// // 	bool setOperationStatus(vector<unsigned char>& edt) {
// // 		(*(mStatus.get()))[0] = edt.at(0);
// // 		if(mStatus.get()->at(0) == 0x30) {
// // 			cout << "Light ON" << endl;
// // 		} else {
// // 			cout << "Light OFF" << endl;
// // 		}
// // 		inform().reqInformOperationStatus().send();
// // 		return true;
// // 	}
// // 	virtual shared_ptr<vector<unsigned char> > getOperationStatus() {
// // 		return mStatus;
// // 	}
// // 	virtual bool setInstallationLocation(vector<unsigned char>& edt) {
// // 		return false;
// // 	}
// // 	virtual shared_ptr<vector<unsigned char> > getInstallationLocation() {
// // 		return mLocation;
// // 	}
// // 	virtual shared_ptr<vector<unsigned char> > getFaultStatus() {
// // 		return mFaultStatus;
// // 	}
// // 	virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
// // 		return mManufacturerCode;
// // 	}


// // 	bool setLightingModeSetting(vector<unsigned char>& edt) {
// // 		(*(mLightingMode.get()))[0] = edt.at(0);

// // 		return true;
// // 	}

// // 	shared_ptr<vector<unsigned char> > getLightingModeSetting() {
// // 		return mLightingMode;
// // 	}

// // 	bool isValidLightingModeSetting(vector<unsigned char>& edt) {
// // 		if(edt.size() != 1) {return false;}
// // 		if(edt.at(0) == 0x41) {return true;}
// // 		if(edt.at(0) == 0x42) {return true;}
// // 		if(edt.at(0) == 0x43) {return true;}
// // 		if(edt.at(0) == 0x45) {return true;}
// // 		return false;
// // 	}

// // 	bool setRgbSettingForColorLighting(vector<unsigned char>& edt) {
// // 		(*(mColor.get()))[0] = edt.at(0);
// // 		(*(mColor.get()))[1] = edt.at(1);
// // 		(*(mColor.get()))[2] = edt.at(2);
// // 		cout << "R:" << (int)(mColor.get()->at(0))
// // 				<< ",G:" << (int)(mColor.get()->at(1))
// // 				<< ",B:" << (int)(mColor.get()->at(2)) << endl;
// // 		return true;
// // 	}

// // 	shared_ptr<vector<unsigned char> > getRgbSettingForColorLighting() {
// // 		return mColor;
// // 	}

// // 	bool isValidRgbSettingForColorLighting(vector<unsigned char>& edt) {
// // 		if(edt.size() != 3) {return false;}
// // 		return true;
// // 	}
// // };


// // int main() {

// // 	shared_ptr<DefaultNodeProfile> profile(new DefaultNodeProfile());
// // 	vector<shared_ptr<DeviceObject> > devices;
// // 	devices.push_back(shared_ptr<DeviceObject>(new LightEmulator()));

// // 	//Echo::addEventListener(std::shared_ptr<Echo::EventListener>(new Echo::Logger()));

// // 	Echo::start(profile, devices);

// // 	while(true) {
// // 		NodeProfile::Getter(NodeProfile::ECHO_CLASS_CODE
// // 				, NodeProfile::INSTANCE_CODE
// // 				, EchoSocket::MULTICAST_ADDRESS).reqGetSelfNodeInstanceListS().send();


// // 		sleep(10);
// // 	}




// // 	return 0;
// // }