/*
 * EchoObject.cpp
 *
 *  Created on: 2013/10/23
 *      Author: Fumiaki
 */

#include "EchoObject.h"
#include "OpenECHO.h"


namespace sonycsl_openecho {

EchoObject::EchoObject() {
	// TODO Auto-generated constructor stub

	//mReceiver = NULL;
	mAnnouncementProperties = std::shared_ptr<std::set<unsigned char> >(new std::set<unsigned char>());
	mSetProperties = std::shared_ptr<std::set<unsigned char> >(new std::set<unsigned char>());
	mGetProperties = std::shared_ptr<std::set<unsigned char> >(new std::set<unsigned char>());


}

EchoObject::~EchoObject() {
	// TODO Auto-generated destructor stub
}

void EchoObject::init() {
	setupPropertyMaps();
}

unsigned char EchoObject::getClassGroupCode() {
	unsigned short code = getEchoClassCode();
	return (unsigned char)((code >> 8) & 0xFF);
}

unsigned char EchoObject::getClassCode() {
	unsigned short code = getEchoClassCode();
	return (unsigned char)(code & 0xFF);
}

long EchoObject::getEchoObjectCode() {
	return EchoUtils::convertToEchoObjectCode(getEchoClassCode(), getInstanceCode());
}


void EchoObject::setNode(std::shared_ptr<EchoNode> node) {
	mNode = node;

	//Echo::EventListener listener = Echo::getEventListener();
	//std::shared_ptr<EchoObject> eoj
	//listener.onNewEchoObject(this);
}

std::shared_ptr<EchoNode> EchoObject::getNode() {
	return mNode;
}

void EchoObject::removeNode() {
	mNode = std::shared_ptr<EchoNode>();
}


bool EchoObject::isProxy() {
	std::shared_ptr<EchoNode> node = getNode();
	if(node.get() == NULL) {
		return true;
	}
	return node.get()->isProxy();
}

bool EchoObject::isSelfObject() {
	std::shared_ptr<EchoNode> node = getNode();
	if(node.get() == NULL) {
		return false;
	}
	return node.get()->isSelfNode();
}

bool EchoObject::setProperty(EchoProperty& property) {
	return false;
}

std::shared_ptr<std::vector<unsigned char> > EchoObject::getProperty(unsigned char epc) {
	return std::shared_ptr<std::vector<unsigned char> >();
}

bool EchoObject::isValidProperty(EchoProperty& property) {
	return false;
}

void EchoObject::setReceiver(std::shared_ptr<EchoObject::Receiver> receiver) {
	mReceiver = receiver;
}

EchoFrame EchoObject::onReceiveRequest(EchoFrame& frame) {
	// receive response
	/*
	switch(frame.getESV()) {
	case EchoFrame::ESV_SET_RES: case EchoFrame::ESV_SETI_SNA: case EchoFrame::ESV_SETC_SNA:
	case EchoFrame::ESV_GET_RES: case EchoFrame::ESV_GET_SNA:
	case EchoFrame::ESV_INF: case EchoFrame::ESV_INF_SNA:
	case EchoFrame::ESV_INFC:
	case EchoFrame::ESV_INFC_RES:
		if(mReceiver.get() != NULL) {
			mReceiver.get()->receive(frame);
		}
		return;
	}*/

	// receive request
	unsigned char esv;

	switch(frame.getESV()) {
	case EchoFrame::ESV_SETI:
		esv = EchoFrame::ESV_SET_NO_RES;
		break;
	case EchoFrame::ESV_SETC:
		esv = EchoFrame::ESV_SET_RES;
		break;
	case EchoFrame::ESV_GET:
		esv = EchoFrame::ESV_GET_RES;
		break;
	case EchoFrame::ESV_INF_REQ:
		esv = EchoFrame::ESV_INF;
		break;
	case EchoFrame::ESV_INFC:
		esv = EchoFrame::ESV_INFC_RES;
		break;
	case EchoFrame::ESV_SET_GET:
		esv = EchoFrame::ESV_SET_GET_SNA;
		break;
	}
	EchoFrame response(frame.getDstEchoClassCode(), frame.getDstEchoInstanceCode()
			, frame.getSrcEchoClassCode(), frame.getSrcEchoInstanceCode()
			, frame.getSrcEchoAddress(), esv);
	response.setTID(frame.getTID());
	switch(frame.getESV()) {
	case EchoFrame::ESV_SETI:
	case EchoFrame::ESV_SETC:
		for(int pidx = 0; pidx < frame.getPropertyList().size(); pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			onReceiveSetRequest(p, response);
		}
		break;
	case EchoFrame::ESV_GET:
	case EchoFrame::ESV_INF_REQ:
		for(int pidx = 0; pidx < frame.getPropertyList().size(); pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			onReceiveGetRequest(p.epc, response);
		}
		break;
	case EchoFrame::ESV_INFC:
		for(int pidx = 0; pidx < frame.getPropertyList().size(); pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			response.addPropertyForResponse(p.epc);
		}
		break;
	}
/*
	switch(frame.getESV()) {
	case EchoFrame::ESV_SETI_SNA:
	case EchoFrame::ESV_SET_RES: case EchoFrame::ESV_SETC_SNA:
	case EchoFrame::ESV_GET_RES: case EchoFrame::ESV_GET_SNA:
	case EchoFrame::ESV_INF_SNA:
	case EchoFrame::ESV_INFC_RES:
		break;
	case EchoFrame::ESV_INF:
		//response.setDstEchoAddress(EchoSocket::MULTICAST_ADDRESS);
		break;
	case EchoFrame::ESV_SET_GET_SNA:
		//EchoSocket::sendUDPFrame(frame);
		break;
	}*/
	return response;

}

EchoObject::Setter EchoObject::set() {
	return EchoObject::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), true);
}

