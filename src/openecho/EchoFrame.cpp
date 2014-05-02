/*
 * EchoFrame.cpp
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#include "EchoFrame.h"
#include "OpenECHO.h"


namespace sonycsl_openecho {

const unsigned char EchoFrame::EHD1 = 0x10;
const unsigned char EchoFrame::EHD2 = 0x81;

EchoFrame::EchoFrame(const unsigned short srcEchoClassCode,
		const unsigned char srcEchoInstanceCode,
		const unsigned short dstEchoClassCode,
		const unsigned char dstEchoInstanceCode,
		const std::string dstEchoAddress, const unsigned char esv) {
	mSrcEchoClassCode = srcEchoClassCode;
	mSrcEchoInstanceCode = srcEchoInstanceCode;
	mSrcEchoAddress = EchoSocket::SELF_ADDRESS;
	mDstEchoClassCode = dstEchoClassCode;
	mDstEchoInstanceCode = dstEchoInstanceCode;
	mDstEchoAddress = dstEchoAddress;
	mESV = esv;

	mTID = 0;
}

EchoFrame::EchoFrame(const std::string srcEchoAddress,
		const std::vector<unsigned char>& frame) {
	mSrcEchoAddress = srcEchoAddress;
	mDstEchoAddress = EchoSocket::SELF_ADDRESS;
	if(frame.at(0) != EHD1) return;
	if(frame.at(1) != EHD2) return;
	mTID = (frame.at(2) << 8) & 0xFF00;
	mTID += frame.at(3) & 0xFF;
	mSrcEchoClassCode = (frame.at(4) << 8) & 0xFF00;
	mSrcEchoClassCode += frame.at(5) & 0xFF;
	mSrcEchoInstanceCode = frame.at(6);
	mDstEchoClassCode = (frame.at(7) << 8) & 0xFF00;
	mDstEchoClassCode += frame.at(8) & 0xFF;
	mDstEchoInstanceCode = frame.at(9);
	mESV = frame.at(10);
	int propertyListSize = frame.at(11);
	for(int i = 0, pos = 12; i < propertyListSize; i++) {
		unsigned char epc = frame.at(pos);
		unsigned char pdc = frame.at(pos+1);
		pos += 2;
		if(pdc == 0) {
			mPropertyList.push_back(EchoProperty(epc));
		} else {
			std::vector<unsigned char> edt;
			for(unsigned char j = 0; j < pdc; j++) {
				edt.push_back(frame.at(pos));
				pos += 1;
			}
			mPropertyList.push_back(EchoProperty(epc, edt));
		}
	}

}

EchoFrame::~EchoFrame() {
	// TODO Auto-generated destructor stub
}

unsigned short EchoFrame::getTID() {
	return mTID;
}

void EchoFrame::setTID(unsigned short tid) {
	mTID = tid;
}

unsigned char EchoFrame::getESV() {
	return mESV;
}

unsigned short EchoFrame::getSrcEchoClassCode() {
	return mSrcEchoClassCode;
}

unsigned char EchoFrame::getSrcEchoInstanceCode() {
	return mSrcEchoInstanceCode;
}

std::string EchoFrame::getSrcEchoAddress() {
	return mSrcEchoAddress;
}

unsigned short EchoFrame::getDstEchoClassCode() {
	return mDstEchoClassCode;
}


void EchoFrame::setDstEchoInstanceCode(const unsigned char echoInstanceCode) {
	mDstEchoInstanceCode = echoInstanceCode;
}

unsigned char EchoFrame::getDstEchoInstanceCode() {
	return mDstEchoInstanceCode;
}

std::string EchoFrame::getDstEchoAddress() const {
	return mDstEchoAddress;
}

void EchoFrame::setDstEchoAddress(const std::string dstEchoAddress) {
	mDstEchoAddress = dstEchoAddress;
}

std::vector<EchoProperty> EchoFrame::getPropertyList() {
	return mPropertyList;
}

std::vector<unsigned char> EchoFrame::getFrameByteArray() const {
	std::vector<unsigned char> frame;
	int propertyListSize = mPropertyList.size();
	if(propertyListSize > 255) {
		propertyListSize = 255;
	}
	int packetSize = 12;
	for(int i = 0; i < propertyListSize; i++) {
		packetSize += mPropertyList.at(i).size();
		if(packetSize > EchoUDPProtocol::UDP_MAX_PACKET_SIZE) {
			propertyListSize = i - 1;
			break;
		}
	}

	frame.push_back(EHD1);
	frame.push_back(EHD2);
	frame.push_back(((mTID >> 8) & 0xff));
	frame.push_back((mTID & 0xff));
	frame.push_back(((mSrcEchoClassCode >> 8) & 0xff));
	frame.push_back((mSrcEchoClassCode & 0xff));
	frame.push_back(mSrcEchoInstanceCode);
	frame.push_back(((mDstEchoClassCode >> 8) & 0xff));
	frame.push_back((mDstEchoClassCode & 0xff));
	frame.push_back(mDstEchoInstanceCode);
	frame.push_back(mESV);
	frame.push_back(propertyListSize);
	for(int pidx = 0; pidx < mPropertyList.size(); pidx++) {
		EchoProperty p = mPropertyList.at(pidx);
		frame.push_back(p.epc);
		frame.push_back(p.pdc);
		int size = p.pdc & 0xFF;
		for(int i = 0; i < size; i++) {
			frame.push_back(p.edt.at(i));
		}
	}
	if(mESV == ESV_SET_GET_SNA) {
		frame.push_back(0);
	}
	return frame;
}

void EchoFrame::addPropertyForResponse(const unsigned char epc) {
	EchoProperty property(epc);
	addPropertyForResponse(property);
}

void EchoFrame::addPropertyForResponse(const unsigned char epc,
		const std::vector<unsigned char>& edt) {
	EchoProperty property(epc, edt);
	addPropertyForResponse(property);
}

void EchoFrame::addPropertyForResponse(const EchoProperty& property) {
	mPropertyList.push_back(property);
	switch(mESV) {
	case ESV_SET_NO_RES: case ESV_SETI_SNA:
		if(property.pdc != 0) {
			mESV = ESV_SETI_SNA;
		}
		break;
	case ESV_SET_RES: case ESV_SETC_SNA:
		if(property.pdc != 0) {
			mESV = ESV_SETC_SNA;
		}
		break;
	case ESV_GET_RES: case ESV_GET_SNA:
		if(property.pdc == 0) {
			mESV = ESV_GET_SNA;
		}
		break;
	case ESV_INF: case ESV_INF_SNA:
		if(property.pdc == 0) {
			mESV = ESV_INF_SNA;
		}
		break;
	}
}

EchoFrame::EchoFrame() {
}

void EchoFrame::addProperty(const EchoProperty& property) {
	mPropertyList.push_back(property);
}

};
