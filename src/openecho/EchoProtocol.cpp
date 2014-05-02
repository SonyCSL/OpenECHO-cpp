/*
 * EchoProtocol.cpp
 *
 *  Created on: 2014/03/17
 *      Author: Fumiaki
 */

#include "EchoProtocol.h"
#include "OpenECHO.h"


namespace sonycsl_openecho {

EchoProtocol::EchoProtocol() {
	// TODO Auto-generated constructor stub

}

EchoProtocol::~EchoProtocol() {
	// TODO Auto-generated destructor stub
}

EchoTask::EchoTask(EchoFrame frame) : mFrame(new EchoFrame(frame)){
}

EchoTask::~EchoTask() {
	delete mFrame;
}

void EchoTask::perform() {
	std::cerr << "perform" << std::endl;
	checkObjectInFrame();
	if(isReportFrame()) {
		std::cerr << "report" << std::endl;

		onReceiveReport();
	}
	if(isRequestFrame()) {
		std::cerr << "request" << std::endl;

		std::vector<EchoFrame> responses = onReceiveRequest();
		for(EchoFrame res : responses) {

			if(res.getESV() == EchoFrame::ESV_SET_NO_RES) {
				return;
			}
			if(res.getESV() == EchoFrame::ESV_INF) {
				res.setDstEchoAddress(EchoSocket::MULTICAST_ADDRESS);
				informAll(res);
			} else {
				respond(res);
			}
		}
	}
}

bool EchoTask::isRequestFrame() {
	switch(mFrame->getESV()) {
	case EchoFrame::ESV_SETI: case EchoFrame::ESV_SETC:
	case EchoFrame::ESV_GET:
	case EchoFrame::ESV_INF_REQ:
	case EchoFrame::ESV_SET_GET:
	case EchoFrame::ESV_INFC:
		return true;
	default:
		return false;
	}
}

bool EchoTask::isReportFrame() {
	switch(mFrame->getESV()) {
	case EchoFrame::ESV_SETI_SNA:
	case EchoFrame::ESV_SET_RES: case EchoFrame::ESV_SETC_SNA:
	case EchoFrame::ESV_GET_RES: case EchoFrame::ESV_GET_SNA:
	case EchoFrame::ESV_INF: case EchoFrame::ESV_INF_SNA:
	case EchoFrame::ESV_INFC_RES:
	case EchoFrame::ESV_INFC:
		return true;
	default:
		return false;
	}
}

std::vector<EchoFrame> EchoTask::onReceiveRequest() {

	std::vector<EchoFrame> responses;
	std::shared_ptr<EchoNode> selfNode = Echo::getSelfNode();
	if(selfNode.get() == nullptr) {
		return responses;
	}
	if(mFrame->getDstEchoInstanceCode() == 0) {
		if(mFrame->getDstEchoClassCode() == NodeProfile::ECHO_CLASS_CODE) {
			std::shared_ptr<EchoObject> deoj = selfNode.get()->getNodeProfile();
			EchoFrame res = onReceiveRequest(deoj);
			responses.push_back(res);
		} else {
			//DeviceObject[] deojList = selfNode.getDevices(frame.getDstEchoClassCode());
			std::vector<std::shared_ptr<DeviceObject> > deojList = selfNode.get()->getDevices(mFrame->getDstEchoClassCode());
			for(std::shared_ptr<DeviceObject> deoj : deojList) {
				EchoFrame res = onReceiveRequest(deoj);
				responses.push_back(res);
			}
		}
	} else {
		std::shared_ptr<EchoObject> deoj = selfNode.get()->getInstance(mFrame->getDstEchoClassCode(), mFrame->getDstEchoInstanceCode());
		if(deoj.get() == nullptr) {return responses;}
		EchoFrame res = onReceiveRequest(deoj);
		responses.push_back(res);
	}
	return responses;
}

EchoFrame EchoTask::onReceiveRequest(
		std::shared_ptr<EchoObject> deoj) {
	EchoFrame request = *mFrame; // copy
	request.setDstEchoInstanceCode(deoj.get()->getInstanceCode());
	EchoFrame response = deoj.get()->onReceiveRequest(request);

	return response;
}

void EchoTask::onReceiveReport() {
	std::shared_ptr<EchoNode> node  = Echo::getNode(mFrame->getSrcEchoAddress());
	std::shared_ptr<EchoObject> seoj = node.get()->getInstance(
			mFrame->getSrcEchoClassCode(), mFrame->getSrcEchoInstanceCode());

	if(seoj.get() == nullptr) {
		return;
	}

	std::shared_ptr<EchoObject::Receiver> receiver = seoj.get()->getReceiver();
	if(receiver.get() != nullptr) {
		receiver.get()->onReceive(seoj, *mFrame);
	}
}

void EchoTask::respond(const EchoFrame& response) {
}

void EchoTask::informAll(const EchoFrame& response) {
}

void EchoTask::checkObjectInFrame() {
	if(EchoSocket::SELF_ADDRESS == mFrame->getSrcEchoAddress()) {
		// self node
		return;
	}

	// other node
	std::shared_ptr<EchoNode> node = Echo::getNode(mFrame->getSrcEchoAddress());
	bool flagNewNode = false;
	if(node.get() == nullptr) {
		node = Echo::addOtherNode(mFrame->getSrcEchoAddress());
		flagNewNode = true;
		if(node.get() == nullptr) {return;}

		node.get()->getNodeProfile().get()->setNode(node);
	}

	if(mFrame->getSrcEchoClassCode() == NodeProfile::ECHO_CLASS_CODE
		&& mFrame->getSrcEchoInstanceCode() == NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY) {
		std::shared_ptr<NodeProfile> profile = node.get()->getNodeProfile();
		NodeProfile::Proxy* proxy = dynamic_cast<NodeProfile::Proxy *>(profile.get());
		proxy->setInstanceCode(NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY);
	}

	bool flagNewDevice = false;
	std::shared_ptr<EchoObject> seoj = node.get()->getInstance(mFrame->getSrcEchoClassCode(), mFrame->getSrcEchoInstanceCode());
	if(seoj.get() == nullptr) {
		// generate
		// device

		seoj = node.get()->addOtherDevice(mFrame->getSrcEchoClassCode(), mFrame->getSrcEchoInstanceCode());
		flagNewDevice = true;

		if(seoj.get() == nullptr) {
			if(flagNewNode) {
				node.get()->onNew();
			}
			node.get()->onFound();
			return;
		} else {seoj.get()->setNode(node);}
	}
	if(seoj.get()->getEchoClassCode() == NodeProfile::ECHO_CLASS_CODE
		&& (seoj.get()->getInstanceCode() == NodeProfile::INSTANCE_CODE
			|| seoj.get()->getInstanceCode() == NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY)
		&& (mFrame->getESV() == EchoFrame::ESV_GET_RES
			|| mFrame->getESV() == EchoFrame::ESV_GET_SNA
			|| mFrame->getESV() == EchoFrame::ESV_INF
			|| mFrame->getESV() == EchoFrame::ESV_INF_SNA
			|| mFrame->getESV() == EchoFrame::ESV_INFC)) {
		// seoj is NodeProfile
		std::vector<std::shared_ptr<EchoObject> > foundDevices;
		std::vector<char> flagNewDevices;
		char TRUE = 1;
		char FALSE = 0;

		for(EchoProperty p : mFrame->getPropertyList()) {
			if(p.epc != NodeProfile::EPC_INSTANCE_LIST_NOTIFICATION
					&& p.epc != NodeProfile::EPC_SELF_NODE_INSTANCE_LIST_S) {continue;}
			if(p.pdc == 0) {continue;}
			int deviceListSize = (int)p.edt[0];
			if(deviceListSize > 84) {
				deviceListSize = 84;
			}
			for(int d = 0, i = 1; d < deviceListSize; d++) {
				if(i == p.pdc) break;
				unsigned short echoClassCode = (unsigned short)(((p.edt[i]) & 0xFF) << 8);
				i += 1;
				if(i == p.pdc) break;
				echoClassCode += p.edt[i] & 0xFF;
				i += 1;
				if(i == p.pdc) break;
				unsigned char echoInstanceCode = p.edt[i];
				i += 1;
				if(node.get()->containsDevice(echoClassCode, echoInstanceCode)) {
					flagNewDevices.push_back(FALSE);
					foundDevices.push_back(node.get()->getInstance(echoClassCode, echoInstanceCode));
				} else {
					// new
					flagNewDevices.push_back(TRUE);
					std::shared_ptr<EchoObject> eoj = node.get()->addOtherDevice(echoClassCode, echoInstanceCode);
					foundDevices.push_back(eoj);
					if(eoj.get() != nullptr) {eoj->setNode(node);}
				}
			}
		}

		if(flagNewNode) {
			node.get()->onNew();
		}
		node.get()->onFound();
		if(flagNewDevice) {
			seoj.get()->onNew();
		}
		seoj.get()->onFound();
		int foundDeviceListSize = foundDevices.size();
		for(int i = 0; i < foundDeviceListSize; i++) {
			if(flagNewDevices.at(i) == TRUE) {
				//Echo.getEventListener().onNewEchoObject(foundDevices.get(i));
				foundDevices.at(i).get()->onNew();
			}
			//Echo.getEventListener().onFoundEchoObject(foundDevices.get(i));
			foundDevices.at(i).get()->onFound();
		}
	} else {
		// seoj is DeviceObject
		if(flagNewNode) {
			//Echo.getEventListener().onNewNode(node);
			node.get()->onNew();
		}
		//Echo.getEventListener().onFoundNode(node);
		node.get()->onFound();
		if(flagNewDevice) {
			//Echo.getEventListener().onNewEchoObject(seoj);
			seoj.get()->onNew();
		}
		//Echo.getEventListener().onFoundEchoObject(seoj);
		seoj.get()->onFound();
		return;
	}
}

};