EchoObject::Setter EchoObject::set(bool responseRequired) {
	return EchoObject::Setter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress(), responseRequired);
}

EchoObject::Getter EchoObject::get() {
	return EchoObject::Getter(getEchoClassCode(), getInstanceCode()
			, getNode().get()->getAddress());
}

EchoObject::Informer EchoObject::inform() {

	std::string address;
	if(isSelfObject()) {
		address = EchoSocket::MULTICAST_ADDRESS;
	} else {
		address = getNode().get()->getAddress();
	}
	return EchoObject::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

void EchoObject::setupPropertyMaps() {
}
void EchoObject::onReceiveSetRequest(EchoProperty& property,
		EchoFrame& response) {
	bool success = false;
	if(mSetProperties.get()->find(property.epc) == mSetProperties.get()->end()) {
		// not contains
		success = false;
	} else {
		// contains
		bool valid = isValidProperty(property);
		// event listner
		if(valid) {
			success = setProperty(property);
			// event listner
		} else {
			success = false;
		}

	}
	if(success) {
		response.addPropertyForResponse(property.epc);
	} else {
		response.addPropertyForResponse(property.epc, property.edt);
	}

}

void EchoObject::addStatusChangeAnnouncementProperty(unsigned char epc) {
	mAnnouncementProperties.get()->insert(epc);
}

void EchoObject::removeStatusChangeAnnouncementProperty(unsigned char epc) {
	mAnnouncementProperties.get()->erase(epc);
}

void EchoObject::clearStatusChangeAnnouncementProperties() {
	mAnnouncementProperties.get()->clear();
}

std::shared_ptr<std::set<unsigned char> > EchoObject::getStatusChangeAnnouncementProperties() {
	return mAnnouncementProperties;
}

void EchoObject::addSetProperty(unsigned char epc) {
	mSetProperties.get()->insert(epc);
}

void EchoObject::removeSetProperty(unsigned char epc) {
	mSetProperties.get()->erase(epc);
}

void EchoObject::clearSetProperties() {
	mSetProperties.get()->clear();
}

std::shared_ptr<std::set<unsigned char> > EchoObject::getSetProperties() {
	return mSetProperties;
}

void EchoObject::addGetProperty(unsigned char epc) {
	mGetProperties.get()->insert(epc);
}

void EchoObject::removeGetProperty(unsigned char epc) {
	mGetProperties.get()->erase(epc);
}

void EchoObject::clearGetProperties() {
	mGetProperties.get()->clear();
}

std::shared_ptr<std::set<unsigned char> > EchoObject::getGetProperties() {
	return mGetProperties;
}

void EchoObject::onNew(std::shared_ptr<EchoObject> eoj) {
	init();
	Echo::getEventListenerDelegate().onNewEchoObject(eoj);
}

void EchoObject::onFound(std::shared_ptr<EchoObject> eoj) {
	Echo::getEventListenerDelegate().onFoundEchoObject(eoj);
}

void EchoObject::onReceiveGetRequest(unsigned char epc, EchoFrame& response) {

	std::shared_ptr<std::vector<unsigned char> > edt;
	if(response.getESV() == EchoFrame::ESV_GET_RES
			|| response.getESV() == EchoFrame::ESV_GET_SNA) {
		if(mGetProperties.get()->find(epc) == mGetProperties.get()->end()) {
			// not contains
			//edt = 0;
		} else {
			// contains
			edt = getProperty(epc);
			// event listner

		}

	} else {
		edt = getProperty(epc);
		// event listner

	}

	bool valid = false;
	if(edt.get() != nullptr) {
		EchoProperty property(epc, *(edt.get()));

		valid = isValidProperty(property);
	}
	//EchoProperty property(epc, edt);

	//bool valid = isValidProperty(property);
	// event listner
	if(valid) {
		response.addPropertyForResponse(epc, *(edt.get()));
	} else {
		response.addPropertyForResponse(epc);
	}

}

EchoObject::Informer EchoObject::inform(bool multicast) {
	std::string address;
	if(multicast) {
		address = EchoSocket::MULTICAST_ADDRESS;
	} else {
		address = getNode().get()->getAddress();
	}
	return EchoObject::Informer(getEchoClassCode(), getInstanceCode()
			, address, isSelfObject());
}

EchoObject::InformerC EchoObject::informC(std::string address) {
	return EchoObject::InformerC(getEchoClassCode(), getInstanceCode()
			, address);
}

EchoObject::Receiver::Receiver() {
}

EchoObject::Receiver::~Receiver() {
}

bool EchoObject::Receiver::onSetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid,
		unsigned char esv, EchoProperty& property, bool success) {
	return false;
}

