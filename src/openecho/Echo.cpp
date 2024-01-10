/*
 * Echo.cpp
 *
 *  Created on: 2013/10/21
 *      Author: Fumiaki
 */

#include "Echo.h"
#include "OpenECHO.h"


namespace sonycsl_openecho {

std::shared_ptr<EchoStorage> Echo::sStorage;
std::shared_ptr<EchoNode> Echo::sSelfNode;
std::map<std::string, std::shared_ptr<EchoNode> > Echo::sOtherNodes;
Echo::EventListenerDelegate Echo::sEventListenerDelegate;

Echo::Echo() {
	// TODO Auto-generated constructor stub

}

Echo::~Echo() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<EchoNode> Echo::start(
		std::shared_ptr<NodeProfile> profile,
		std::vector<std::shared_ptr<DeviceObject> > devices) {
	if(sStorage.get() == nullptr) {
		sStorage = std::shared_ptr<EchoStorage>(new EchoStorage());
	}

	sSelfNode = std::shared_ptr<EchoNode>(new EchoNode(profile, devices));
	sSelfNode.get()->getNodeProfile().get()->setNode(sSelfNode);
	int devicesSize = devices.size();
	for(int i = 0; i < devicesSize; i++) {
		devices.at(i).get()->setNode(sSelfNode);
	}


	EchoSocket::openSocket();
	EchoSocket::startReceiverThread();
	//Echo::getEventListener().onNewNode(sSelfNode);
	//Echo::getEventListener().onFoundNode(sSelfNode);
	//sSelfNode.get()->onNewNode();
	//sSelfNode.get()->onFoundNode();
	sSelfNode.get()->onNew(sSelfNode);
	sSelfNode.get()->onFound(sSelfNode);

	sSelfNode.get()->getNodeProfile().get()->onNew(sSelfNode.get()->getNodeProfile());
	sSelfNode.get()->getNodeProfile().get()->onFound(sSelfNode.get()->getNodeProfile());

	for(int i = 0; i < devicesSize; i++) {
		devices.at(i).get()->onNew(devices.at(i));
		devices.at(i).get()->onFound(devices.at(i));

	}

	profile.get()->inform().reqInformInstanceListNotification().send();

	return sSelfNode;
}

void Echo::restart() {
}

void Echo::stop() {
}

bool Echo::isStarted() {
	return true;
}

void Echo::setStorage(std::shared_ptr<EchoStorage> storage) {
	sStorage = storage;
}

std::shared_ptr<EchoStorage> Echo::getStorage() {
	return sStorage;
}

Echo::EventListener& Echo::getEventListenerDelegate() {
	return sEventListenerDelegate;
}

std::shared_ptr<EchoNode> Echo::getSelfNode() {
	return sSelfNode;
}

std::vector<std::shared_ptr<EchoNode> > Echo::getNodes() {
	std::vector<std::shared_ptr<EchoNode> > nodes;
	nodes.push_back(sSelfNode);
	for(std::map<std::string, std::shared_ptr<EchoNode> >::iterator itr = sOtherNodes.begin();
			itr != sOtherNodes.end(); itr++) {
		nodes.push_back(itr->second);
	}
	return nodes;
}

std::shared_ptr<EchoNode> Echo::getNode(std::string address) {
	if(EchoSocket::SELF_ADDRESS == address) {
		return sSelfNode;
	}
	if (sOtherNodes.find(address) == sOtherNodes.end()) {
		std::shared_ptr<EchoNode> node;
		return node;
	} else {
		return sOtherNodes.at(address);
	}
}

bool Echo::containsNode(std::string address) {
	std::shared_ptr<EchoNode> node = getNode(address);
	if(node.get() == NULL) {
		return false;
	}
	return true;
}

std::shared_ptr<EchoNode> Echo::addOtherNode(std::string address) {
	std::shared_ptr<EchoNode> node(new EchoNode(address));
	node.get()->getNodeProfile().get()->setNode(node);
	sOtherNodes.insert(std::map<std::string, std::shared_ptr<EchoNode> >::value_type(address, node));
	return node;
}

void Echo::addEventListener(
		std::shared_ptr<Echo::EventListener> eventListener) {
	sEventListenerDelegate.addEventListener(eventListener);
}

void Echo::removeEventListener(
		std::shared_ptr<Echo::EventListener> eventListener) {
	sEventListenerDelegate.removeEventListener(eventListener);
}

void Echo::removeOtherNode(std::string address) {
	if (sOtherNodes.find(address) == sOtherNodes.end()) {
		//std::shared_ptr<EchoNode> node;
		//return node;
	} else {
		//return mOtherNodes.at(address);
		sOtherNodes.erase(address);
	}
}

void Echo::EventListener::onNewNode(std::shared_ptr<EchoNode> node) {
}

void Echo::EventListener::onFoundNode(std::shared_ptr<EchoNode> node) {
}

void Echo::EventListener::onNewEchoObject(std::shared_ptr<EchoObject> eoj) {
}

void Echo::EventListener::onFoundEchoObject(std::shared_ptr<EchoObject> eoj) {
}

void Echo::EventListener::onNewNodeProfile(
		std::shared_ptr<NodeProfile> profile) {
}

Echo::EventListener::EventListener() {
}

Echo::EventListener::~EventListener() {
}

void Echo::EventListener::onNewDeviceObject(std::shared_ptr<DeviceObject> device) {
}
// void Echo::EventListener::onNewHouseholdSolarPowerGeneration(std::shared_ptr<HouseholdSolarPowerGeneration> device) {
// }



void Echo::EventListener::onSendFrame(EchoFrame& frame) {
}

void Echo::EventListener::onReceiveFrame(EchoFrame& frame) {
}

void Echo::EventListenerDelegate::addEventListener(
		std::shared_ptr<Echo::EventListener> eventListener) {
	mEventListeners.push_back(eventListener);

}

void Echo::EventListenerDelegate::removeEventListener(
		std::shared_ptr<Echo::EventListener> eventListener) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		if((*it).get() == eventListener.get()) {
			mEventListeners.erase(it);
			break;
		}
		++it;
	}
}

