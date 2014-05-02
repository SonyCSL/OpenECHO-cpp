/*
 * EchoUDPProtocol.h
 *
 *  Created on: 2014/03/17
 *      Author: Fumiaki
 */

#ifndef ECHOUDPPROTOCOL_H_
#define ECHOUDPPROTOCOL_H_

#include "EchoProtocol.h"

#include <string>
#include <memory>
#include <queue>
//#include <boost/shared_ptr.hpp>

#include <cstring> // for memset.

#include <pthread.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class EchoUDPProtocol: public EchoProtocol {
public:
	static const int UDP_MAX_PACKET_SIZE;
	static const int PORT;
protected:

	int mReceiverSock;
	struct sockaddr_in mReceiverSockAddr;
	struct ip_mreq mReceiverIpMreq;
	//bool mRunningReceiverThread;

public:
	EchoUDPProtocol();
	virtual ~EchoUDPProtocol();

	void openUDP();
	void closeUDP();

	void sendUDP(const EchoFrame& frame);
	void sendToSelf(const EchoFrame& frame);

	virtual void receive();

};

class UDPProtocolTask : EchoTask {
protected:
	EchoUDPProtocol& mProtocol;
public:
	UDPProtocolTask(EchoFrame frame, EchoUDPProtocol& protocol);
	virtual ~UDPProtocolTask();

protected:
	virtual void respond(const EchoFrame& response);
	virtual void informAll(const EchoFrame& response);
};

#endif /* ECHOUDPPROTOCOL_H_ */
