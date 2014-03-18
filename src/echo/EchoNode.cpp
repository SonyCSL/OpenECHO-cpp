/*
 * EchoNode.cpp
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#include "EchoNode.h"
#include "OpenECHO.h"


EchoNode::EchoNode(std::shared_ptr<NodeProfile> nodeProfile,
		std::vector<std::shared_ptr<DeviceObject> > devices) {
	// self node
	mAddress = EchoSocket::SELF_ADDRESS;
	mNodeProfile = nodeProfile;
	int devicesSize = devices.size();
	for(int i = 0; i < devicesSize; i++) {
		//devices.at(i).get()->allocateSelfDeviceInstanceCode();
		//mDevices.push_back(devices.at(i));
		//addDevice(devices.at(i));
		if(isSelfNode()) {
			devices.at(i).get()->allocateSelfDeviceInstanceCode();
			mDevices.push_back(devices.at(i));
		}
	}
}

EchoNode::EchoNode(std::string address) {
	// other node
	mAddress = address;
	mNodeProfile = std::shared_ptr<NodeProfile>(new NodeProfile::Proxy());
}


EchoNode::~EchoNode() {
	// TODO Auto-generated destructor stub
}

bool EchoNode::isProxy() {
	return (mAddress != EchoSocket::SELF_ADDRESS);
}

bool EchoNode::isSelfNode() {
	return (mAddress == EchoSocket::SELF_ADDRESS);
}

std::shared_ptr<NodeProfile> EchoNode::getNodeProfile() {
	return mNodeProfile;
}

std::string EchoNode::getAddress() {
	return mAddress;
}

std::shared_ptr<DeviceObject> EchoNode::addOtherDevice(unsigned short echoClassCode,
		unsigned char echoInstanceCode) {
	std::shared_ptr<DeviceObject> device(newOtherDevice(echoClassCode, echoInstanceCode));
	addDevice(device);
	return device;
}


void EchoNode::addDevice(std::shared_ptr<DeviceObject> device) {
	if(device.get() == nullptr) {
		return;
	}
	if(device.get()->getNode().get() == this) {
		return;
	}

	if(isSelfNode()) {
		device.get()->allocateSelfDeviceInstanceCode();
		device.get()->setNode(Echo::getSelfNode());
		mDevices.push_back(device);
		device.get()->onNew();
		device.get()->onFound();
	} else {
		mDevices.push_back(device);
	}
	std::cerr << "[addDevice]address:" << mAddress << ",class:"
			<< std::hex << device.get()->getEchoClassCode() << ",instance:"
			<< std::hex << (int)(device.get()->getInstanceCode()) << std::endl;


}
void EchoNode::removeDevice(unsigned short echoClassCode,
		unsigned char echoInstanceCode) {
	int listSize = mDevices.size();
	for(int i = 0; i < listSize; i++) {
		if(mDevices.at(i).get()->getEchoClassCode() == echoClassCode
				&& mDevices.at(i).get()->getInstanceCode() == echoInstanceCode) {
			mDevices.erase(mDevices.begin() + i);

			if(isSelfNode()) {

			}
			break;
		}
	}
}

bool EchoNode::containsDevice(unsigned short echoClassCode,
		unsigned char echoInstanceCode) {

	int listSize = mDevices.size();
	for(int i = 0; i < listSize; i++) {
		if(mDevices.at(i).get()->getEchoClassCode() == echoClassCode
				&& mDevices.at(i).get()->getInstanceCode() == echoInstanceCode) {

			return true;
		}
	}
	return false;
}

std::shared_ptr<EchoObject> EchoNode::getInstance(
		unsigned short echoClassCode, unsigned char echoInstanceCode) {
	if(echoClassCode == mNodeProfile.get()->getEchoClassCode()
			&& echoInstanceCode == mNodeProfile.get()->getInstanceCode()) {
		return mNodeProfile;
	}

	int listSize = mDevices.size();
	for(int i = 0; i < listSize; i++) {
		if(mDevices.at(i).get()->getEchoClassCode() == echoClassCode
				&& mDevices.at(i).get()->getInstanceCode() == echoInstanceCode) {
			return mDevices.at(i);
		}
	}
	std::shared_ptr<EchoObject> eoj;
	return eoj;
}

std::vector<std::shared_ptr<DeviceObject> > EchoNode::getDevices() {

	return mDevices;
}


std::vector<std::shared_ptr<DeviceObject> > EchoNode::getDevices(
		unsigned short echoClassCode) {

	std::vector<std::shared_ptr<DeviceObject> > ret;

	int listSize = mDevices.size();
	for(int i = 0; i < listSize; i++) {
		if(mDevices.at(i).get()->getEchoClassCode() == echoClassCode) {
			ret.push_back(mDevices.at(i));
		}
	}
	return ret;
}

void EchoNode::onNew() {
}

void EchoNode::onFound() {
}

DeviceObject* EchoNode::newOtherDevice(unsigned short echoClassCode,
		unsigned char echoInstanceCode) {
	//return 0;
	DeviceObject* device = new DeviceObject::Proxy(echoClassCode, echoInstanceCode);

	return device;
}