void Echo::EventListenerDelegate::onNewNode(std::shared_ptr<EchoNode> node) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onNewNode(node);
		++it;
	}
}

void Echo::EventListenerDelegate::onFoundNode(std::shared_ptr<EchoNode> node) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onFoundNode(node);
		++it;
	}
}

void Echo::EventListenerDelegate::onNewEchoObject(
		std::shared_ptr<EchoObject> eoj) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onNewEchoObject(eoj);
		++it;
	}
}

void Echo::EventListenerDelegate::onFoundEchoObject(
		std::shared_ptr<EchoObject> eoj) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onFoundEchoObject(eoj);
		++it;
	}
}

void Echo::EventListenerDelegate::onNewNodeProfile(
		std::shared_ptr<NodeProfile> profile) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onNewNodeProfile(profile);
		++it;
	}
}

void Echo::EventListenerDelegate::onNewDeviceObject(
		std::shared_ptr<DeviceObject> device) {
	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onNewDeviceObject(device);
		++it;
	}
}

void Echo::EventListenerDelegate::onSendFrame(EchoFrame& frame) {

	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onSendFrame(frame);
		++it;
	}
}

void Echo::EventListenerDelegate::onReceiveFrame(EchoFrame& frame) {

	std::list<std::shared_ptr<Echo::EventListener> >::iterator it = mEventListeners.begin();
	while( it != mEventListeners.end() ) {
		(*it).get()->onReceiveFrame(frame);
		++it;
	}
}

void Echo::Logger::onNewNode(std::shared_ptr<EchoNode> node) {
	std::cout << "[onNewNode]address:" << node.get()->getAddress() << std::endl;
}

void Echo::Logger::onFoundNode(std::shared_ptr<EchoNode> node) {
	std::cout << "[onFoundNode]address:" << node.get()->getAddress() << std::endl;
}

void Echo::Logger::onNewEchoObject(std::shared_ptr<EchoObject> eoj) {
	std::cout << "[onNewEchoObject]address:" << eoj.get()->getNode().get()->getAddress() << ",echo_class_code:"
			<< std::hex << eoj.get()->getEchoClassCode() << ",instance_code:"
			<< std::hex << (int)(eoj.get()->getInstanceCode()) << std::endl;
}

void Echo::Logger::onFoundEchoObject(std::shared_ptr<EchoObject> eoj) {
	std::cout << "[onFoundEchoObject]address:" << eoj.get()->getNode().get()->getAddress() << ",echo_class_code:"
			<< std::hex << eoj.get()->getEchoClassCode() << ",instance_code:"
			<< std::hex << (int)(eoj.get()->getInstanceCode()) << std::endl;
}

void Echo::Logger::onSendFrame(EchoFrame& frame) {

	std::vector<unsigned char> byteArray = frame.getFrameByteArray();
	int size = byteArray.size();
	unsigned char buffer[size];
	for (int i = 0; i < size; i++) {
		buffer[i] = byteArray.at(i);
	}

	std::cout << "[onSendFrame]data:" << std::hex;
	for (int i = 0; i < size; i++) {
		std::cout << (int) (buffer[i]) << " ";
	}
	std::cout << ", to:" << frame.getDstEchoAddress() << std::endl;

}

void Echo::Logger::onReceiveFrame(EchoFrame& frame) {

	std::vector<unsigned char> byteArray = frame.getFrameByteArray();
	int size = byteArray.size();
	unsigned char buffer[size];
	for (int i = 0; i < size; i++) {
		buffer[i] = byteArray.at(i);
	}


	std::cout << "[onReceiveFrame]:data:" << std::hex;
	for (int i = 0; i < size; i++) {
		std::cout << (int) (buffer[i]) << " ";
	}
	std::cout << ", from:" << frame.getSrcEchoAddress() << std::endl;
}
};

