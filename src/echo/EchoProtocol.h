/*
 * EchoProtocol.h
 *
 *  Created on: 2014/03/17
 *      Author: Fumiaki
 */

#ifndef ECHOPROTOCOL_H_
#define ECHOPROTOCOL_H_

class EchoFrame;

class EchoProtocol {
public:
	EchoProtocol();
	virtual ~EchoProtocol();

	virtual void receive() = 0;

	class Task {
	protected:
		EchoFrame* mFrame;
	public:
		Task(EchoFrame* frame);
		virtual ~Task();

		void perform();
	protected:
		void respond(const EchoFrame& response) = 0;
		void informAll(const EchoFrame& response) = 0;

		bool isRequestFrame();
		bool isReportFrame();

		std::vector<EchoFrame> onReceiveRequest();
		EchoFrame onReceiveRequest(std::shared_ptr<EchoObject> deoj);
		void onReceiveReport();
		void checkObjectInFrame();

	};
};

#endif /* ECHOPROTOCOL_H_ */
