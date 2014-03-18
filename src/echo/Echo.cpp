/*
 * Echo.cpp
 *
 *  Created on: 2013/10/21
 *      Author: Fumiaki
 */

#include "Echo.h"
#include "OpenECHO.h"


std::shared_ptr<EchoStorage> Echo::sStorage;
std::shared_ptr<EchoNode> Echo::sSelfNode;
std::map<std::string, std::shared_ptr<EchoNode> > Echo::sOtherNodes;
Echo::EventListener Echo::sListener;
std::vector<std::shared_ptr<Echo::EventListener> > Echo::sEventListeners;

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
	sSelfNode.get()->onNew();
	sSelfNode.get()->onFound();

	sSelfNode.get()->getNodeProfile().get()->onNew();
	sSelfNode.get()->getNodeProfile().get()->onFound();

	for(int i = 0; i < devicesSize; i++) {
		devices.at(i).get()->onNew();
		devices.at(i).get()->onFound();

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

Echo::EventListener& Echo::getEventListener() {
	return sListener;
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

void Echo::EventListener::onNewDevice(std::shared_ptr<DeviceObject> device) {
}
