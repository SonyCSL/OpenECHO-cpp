/*
 * Tutorial1.cpp
 *
 *  Created on: 2014/05/02
 *      Author: Fumiaki
 */


#include <iostream>
#include <memory>
#include "../openecho/OpenECHO.h"

using namespace std;
// OpenECHOのnamespaceは"sonycsl_openecho"
using namespace sonycsl_openecho;


class MyControllerReceiver : public DeviceObject::Receiver {
public:
	MyControllerReceiver(){}
	virtual ~MyControllerReceiver(){}
protected:
	virtual void onGetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {
		cout << "Controller power : ";
		for(unsigned char b : property.edt) {
			cout << hex << (int)b << " ";
		}
		cout << endl;
	}
	virtual void onGetInstallationLocation(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {
		cout << "Installation location : ";
		for(unsigned char b : property.edt) {
			cout << hex << (int)b << " ";
		}
		cout << endl;
	}
};
class MyPowerDistributionBoardMeteringReceiver : public DeviceObject::Receiver {
public:
	MyPowerDistributionBoardMeteringReceiver(){}
	virtual ~MyPowerDistributionBoardMeteringReceiver(){}
protected:

	virtual void onGetMeasuredInstantaneousCurrents(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {
		cout << "GetMeasuredInstantaneousCurrents IntCur : ";
		for(unsigned char b : property.edt) {
			cout << hex << (int)b << " ";
		}
		cout << endl;
	}
	virtual void onGetOperationStatus(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {
		cout << "PowerDistributionBoardMetering power : ";
		for(unsigned char b : property.edt) {
			cout << hex << (int)b << " ";
		}
		cout << endl;
	}
	virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {

		bool ret = DeviceObject::Receiver::onGetProperty(eoj, tid, esv, property, success);
		if(ret) return true;
		switch(property.epc) {
		case ((unsigned char)0xC7) :
			onGetMeasuredInstantaneousCurrents(eoj, tid, esv, property, success);
			return true;
		default :
			return false;
		}
	}

};

class MyEventListener : public Echo::EventListener {
	virtual void onNewDeviceObject(std::shared_ptr<DeviceObject> device) {
		if(device.get()->getEchoClassCode() == 0x05FF) {
			cout << "Controller found." << endl;
			device.get()->setReceiver(shared_ptr<EchoObject::Receiver>(new MyControllerReceiver()));
			device.get()->get().reqGetOperationStatus().reqGetInstallationLocation().send();
		} else if(device.get()->getEchoClassCode() == 0x0287) {
			cout << "PowerDistributionBoardMetering found." << endl;
			device.get()->setReceiver(shared_ptr<EchoObject::Receiver>(new MyPowerDistributionBoardMeteringReceiver()));
			device.get()->get().reqGetProperty((unsigned char)0xC7).reqGetOperationStatus().send();
		}
	}
};

class DefaultNodeProfile : public NodeProfile {

public:
	DefaultNodeProfile(){}
	virtual ~DefaultNodeProfile(){}
protected:
	virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
		return shared_ptr<vector<unsigned char> >();
	}
	virtual shared_ptr<vector<unsigned char> > getOperatingStatus() {
		return shared_ptr<vector<unsigned char> >();
	}
	virtual shared_ptr<vector<unsigned char> > getIdentificationNumber() {
		return shared_ptr<vector<unsigned char> >();
	}
};

class DefaultController : public DeviceObject {

public:
	DefaultController(){}
	virtual ~DefaultController(){}

	virtual unsigned short getEchoClassCode() {
		return 0x05FF;
	}
protected:
	virtual shared_ptr<vector<unsigned char> > getOperationStatus() {
		return shared_ptr<vector<unsigned char> >();
	}
	virtual bool setInstallationLocation(vector<unsigned char>& edt) {
		return false;
	}
	virtual shared_ptr<vector<unsigned char> > getInstallationLocation() {
		return shared_ptr<vector<unsigned char> >();
	}
	virtual shared_ptr<vector<unsigned char> > getFaultStatus() {
		return shared_ptr<vector<unsigned char> >();
	}
	virtual shared_ptr<vector<unsigned char> > getManufacturerCode() {
		return shared_ptr<vector<unsigned char> >();
	}
};


int main() {

	shared_ptr<Echo::EventListener> eventListener(new MyEventListener());
	Echo::addEventListener(eventListener);

	shared_ptr<DefaultNodeProfile> profile(new DefaultNodeProfile());
	vector<shared_ptr<DeviceObject> > devices;
	devices.push_back(shared_ptr<DeviceObject>(new DefaultController()));

	Echo::start(profile, devices);

	while(true) {
		NodeProfile::Getter(NodeProfile::ECHO_CLASS_CODE
				, NodeProfile::INSTANCE_CODE
				, EchoSocket::MULTICAST_ADDRESS).reqGetSelfNodeInstanceListS().send();


		sleep(10);
	}




	return 0;
}
