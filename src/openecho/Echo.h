/*
 * Echo.h
 *
 *  Created on: 2013/10/21
 *      Author: Fumiaki
 */

#ifndef ECHO_H_
#define ECHO_H_

#include <map>
#include <vector>
#include <list>
#include <string>
#include <memory>

namespace sonycsl_openecho {

class EchoStorage;
class EchoFrame;
class EchoNode;
class EchoObject;
class NodeProfile;
class DeviceObject;

class Echo {
public:
	class EventListener;
private:
	class EventListenerDelegate;
private:
	static std::shared_ptr<EchoStorage> sStorage;

	static std::shared_ptr<EchoNode> sSelfNode;
	static std::map<std::string, std::shared_ptr<EchoNode> > sOtherNodes;

	static Echo::EventListenerDelegate sEventListenerDelegate;

private:
	Echo();
	~Echo();
	Echo(const Echo& rhs);
	Echo& operator=(const Echo& rhs);

public:

	static std::shared_ptr<EchoNode> start(std::shared_ptr<NodeProfile> profile, std::vector<std::shared_ptr<DeviceObject> > devices);
	static void restart();
	static void stop();
	static bool isStarted();

	static void setStorage(std::shared_ptr<EchoStorage> storage);
	static std::shared_ptr<EchoStorage> getStorage();

	static Echo::EventListener& getEventListenerDelegate();

	static void addEventListener(std::shared_ptr<Echo::EventListener> eventListener);
	static void removeEventListener(std::shared_ptr<Echo::EventListener> eventListener);

	static std::shared_ptr<EchoNode> getSelfNode();
	static std::vector<std::shared_ptr<EchoNode> > getNodes();
	static std::shared_ptr<EchoNode> getNode(std::string address);
	static bool containsNode(std::string address);
	static std::shared_ptr<EchoNode> addOtherNode(std::string address);
	static void removeOtherNode(std::string address);

public:
	class EventListener {
	public:
		EventListener();
		virtual ~EventListener();
		virtual void onNewNode(std::shared_ptr<EchoNode> node);
		virtual void onFoundNode(std::shared_ptr<EchoNode> node);
		virtual void onNewEchoObject(std::shared_ptr<EchoObject> eoj);
		virtual void onFoundEchoObject(std::shared_ptr<EchoObject> eoj);
		virtual void onNewNodeProfile(std::shared_ptr<NodeProfile> profile);
		virtual void onNewDeviceObject(std::shared_ptr<DeviceObject> device);

        void onNewHouseholdSolarPowerGeneration(std::shared_ptr<HouseholdSolarPowerGeneration> device);

        virtual void onSendFrame(EchoFrame& frame);
		virtual void onReceiveFrame(EchoFrame& frame);
	};

private:
	class EventListenerDelegate : public EventListener {
	private:
		std::list<std::shared_ptr<Echo::EventListener> > mEventListeners;

	public:
		void addEventListener(std::shared_ptr<Echo::EventListener> eventListener);
		void removeEventListener(std::shared_ptr<Echo::EventListener> eventListener);

		virtual void onNewNode(std::shared_ptr<EchoNode> node);
		virtual void onFoundNode(std::shared_ptr<EchoNode> node);
		virtual void onNewEchoObject(std::shared_ptr<EchoObject> eoj);
		virtual void onFoundEchoObject(std::shared_ptr<EchoObject> eoj);
		virtual void onNewNodeProfile(std::shared_ptr<NodeProfile> profile);
		virtual void onNewDeviceObject(std::shared_ptr<DeviceObject> device);


		virtual void onSendFrame(EchoFrame& frame);
		virtual void onReceiveFrame(EchoFrame& frame);

	};

public:
	class Logger : public EventListener {

		virtual void onNewNode(std::shared_ptr<EchoNode> node);
		virtual void onFoundNode(std::shared_ptr<EchoNode> node);
		virtual void onNewEchoObject(std::shared_ptr<EchoObject> eoj);
		virtual void onFoundEchoObject(std::shared_ptr<EchoObject> eoj);
		virtual void onSendFrame(EchoFrame& frame);
		virtual void onReceiveFrame(EchoFrame& frame);
	};
};

};

#endif /* ECHO_H_ */
