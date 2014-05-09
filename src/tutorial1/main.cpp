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

class MyNodeProfileReceiver : public NodeProfile::Receiver {

public:
	MyNodeProfileReceiver(){}
	virtual ~MyNodeProfileReceiver(){}
protected:
	virtual void onGetInstanceListNotification(shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success) {
		cerr << "onGetInstanceListNotification" << endl;
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
	shared_ptr<DefaultNodeProfile> profile(new DefaultNodeProfile());
	vector<shared_ptr<DeviceObject> > devices;
	devices.push_back(shared_ptr<DeviceObject>(new DefaultController()));

	Echo::start(profile, devices);

	while(true) {
		NodeProfile::Getter(NodeProfile::ECHO_CLASS_CODE
				, NodeProfile::INSTANCE_CODE
				, EchoSocket::MULTICAST_ADDRESS).reqGetSelfNodeInstanceListS().send();


		vector<shared_ptr<EchoNode> > nodes = Echo::getNodes();
		shared_ptr<EchoNode> local = Echo::getSelfNode();

		for(shared_ptr<EchoNode> en : nodes) {
			if(en.get()->isSelfNode()) {
				cout << "Node id = " << en.get()->getAddress() << "(local)" << endl;
			} else {
				cout << "Node id = " << en.get()->getAddress() << endl;
			}

			cout << " Node Profile = instanceCode:" << hex << (int)en.get()->getNodeProfile().get()->getInstanceCode() << endl;

			cout << " Devices" << endl;
			vector<shared_ptr<DeviceObject> > dos = en.get()->getDevices();

			for(shared_ptr<DeviceObject> d : dos) {
				cout << "  class:" << hex << d.get()->getEchoClassCode() << ",instanceCode:" << hex << (int)d.get()->getInstanceCode() << endl;
			}
			cout << "----" << endl;
		}
		cout << "--------" << endl;


		sleep(10);
	}




	return 0;
}