bool EchoObject::Receiver::onGetProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid,
		unsigned char esv, EchoProperty& property, bool success) {
	return false;
}

void EchoObject::Receiver::onReceive(std::shared_ptr<EchoObject> eoj, EchoFrame& frame) {
	onReceiveFrame(eoj, frame);

	switch(frame.getESV()) {
	case EchoFrame::ESV_SET_RES: case EchoFrame::ESV_SETI_SNA: case EchoFrame::ESV_SETC_SNA:
		for(int pidx = 0; pidx < frame.getPropertyList().size(); pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			onSetProperty(eoj, frame.getTID(), frame.getESV(), p, (p.pdc == 0));
		}
		break;
	case EchoFrame::ESV_GET_RES: case EchoFrame::ESV_GET_SNA:
	case EchoFrame::ESV_INF: case EchoFrame::ESV_INF_SNA:
	case EchoFrame::ESV_INFC:
		for(int pidx = 0; pidx < frame.getPropertyList().size(); pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			onGetProperty(eoj, frame.getTID(), frame.getESV(), p, (p.pdc != 0));
		}
		break;
	case EchoFrame::ESV_INFC_RES:
		for(int pidx = 0; pidx < frame.getPropertyList().size(); pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			onInformProperty(eoj, frame.getTID(), frame.getESV(), p);
		}
		break;
	}
}

void EchoObject::Receiver::onReceiveFrame(std::shared_ptr<EchoObject> eoj, EchoFrame& frame) {
}

bool EchoObject::Receiver::onInformProperty(std::shared_ptr<EchoObject> eoj, unsigned short tid,
		unsigned char esv, EchoProperty& property) {
	return false;
}

EchoObject::Sender::Sender(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
		, unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
		, std::string dstEchoAddress, unsigned char esv)
	: mSrcEchoClassCode(srcEchoClassCode), mSrcEchoInstanceCode(srcEchoInstanceCode)
	, mDstEchoClassCode(dstEchoClassCode), mDstEchoInstanceCode(dstEchoInstanceCode)
	, mDstEchoAddress(dstEchoAddress), mESV(esv) {
}

EchoObject::Sender::~Sender() {
}

void EchoObject::Sender::setSeoj(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode) {
	mSrcEchoClassCode = srcEchoClassCode;
	mSrcEchoInstanceCode = srcEchoInstanceCode;
}

void EchoObject::Sender::setDeoj(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
		, std::string dstEchoAddress) {
	mDstEchoClassCode = dstEchoClassCode;
	mDstEchoInstanceCode = dstEchoInstanceCode;
	mDstEchoAddress = dstEchoAddress;
}

