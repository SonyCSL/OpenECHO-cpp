/*
 * EchoProtocol.h
 *
 *  Created on: 2014/03/17
 *      Author: Fumiaki
 */

#ifndef ECHOPROTOCOL_H_
#define ECHOPROTOCOL_H_

#include <memory>
#include <vector>


class EchoFrame;
class EchoObject;

class EchoProtocol {
public:
	EchoProtocol();
	virtual ~EchoProtocol();

	virtual void receive() = 0;
};

class EchoTask {
protected:
	EchoFrame* mFrame;
public:
	EchoTask(EchoFrame frame);
	virtual ~EchoTask();

	void perform();
protected:
	virtual void respond(const EchoFrame& response);
	virtual void informAll(const EchoFrame& response);

	bool isRequestFrame();
	bool isReportFrame();

	std::vector<EchoFrame> onReceiveRequest();
	EchoFrame onReceiveRequest(std::shared_ptr<EchoObject> deoj);
	void onReceiveReport();
	void checkObjectInFrame();

};

#endif /* ECHOPROTOCOL_H_ */
