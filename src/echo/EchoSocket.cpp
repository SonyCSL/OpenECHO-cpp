/*
 * EchoSocket.cpp
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */
#include "OpenECHO.h"

#include "EchoSocket.h"

const std::string EchoSocket::SELF_ADDRESS = "127.0.0.1";
const std::string EchoSocket::MULTICAST_ADDRESS = "224.0.23.0";
bool EchoSocket::sRunningReceiverThread = false;
unsigned short EchoSocket::sNextTID= 0;
std::queue<EchoFrame> EchoSocket::sSelfFrameQueue;


int EchoSocket::sReceiverSock = 0;
struct sockaddr_in EchoSocket::sReceiverSockAddr;
struct ip_mreq EchoSocket::sReceiverIpMreq;

EchoSocket::EchoSocket() {
	// TODO Auto-generated constructor stub

}

EchoSocket::~EchoSocket() {
	// TODO Auto-generated destructor stub
}


void EchoSocket::openSocket() {

	sNextTID = Echo::getStorage().get()->getInitialTID();
	sReceiverSock = socket(AF_INET, SOCK_DGRAM, 0);

	sReceiverSockAddr.sin_family = AF_INET;
	sReceiverSockAddr.sin_port = htons(PORT);
	sReceiverSockAddr.sin_addr.s_addr = INADDR_ANY;


	bind(sReceiverSock, (struct sockaddr *)&sReceiverSockAddr, sizeof(sReceiverSockAddr));

	int val = 1;
	ioctl(sReceiverSock, FIONBIO, &val);

	memset(&sReceiverIpMreq, 0, sizeof(sReceiverIpMreq));
	sReceiverIpMreq.imr_interface.s_addr = INADDR_ANY;
	sReceiverIpMreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDRESS.c_str());

	u_char loop = 0; // 0 = invalid, 1 = valid(default);
	if(setsockopt(sReceiverSock
			, IPPROTO_IP
			, IP_MULTICAST_LOOP
			, &loop
			, sizeof(loop)) != 0) {
		perror("EchoSocket::start()[IP_MULTICAST_LOOP]");
		return;
	}
	if (setsockopt(sReceiverSock
		, IPPROTO_IP
		, IP_ADD_MEMBERSHIP
		, (char *)&sReceiverIpMreq
		, sizeof(sReceiverIpMreq)) != 0) {
		perror("EchoSocket::start()[IP_ADD_MEMBERSHIP]");
		return;
	}

	startReceiverThread();
}

void EchoSocket::closeSocket() {
	stopReceiverThread();
	close(sReceiverSock);
	//shutdown(sReceiverSock);
}
void EchoSocket::sendFrameToSelfNode(EchoFrame& frame) {
	//receiveUDPFrame(frame);
	sSelfFrameQueue.push(frame);
}

void EchoSocket::receiveFrameFromSelfNode() {
	if(!sSelfFrameQueue.empty()) {
		std::cerr << "receiveFrameFromeSelfNode" << std::endl;
		onReceiveUDPFrame(sSelfFrameQueue.front());
		sSelfFrameQueue.pop();
	}
}

void EchoSocket::onReceiveUDPFrame(EchoFrame& frame) {

	switch(frame.getESV()) {
	case EchoFrame::ESV_SETI_SNA:
	case EchoFrame::ESV_SET_RES: case EchoFrame::ESV_SETC_SNA:
	case EchoFrame::ESV_GET_RES: case EchoFrame::ESV_GET_SNA:
	case EchoFrame::ESV_INF: case EchoFrame::ESV_INF_SNA:
	case EchoFrame::ESV_INFC_RES:
		// not request
		onReceiveNotRequest(frame);
		break;
	case EchoFrame::ESV_INFC:
		onReceiveNotRequest(frame);
	case EchoFrame::ESV_SETI: case EchoFrame::ESV_SETC:
	case EchoFrame::ESV_GET:
	case EchoFrame::ESV_INF_REQ:
	case EchoFrame::ESV_SET_GET:
		// request
		std::shared_ptr<EchoNode> selfNode = Echo::getSelfNode();
		if(selfNode.get() == NULL) {
			return;
		}
		//std::vector<std::shared_ptr<EchoObject> > deojList;
		if(frame.getDstEchoInstanceCode() == 0) {
			if(frame.getDstEchoClassCode() == NodeProfile::ECHO_CLASS_CODE) {
				std::shared_ptr<EchoObject> deoj = selfNode.get()->getNodeProfile();

				onReceiveUDPRequsetFrame(deoj, frame);

			} else {
				std::vector<std::shared_ptr<DeviceObject> > deojList = selfNode.get()->getDevices(frame.getDstEchoClassCode());
				int deojListSize = deojList.size();
				for(int i = 0; i < deojListSize; i++) {
					std::shared_ptr<DeviceObject> deoj = deojList.at(i);
					onReceiveUDPRequsetFrame(deoj, frame);
				}

				return;
			}
		} else {
			std::shared_ptr<EchoObject> deoj = selfNode.get()->getInstance(frame.getDstEchoClassCode(), frame.getDstEchoInstanceCode());
			if(deoj.get() == NULL){
				return;
			}

			onReceiveUDPRequsetFrame(deoj, frame);
			return;
		}
		break;
	}
}

