//============================================================================
// Name        : OpenECHO.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include "echo/OpenECHO.h"

using namespace std;

class MyNodeProfile : public NodeProfile {

public:
	MyNodeProfile(){}
	virtual ~MyNodeProfile(){}
protected:
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturerCode() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
	virtual std::shared_ptr<std::vector<unsigned char> > getOperatingStatus() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
	virtual std::shared_ptr<std::vector<unsigned char> > getIdentificationNumber() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
};

class MyNodeProfileReceiver : public NodeProfile::Receiver {

public:
	MyNodeProfileReceiver(){}
	virtual ~MyNodeProfileReceiver(){}
protected:
	virtual void onGetInstanceListNotification(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {
		cerr << "onGetInstanceListNotification" << endl;
	}
};
class MyController : public DeviceObject {

public:
	MyController(){}
	virtual ~MyController(){}

	virtual unsigned short getEchoClassCode() {
		return 0x05FF;
	}
protected:
	virtual std::shared_ptr<std::vector<unsigned char> > getOperationStatus() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
	virtual bool setInstallationLocation(std::vector<unsigned char>& edt) {
		return false;
	}
	virtual std::shared_ptr<std::vector<unsigned char> > getInstallationLocation() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
	virtual std::shared_ptr<std::vector<unsigned char> > getFaultStatus() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
	virtual std::shared_ptr<std::vector<unsigned char> > getManufacturerCode() {
		return std::shared_ptr<std::vector<unsigned char> >();
	}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	std::shared_ptr<MyNodeProfile> profile(new MyNodeProfile());
	std::vector<std::shared_ptr<DeviceObject> > devices;
	devices.push_back(std::shared_ptr<DeviceObject>(new MyController()));

	profile.get()->setReceiver(std::shared_ptr<EchoObject::Receiver>(new MyNodeProfileReceiver()));

	//while(true){}
	Echo::start(profile, devices);

	while(true){sleep(1);}




	return 0;
}