void EchoObject::Sender::send(EchoFrame& frame) {
	unsigned short tid = EchoSocket::nextTID();
	frame.setTID(tid);
	EchoSocket::sendUDPFrame(frame);
}

void EchoObject::Sender::sendTCP(EchoFrame& frame) {
	unsigned short tid = EchoSocket::nextTID();
	frame.setTID(tid);
	//EchoSocket::sendTCPFrame(frame);
}

EchoObject::Setter::Setter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
		, std::string dstEchoAddress, bool responseRequired)
	: EchoObject::Sender(NodeProfile::ECHO_CLASS_CODE
	, Echo::getSelfNode()->getNodeProfile()->getInstanceCode()
	, dstEchoClassCode, dstEchoInstanceCode, dstEchoAddress
	, responseRequired ? EchoFrame::ESV_SETC : EchoFrame::ESV_SETI) {
}

EchoObject::Setter::~Setter() {
}

EchoFrame EchoObject::Setter::send() {
	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);

	for(int pidx = 0; pidx < mPropertyList.size(); pidx++) {
		EchoProperty p = mPropertyList.at(pidx);
		frame.addProperty(p);
	}
	Sender::send(frame);
	return frame;
}

EchoFrame EchoObject::Setter::sendTCP() {
	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);

	for(int pidx = 0; pidx < mPropertyList.size(); pidx++) {
		EchoProperty p = mPropertyList.at(pidx);
		frame.addProperty(p);
	}
	Sender::sendTCP(frame);
	return frame;
}

EchoObject::Setter& EchoObject::Setter::reqSetProperty(unsigned char epc,
		std::vector<unsigned char> edt) {
	mPropertyList.push_back(EchoProperty(epc, edt));
	return (*this);
}

EchoObject::Getter::Getter(unsigned short dstEchoClassCode, unsigned char dstEchoInstanceCode
		, std::string dstEchoAddress)
	: EchoObject::Sender(NodeProfile::ECHO_CLASS_CODE
	, Echo::getSelfNode()->getNodeProfile()->getInstanceCode()
	, dstEchoClassCode, dstEchoInstanceCode, dstEchoAddress
	, EchoFrame::ESV_GET) {
}

EchoObject::Getter::~Getter() {
}

EchoFrame EchoObject::Getter::send() {

	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);


	for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
		unsigned char epc = mEPCList.at(eidx);
		frame.addProperty(EchoProperty(epc));
	}
	Sender::send(frame);
	return frame;
}

EchoFrame EchoObject::Getter::sendTCP() {
	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);


	for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
		unsigned char epc = mEPCList.at(eidx);
		frame.addProperty(EchoProperty(epc));
	}
	Sender::sendTCP(frame);
	return frame;
}

EchoObject::Getter& EchoObject::Getter::reqGetProperty(unsigned char epc) {
	mEPCList.push_back(epc);
	return (*this);
}

EchoObject::Informer::Informer(unsigned short echoClassCode, unsigned char echoInstanceCode
		, std::string dstEchoAddress, bool isSelfObject)
	: EchoObject::Sender
	( isSelfObject ? echoClassCode : NodeProfile::ECHO_CLASS_CODE
	, isSelfObject ? echoInstanceCode : Echo::getSelfNode()->getNodeProfile()->getInstanceCode()
	, isSelfObject ? NodeProfile::ECHO_CLASS_CODE : echoClassCode
	, isSelfObject ? NodeProfile::INSTANCE_CODE : echoInstanceCode
	, dstEchoAddress
	, isSelfObject ? EchoFrame::ESV_INF : EchoFrame::ESV_INF_REQ) {
}

EchoObject::Informer::~Informer() {
}

EchoFrame EchoObject::Informer::send() {

	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);

	if(mESV == EchoFrame::ESV_INF_REQ) {

		for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
			unsigned char epc = mEPCList.at(eidx);
			frame.addProperty(EchoProperty(epc));
		}
	} else {
		std::shared_ptr<EchoNode> node = Echo::getSelfNode();
		if(node.get() == NULL) {
			return frame;
		}
		std::shared_ptr<EchoObject> seoj = node.get()->getInstance(mSrcEchoClassCode, mSrcEchoInstanceCode);
		if(seoj.get() == NULL) {
			return frame;
		}

		for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
			unsigned char epc = mEPCList.at(eidx);
			std::shared_ptr<std::vector<unsigned char> > edt = seoj.get()->getProperty(epc);

			if(edt.get() != nullptr) {
				EchoProperty property(epc, *(edt.get()));

				if(seoj.get()->isValidProperty(property)) {
					frame.addProperty(property);
				}
			}
		}
	}

	Sender::send(frame);
	return frame;
}

