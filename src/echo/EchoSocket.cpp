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
bool EchoSocket::sRunningPerformerThread = false;
EchoUDPProtocol EchoSocket::sUDPProtocol;
unsigned short EchoSocket::sNextTID = 0;
std::queue<std::shared_ptr<EchoTask> > EchoSocket::sTaskQueue;


EchoSocket::EchoSocket() {
	// TODO Auto-generated constructor stub

}

EchoSocket::~EchoSocket() {
	// TODO Auto-generated destructor stub
}


void EchoSocket::openSocket() {
	//startReceiverThread();
	sUDPProtocol.openUDP();
}

void EchoSocket::closeSocket() {
	//stopReceiverThread();
	//close(sReceiverSock);
	//shutdown(sReceiverSock);
	sUDPProtocol.closeUDP();
}
void EchoSocket::enqueueTask(std::shared_ptr<EchoTask> task) {
	//receiveUDPFrame(frame);
	sTaskQueue.push(task);
}

std::shared_ptr<EchoTask> EchoSocket::dequeueTask() {
	if(!sTaskQueue.empty()) {
		std::shared_ptr<EchoTask> task = sTaskQueue.front();
		sTaskQueue.pop();
		return task;
	} else {
		return std::shared_ptr<EchoTask>();
	}
}

void EchoSocket::sendUDPFrame(EchoFrame& frame) {
	sUDPProtocol.sendUDP(frame);
}


void EchoSocket::startReceiverThread() {
	pthread_t thread;
	pthread_create(&thread, NULL, receiverThread, NULL);
	pthread_t thread1;
	pthread_create(&thread1, NULL, taskPerformerThread, NULL);
}

void EchoSocket::stopReceiverThread() {
	sRunningReceiverThread = false;
	sRunningPerformerThread = false;
}
void EchoSocket::resumeReceiverThread() {
}

void EchoSocket::pauseReceiverThread() {
}

unsigned short EchoSocket::nextTID() {
	unsigned short ret = sNextTID;
	sNextTID += 1;
	//Echo::getStorage().get()->setNextTID(sNextTID);
	return ret;
}

short EchoSocket::getNextTIDNoIncrement() {
	return sNextTID;
}

void* EchoSocket::receiverThread(void*) {

	sRunningReceiverThread = true;
	while(sRunningReceiverThread) {
		receive();
		usleep(10000);
	}
	return 0;
}

void* EchoSocket::taskPerformerThread(void*) {
	sRunningPerformerThread = true;
	while(sRunningPerformerThread) {
		performTasks();
		usleep(10000);
	}
	return 0;
}

void EchoSocket::receive() {
	sUDPProtocol.receive();
}

void EchoSocket::performTasks() {
	std::shared_ptr<EchoTask> task = dequeueTask();
	while(task.get() != nullptr) {
		task.get()->perform();
		task = dequeueTask();
	}
}
