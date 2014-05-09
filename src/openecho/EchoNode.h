/*
 * EchoNode.h
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#ifndef ECHONODE_H_
#define ECHONODE_H_


#include <vector>
#include <map>
#include <string>
#include <memory>


namespace sonycsl_openecho {


class EchoObject;
class NodeProfile;
class DeviceObject;


class EchoNode {
private:
	std::shared_ptr<NodeProfile> mNodeProfile;
	std::vector<std::shared_ptr<DeviceObject> > mDevices;
	std::string mAddress;
//protected:
//	int mNodeIndex;
public:
	EchoNode(std::shared_ptr<NodeProfile> nodeProfile, std::vector<std::shared_ptr<DeviceObject> > devices);
	EchoNode(std::string address);
	virtual ~EchoNode();

private:
	void operator =(const EchoNode& src); // non-copyable
	EchoNode(const EchoNode& src); // non-copyable

public:
	void onNew(std::shared_ptr<EchoNode> node);
	void onFound(std::shared_ptr<EchoNode> node);
	bool isProxy();
	bool isSelfNode();
	std::shared_ptr<NodeProfile> getNodeProfile();
	std::string getAddress();
	std::shared_ptr<DeviceObject> addOtherDevice(unsigned short echoClassCode, unsigned char echoInstanceCode);
	void addDevice(std::shared_ptr<DeviceObject> device);
	void removeDevice(unsigned short echoClassCode, unsigned char echoInstanceCode);
	bool containsDevice(unsigned short echoClassCode, unsigned char echoInstanceCode);
	std::shared_ptr<EchoObject> getInstance(unsigned short echoClassCode, unsigned char echoInstanceCode);
	std::vector<std::shared_ptr<DeviceObject> > getDevices();
	std::vector<std::shared_ptr<DeviceObject> > getDevices(unsigned short echoClassCode);
private:
	static DeviceObject* newOtherDevice(unsigned short echoClassCode, unsigned char echoInstanceCode);
};

};

#endif /* ECHONODE_H_ */