EchoFrame EchoObject::Informer::sendTCP() {

	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);

	if(mESV == EchoFrame::ESV_INF_REQ) {
		for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
			unsigned char epc = mEPCList.at(eidx);
			frame.addProperty(EchoProperty(epc));
		}
	} else {
		std::shared_ptr<EchoNode> node = Echo::getSelfNode();
		if(node.get() == NULL) {
			return frame;
		}
		std::shared_ptr<EchoObject> seoj = node.get()->getInstance(mSrcEchoClassCode, mSrcEchoInstanceCode);
		if(seoj.get() == NULL) {
			return frame;
		}

		for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
			unsigned char epc = mEPCList.at(eidx);
			std::shared_ptr<std::vector<unsigned char> > edt = seoj.get()->getProperty(epc);
			if(edt.get() != nullptr) {
				EchoProperty property(epc, *(edt.get()));

				if(seoj.get()->isValidProperty(property)) {
					frame.addProperty(property);
				}
			}
		}
	}

	Sender::sendTCP(frame);
	return frame;
}

EchoObject::Informer& EchoObject::Informer::reqInformProperty(unsigned char epc) {
	mEPCList.push_back(epc);
	return (*this);
}

EchoObject::InformerC::InformerC(unsigned short srcEchoClassCode, unsigned char srcEchoInstanceCode
		, std::string dstEchoAddress)
	: EchoObject::Sender(NodeProfile::ECHO_CLASS_CODE
	, Echo::getSelfNode()->getNodeProfile()->getInstanceCode()
	, NodeProfile::ECHO_CLASS_CODE, NodeProfile::INSTANCE_CODE, dstEchoAddress
	, EchoFrame::ESV_INFC) {
}

EchoObject::InformerC::~InformerC() {
}

EchoFrame EchoObject::InformerC::send() {

	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);

	std::shared_ptr<EchoNode> node = Echo::getSelfNode();
	if(node.get() == NULL) {
		return frame;
	}
	std::shared_ptr<EchoObject> seoj = node.get()->getInstance(mSrcEchoClassCode, mSrcEchoInstanceCode);
	if(seoj.get() == NULL) {
		return frame;
	}
	for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
		unsigned char epc = mEPCList.at(eidx);
		std::shared_ptr<std::vector<unsigned char> > edt = seoj.get()->getProperty(epc);

		if(edt.get() != nullptr) {
			EchoProperty property(epc, *(edt.get()));

			if(seoj.get()->isValidProperty(property)) {
				frame.addProperty(property);
			}
		}
	}

	Sender::send(frame);
	return frame;
}

EchoFrame EchoObject::InformerC::sendTCP() {

	EchoFrame frame(mSrcEchoClassCode, mSrcEchoInstanceCode
			, mDstEchoClassCode, mDstEchoInstanceCode
			, mDstEchoAddress, mESV);

	std::shared_ptr<EchoNode> node = Echo::getSelfNode();
	if(node.get() == NULL) {
		return frame;
	}
	std::shared_ptr<EchoObject> seoj = node.get()->getInstance(mSrcEchoClassCode, mSrcEchoInstanceCode);
	if(seoj.get() == NULL) {
		return frame;
	}
	for(int eidx = 0; eidx < mEPCList.size(); eidx++) {
		unsigned char epc = mEPCList.at(eidx);
		std::shared_ptr<std::vector<unsigned char> > edt = seoj.get()->getProperty(epc);

		if(edt.get() != nullptr) {
			EchoProperty property(epc, *(edt.get()));

			if(seoj.get()->isValidProperty(property)) {
				frame.addProperty(property);
			}
		}
	}

	Sender::sendTCP(frame);
	return frame;
}

EchoObject::InformerC& EchoObject::InformerC::reqInformProperty(unsigned char epc) {
	mEPCList.push_back(epc);
	return (*this);
}

std::shared_ptr<EchoObject::Receiver> EchoObject::getReceiver() {
	return mReceiver;
}

};