void EchoSocket::onReceiveUDPRequsetFrame(
		const std::shared_ptr<EchoObject> deoj, EchoFrame& frame) {

	EchoFrame request = frame;
	request.setDstEchoInstanceCode(deoj.get()->getInstanceCode());
	EchoFrame response = deoj.get()->onReceiveRequest(request);
	if(response.getESV() == EchoFrame::ESV_INF) {
		response.setDstEchoAddress(MULTICAST_ADDRESS);
	}
	if(response.getESV() == EchoFrame::ESV_SET_NO_RES) {
		continue;
	}
	sendUDPFrame(response);
}

void EchoSocket::onReceiveNotRequest(EchoFrame& frame) {

	std::shared_ptr<EchoNode> node = Echo::getNode(frame.getSrcEchoAddress());
	bool flagNewNode = false;
	if(node.get() == nullptr) {
		// generate
		node = Echo::addOtherNode(frame.getSrcEchoAddress());
		flagNewNode = true;

		//node = Echo::getNode(frame.getSrcEchoAddress());
		if(node.get() == nullptr) {return;}

		node.get()->getNodeProfile().get()->setNode(node);

	}

	if(frame.getSrcEchoClassCode() == NodeProfile::ECHO_CLASS_CODE
			&& frame.getSrcEchoInstanceCode() == NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY) {
		//node.get()->getNodeProfile().get()->setInstanceCode(NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY);
		NodeProfile* profile = node.get()->getNodeProfile().get();
		NodeProfile::Proxy* proxy = dynamic_cast<NodeProfile::Proxy *> (profile);
		if(proxy) {
			proxy->setInstanceCode(NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY);
		}
	}

	bool flagNewDevice = false;
	std::shared_ptr<EchoObject> seoj = node.get()->getInstance(frame.getSrcEchoClassCode(), frame.getSrcEchoInstanceCode());
	if(seoj.get() == nullptr) {
		// generate
		// device

		seoj = node.get()->addOtherDevice(frame.getSrcEchoClassCode(), frame.getSrcEchoInstanceCode());
		flagNewDevice = true;

		if(seoj.get() != nullptr) {seoj.get()->setNode(node);}

		//seoj = node.get()->getInstnace(frame.getSrcEchoClassCode(), frame.getSrcEchoInstanceCode());
	}

	// check new node or instance
	checkNewObjectInResponse(frame, node, seoj, flagNewNode, flagNewDevice);

	if(seoj.get() == nullptr) {return;}
	seoj.get()->setNode(node);

	// receiver
	std::shared_ptr<EchoObject::Receiver> receiver = seoj.get()->getReceiver();
	if(receiver.get() != nullptr) {
		receiver.get()->onReceive(seoj, frame);
	}
}

void EchoSocket::checkNewObjectInResponse(EchoFrame& frame,
		const std::shared_ptr<EchoNode> node,
		const std::shared_ptr<EchoObject> seoj, const bool flagNewNode,
		const bool flagNewDevice) {
	if(seoj.get() == NULL) {
		if(flagNewNode) {
			Echo::getEventListener().onNewNode(node);
		}
		Echo::getEventListener().onFoundNode(node);
		return;
	}
	if(seoj.get()->getEchoClassCode() == NodeProfile::ECHO_CLASS_CODE
			&& (seoj.get()->getInstanceCode() == NodeProfile::INSTANCE_CODE
				|| seoj.get()->getInstanceCode() == NodeProfile::INSTANCE_CODE_TRANSMISSION_ONLY)
			&& (frame.getESV() == EchoFrame::ESV_GET_RES
				|| frame.getESV() == EchoFrame::ESV_GET_SNA
				|| frame.getESV() == EchoFrame::ESV_INF
				|| frame.getESV() == EchoFrame::ESV_INF_SNA
				|| frame.getESV() == EchoFrame::ESV_INFC)) {
		// seoj is NodeProfile
		std::vector<std::shared_ptr<EchoObject> > foundDevices;
		std::vector<bool> flagNewDevices;

		int propertyListSize = frame.getPropertyList().size();
		for(int pidx = 0; pidx < propertyListSize; pidx++) {
			EchoProperty p = frame.getPropertyList().at(pidx);
			if(p.epc != NodeProfile::EPC_INSTANCE_LIST_NOTIFICATION
				&& p.epc != NodeProfile::EPC_SELF_NODE_INSTANCE_LIST_S) {continue;}
			if(p.pdc == 0) {continue;}
			unsigned char deviceListSize = p.edt.at(0);
			if(deviceListSize > 84) {
				deviceListSize = 84;
			}
			for(unsigned char d = 0, i = 1; d < deviceListSize; d++) {
				if(i == p.pdc) break;
				unsigned short echoClassCode = ((unsigned short)(p.edt.at(i))) << 8;
				i += 1;
				if(i == p.pdc) break;
				echoClassCode += p.edt.at(i);
				i += 1;
				if(i == p.pdc) break;
				unsigned char echoInstanceCode = p.edt.at(i);
				i += 1;
				if(node.get()->containsDevice(echoClassCode, echoInstanceCode)) {
					flagNewDevices.push_back(false);
					foundDevices.push_back(node.get()->getInstance(echoClassCode, echoInstanceCode));
				} else {
					// new
					flagNewDevices.push_back(true);
					std::shared_ptr<EchoObject> eoj = node.get()->addOtherDevice(echoClassCode, echoInstanceCode);
					foundDevices.push_back(eoj);
					if(eoj.get() != nullptr) {eoj.get()->setNode(node);}
				}
			}
		}

		if(flagNewNode) {
			Echo::getEventListener().onNewNode(node);
		}
		Echo::getEventListener().onFoundNode(node);
		if(flagNewDevice) {
			Echo::getEventListener().onNewEchoObject(seoj);
		}
		Echo::getEventListener().onFoundEchoObject(seoj);
		int foundDeviceListSize = foundDevices.size();
		for(int i = 0; i < foundDeviceListSize; i++) {
			if(flagNewDevices.at(i)) {
				Echo::getEventListener().onNewEchoObject(foundDevices.at(i));
			}
			Echo::getEventListener().onFoundEchoObject(foundDevices.at(i));
		}
	} else {
		// seoj is DeviceObject
		if(flagNewNode) {
			Echo::getEventListener().onNewNode(node);
		}
		Echo::getEventListener().onFoundNode(node);
		if(flagNewDevice) {
			Echo::getEventListener().onNewEchoObject(seoj);
		}
		Echo::getEventListener().onFoundEchoObject(seoj);
		return;
	}
}

