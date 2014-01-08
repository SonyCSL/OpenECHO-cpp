/*
 * EchoSocket.h
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#ifndef ECHOSOCKET_H_
#define ECHOSOCKET_H_


#include <string>
#include <memory>
#include <queue>
//#include <boost/shared_ptr.hpp>


#include <pthread.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class EchoFrame;
class EchoNode;
class EchoObject;


class EchoSocket {
public:
	static const std::string SELF_ADDRESS;
	static const std::string MULTICAST_ADDRESS;
	static const int PORT = 3610;
	static const int UDP_MAX_PACKET_SIZE = 65507;
	static std::queue<EchoFrame> sSelfFrameQueue;
private:
	static int sReceiverSock;
	static struct sockaddr_in sReceiverSockAddr;
	static struct ip_mreq sReceiverIpMreq;
	static bool sRunningReceiverThread;
	static unsigned short sNextTID;

private:
	EchoSocket();
	~EchoSocket();
	EchoSocket(const EchoSocket& rhs);
	EchoSocket& operator=(const EchoSocket& rhs);


	static void sendFrameToSelfNode(EchoFrame& frame);
	static void receiveFrameFromSelfNode();
	static void onReceiveUDPFrame(EchoFrame& frame);
	static void onReceiveUDPRequsetFrame(const std::shared_ptr<EchoObject> deoj, EchoFrame& frame);
	static void onReceiveNotRequest(EchoFrame& frame);
	static void checkNewObjectInResponse(EchoFrame& frame, const std::shared_ptr<EchoNode> node, const std::shared_ptr<EchoObject> seoj
			, const bool flagNewNode, const bool flagNewDevice);

public:
	static void openSocket();
	static void closeSocket();
	static void sendUDPFrame(EchoFrame& frame);
	static void sendTCPFrame(EchoFrame& frame);

	static void* receive(void*);
	static void receiveUDP();
	static void receiveTCP();
	static void startReceiverThread();
	static void stopReceiverThread();
	static void resumeReceiverThread();
	static void pauseReceiverThread();

	static unsigned short nextTID();
};

#endif /* ECHOSOCKET_H_ */
