/*
 * EchoObject.h
 *
 *  Created on: 2013/10/23
 *      Author: Fumiaki
 */

#ifndef ECHOOBJECT_H_
#define ECHOOBJECT_H_


#include <vector>
#include <memory>
#include <set>
#include <string>

namespace sonycsl_openecho {

class EchoFrame;
class EchoNode;
class EchoProperty;

class EchoObject {
public:
	class Receiver;
	class Setter;
	class Getter;
	class Informer;
	class InformerC;

private:
	std::shared_ptr<EchoObject::Receiver> mReceiver;
	std::shared_ptr<EchoNode> mNode;
protected:
	std::shared_ptr<std::set<unsigned char> > mAnnouncementProperties;
	std::shared_ptr<std::set<unsigned char> > mSetProperties;
	std::shared_ptr<std::set<unsigned char> > mGetProperties;
public:
	EchoObject();
	virtual ~EchoObject();

private:
	void operator =(const EchoObject& src); // non-copyable
	EchoObject(const EchoObject& src); // non-copyable

public:
	void init();
	virtual void onNew(std::shared_ptr<EchoObject> eoj);
	virtual void onFound(std::shared_ptr<EchoObject> eoj);
	unsigned char getClassGroupCode();
	unsigned char getClassCode();
	virtual unsigned char getInstanceCode() = 0;
	virtual unsigned short getEchoClassCode() = 0;
	long getEchoObjectCode();

	void setNode(std::shared_ptr<EchoNode> node);
	std::shared_ptr<EchoNode> getNode();
	void removeNode();

	bool isProxy();
	bool isSelfObject();

	virtual bool setProperty(EchoProperty& property);
	virtual std::shared_ptr<std::vector<unsigned char> > getProperty(unsigned char epc);
	virtual bool isValidProperty(EchoProperty& property);

	void addStatusChangeAnnouncementProperty(unsigned char epc);
	void removeStatusChangeAnnouncementProperty(unsigned char epc);
	void clearStatusChangeAnnouncementProperties();
	std::shared_ptr<std::set<unsigned char> > getStatusChangeAnnouncementProperties();

	void addSetProperty(unsigned char epc);
	void removeSetProperty(unsigned char epc);
	void clearSetProperties();
	std::shared_ptr<std::set<unsigned char> > getSetProperties();

	void addGetProperty(unsigned char epc);
	void removeGetProperty(unsigned char epc);
	void clearGetProperties();
	std::shared_ptr<std::set<unsigned char> > getGetProperties();

	void setReceiver(std::shared_ptr<EchoObject::Receiver> receiver);
	std::shared_ptr<EchoObject::Receiver> getReceiver();

	EchoFrame onReceiveRequest(EchoFrame& frame);

	EchoObject::Setter set();
	EchoObject::Setter set(bool responseRequired);
	EchoObject::Getter get();
	EchoObject::Informer inform();

protected:
	EchoObject::Informer inform(bool multicast);
	EchoObject::InformerC informC(std::string address);

	virtual void setupPropertyMaps();
	void onReceiveSetRequest(EchoProperty& property, EchoFrame& response);
	void onReceiveGetRequest(unsigned char epc, EchoFrame& response);


public:
	class Receiver {
	public:
		Receiver();
		virtual ~Receiver();
	public:
		void onReceive(std::shared_ptr<EchoObject> eoj, EchoFrame& frame);
	protected:
		virtual void onReceiveFrame(std::shared_ptr<EchoObject> eoj, EchoFrame& frame);
		virtual bool onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual bool onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property, bool success);
		virtual bool onInformProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid, unsigned char esv, EchoProperty& property);
	};

	class Sender {
	protected:
		unsigned short mSrcEchoClassCode;
		unsigned char mSrcEchoInstanceCode;
		unsigned short mDstEchoClassCode;
		unsigned char mDstEchoInstanceCode;
		std::string mDstEchoAddress;
		unsigned char mESV;
	public:
		Sender(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
				, unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress, unsigned char esv);
		virtual ~Sender();
		void setSeoj(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode);
		void setDeoj(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress);
	protected:
		virtual EchoFrame send() = 0;
		void send(EchoFrame& frame);
		virtual EchoFrame sendTCP() = 0;
		void sendTCP(EchoFrame& frame);

	};

	class Setter : public EchoObject::Sender {
	private:
		std::vector<EchoProperty> mPropertyList;
	public:
		Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress, bool responseRequired);
		virtual ~Setter();
		EchoFrame send();
		EchoFrame sendTCP();
		virtual EchoObject::Setter& reqSetProperty(unsigned char epc, std::vector<unsigned char> edt);
	};

	class Getter : public EchoObject::Sender {
	private:
		std::vector<unsigned char> mEPCList;
	public:
		Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~Getter();
		EchoFrame send();
		EchoFrame sendTCP();
		virtual EchoObject::Getter& reqGetProperty(unsigned char epc);
	};

	class Informer : public EchoObject::Sender {
	private:
		std::vector<unsigned char> mEPCList;
	public:
		Informer(unsigned short echoClassCode, unsigned char echoInstanceCode
				, std::string dstEchoAddress, bool isSelfObject);
		virtual ~Informer();
		EchoFrame send();
		EchoFrame sendTCP();
		virtual EchoObject::Informer& reqInformProperty(unsigned char epc);
	};

	class InformerC : public EchoObject::Sender {
	private:
		std::vector<unsigned char> mEPCList;
	public:
		InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
				, std::string dstEchoAddress);
		virtual ~InformerC();
		EchoFrame send();
		EchoFrame sendTCP();
		virtual EchoObject::InformerC& reqInformProperty(unsigned char epc);
	};
};


};

#endif /* ECHOOBJECT_H_ */