void EchoSocket::sendUDPFrame(EchoFrame& frame) {

	if(frame.getDstEchoAddress() == SELF_ADDRESS) {
		sendFrameToSelfNode(frame);
		return;
	}
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(frame.getDstEchoAddress().c_str());

	if(frame.getDstEchoAddress() == MULTICAST_ADDRESS) {
		in_addr_t ipaddr = inet_addr(SELF_ADDRESS.c_str());

		if (setsockopt(sock,
				IPPROTO_IP,
				IP_MULTICAST_IF,
				(char *)&ipaddr, sizeof(ipaddr)) != 0) {
			perror("sendUDPFrame");
			return;
		 }
	}


	std::vector<unsigned char> byteArray = frame.getFrameByteArray();
	int size = byteArray.size();
	unsigned char buffer[size];
	for(int i = 0; i < size; i++) {
		buffer[i] = byteArray.at(i);
	}

	sendto(sock, buffer, 5, byteArray.size(), (struct sockaddr *)&addr, sizeof(addr));

	std::cerr << "sendUDPFrame:" << std::hex;
	for(int i = 0; i < size; i++) {
		std::cerr << (int)(buffer[i]) << " ";
	}
	std::cerr << std::endl;


	close(sock);
	if(frame.getDstEchoAddress() == MULTICAST_ADDRESS) {
		EchoFrame f = frame;
		f.setDstEchoAddress(SELF_ADDRESS);
		sendFrameToSelfNode(f);
	}


}

void EchoSocket::sendTCPFrame(EchoFrame& frame) {
}

void EchoSocket::receiveUDP() {
	int size;
	unsigned char buffer[UDP_MAX_PACKET_SIZE];

	struct sockaddr_in from;
	unsigned int addrSize = sizeof(struct sockaddr_in);
	memset(buffer, 0, sizeof(buffer));
	size = recvfrom(sReceiverSock, buffer, sizeof(buffer), 0,(struct sockaddr *)&from, &addrSize);
	if(size < EchoFrame::MIN_FRAME_SIZE) {
		return;
	}
	std::vector<unsigned char> data;
	for(int i = 0; i < size; i++) {
		data.push_back(buffer[i]);
	}

	std::cerr << "receiveUDPFrame:" << std::hex;
	for(int i = 0; i < size; i++) {
		std::cerr << (int)(buffer[i]) << " ";
	}
	std::cerr << std::endl;
	const char* caddress = inet_ntoa(from.sin_addr);
	std::string address = caddress;
	EchoFrame frame(address, data);
	onReceiveUDPFrame(frame);
}

void EchoSocket::startReceiverThread() {
	pthread_t thread;
	pthread_create(&thread, NULL, receive, NULL);
}

void EchoSocket::stopReceiverThread() {
	sRunningReceiverThread = false;
}

void* EchoSocket::receive(void*) {
	sRunningReceiverThread = true;
	while(sRunningReceiverThread) {
		receiveUDP();
		receiveFrameFromSelfNode();
		usleep(10000);
	}
	return 0;
}

void EchoSocket::resumeReceiverThread() {
}

void EchoSocket::pauseReceiverThread() {
}

unsigned short EchoSocket::nextTID() {
	unsigned short ret = sNextTID;
	sNextTID += 1;
	Echo::getStorage().get()->setNextTID(sNextTID);
	return ret;
}

