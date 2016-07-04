/*
 * EchoFrame.h
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#ifndef ECHOFRAME_H_
#define ECHOFRAME_H_

#include "OpenECHO.h"


namespace sonycsl_openecho {


class EchoProperty;

class EchoFrame {
protected:
	static const unsigned char EHD1;
	static const unsigned char EHD2;

public:
	static const int MIN_FRAME_SIZE = 12;

	static const unsigned char ESV_SETI = 0x60;
	static const unsigned char ESV_SETC = 0x61;
	static const unsigned char ESV_GET  = 0x62;
	static const unsigned char ESV_INF_REQ = 0x63;
	static const unsigned char ESV_SET_RES = 0x71;
	static const unsigned char ESV_GET_RES = 0x72;
	static const unsigned char ESV_INF = 0x73;
	static const unsigned char ESV_INFC = 0x74;
	static const unsigned char ESV_INFC_RES = 0x7A;
	static const unsigned char ESV_SETI_SNA = 0x50;
	static const unsigned char ESV_SETC_SNA = 0x51;
	static const unsigned char ESV_GET_SNA = 0x52;
	static const unsigned char ESV_INF_SNA = 0x53;

	static const unsigned char ESV_SET_NO_RES = 0x70;

	static const unsigned char ESV_SET_GET = 0x6E;
	static const unsigned char ESV_SET_GET_RES = 0x7E;
	static const unsigned char ESV_SET_GET_SNA = 0x5E;

private:
	unsigned short mTID;
	unsigned char mESV;

	unsigned short mSrcEchoClassCode;
	unsigned char mSrcEchoInstanceCode;
	std::string mSrcEchoAddress;
	unsigned short mDstEchoClassCode;
	unsigned char mDstEchoInstanceCode;
	std::string mDstEchoAddress;

	std::vector<EchoProperty> mPropertyList;
public:
	EchoFrame();
	EchoFrame(const unsigned short srcEchoClassCode, const unsigned char srcEchoInstanceCode
			, const unsigned short dstEchoClassCode, const unsigned char dstEchoInstanceCode
			, const std::string dstEchoAddress, const unsigned char esv); // send
	EchoFrame(const std::string srcEchoAddress, const std::vector<unsigned char>& frame); // receive
	virtual ~EchoFrame();

	unsigned short getTID();
	void setTID(unsigned short tid);
	unsigned char getESV();
	unsigned short getSrcEchoClassCode();
	unsigned char getSrcEchoInstanceCode();
	std::string getSrcEchoAddress();
	unsigned short getDstEchoClassCode();
	void setDstEchoInstanceCode(const unsigned char echoInstanceCode);
	unsigned char getDstEchoInstanceCode();
	void setDstEchoAddress(const std::string dstEchoAddress);
	std::string getDstEchoAddress() const;
	std::vector<EchoProperty> getPropertyList();
	std::vector<unsigned char> getFrameByteArray() const;
	void addPropertyForResponse(const unsigned char epc);
	void addPropertyForResponse(const unsigned char epc, const std::vector<unsigned char>& edt);
	void addPropertyForResponse(const EchoProperty& property);
	void addProperty(const EchoProperty& property);
};

};

#endif /* ECHOFRAME_H_ */
