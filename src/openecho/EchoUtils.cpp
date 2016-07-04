/*
 * EchoUtils.cpp
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#include "EchoUtils.h"

namespace sonycsl_openecho {

std::map<unsigned short, unsigned char> EchoUtils::sAllocatedSelfDeviceInstanceCode;

long EchoUtils::convertToEchoObjectCode(unsigned short echoClassCode,
		unsigned char instanceCode) {
	long ret = (long)echoClassCode;
	ret  = ret << 8;
	ret += (long)instanceCode;
	return ret;
}

std::shared_ptr<std::vector<unsigned char> > EchoUtils::convertPropertiesToPropertyMap(
		std::shared_ptr<std::set<unsigned char> > properties) {
	std::shared_ptr<std::vector<unsigned char> > ret(new std::vector<unsigned char>());
	int propertiesSize = properties.get()->size();
	if(propertiesSize < 16) {
		ret.get()->resize(propertiesSize+1);
		(*(ret.get()))[0] = propertiesSize;
		for(int i = 0; i < propertiesSize; i++) {
			std::set<unsigned char>::iterator itr = properties.get()->begin();
			for(int j = 0; j < i; j++) {++itr;}
			(*(ret.get()))[i] = *itr;
		}
	} else {
		ret.get()->resize(17);
		(*(ret.get()))[0] = propertiesSize;
		for(int i = 0; i < ret.get()->size(); i++) {
			(*(ret.get()))[i] = 0;
		}
		for(int i = 0; i < propertiesSize; i++) {
			std::set<unsigned char>::iterator itr = properties.get()->begin();
			for(int j = 0; j < i; j++) {++itr;}
			unsigned char p = *itr;
			int high = (int)((p >> 4) & 0x0F);
			if (high < 0x08) {
				continue;
			}
			int low = (int)(p & 0x0F);
			(*(ret.get()))[low+1] = (((*(ret.get()))[low+1] & 0xFF) | (1 << (high - 0x08)));
		}

	}
	return ret;
}

std::shared_ptr<std::set<unsigned char> > EchoUtils::convertPropertyMapToProperties(
		std::shared_ptr<std::vector<unsigned char> > propertyMap) {
	std::shared_ptr<std::set<unsigned char> > ret(new std::set<unsigned char>());
	if(propertyMap.get() == nullptr || propertyMap.get()->size() == 0) {return ret;}
	int propertiesSize = propertyMap.get()->at(0);
	if(propertiesSize < 16) {
		for(int i = 0; i < propertiesSize; i++) {
			ret.get()->insert(propertyMap.get()->at(i+1));
		}
	} else {
		for(int low = 0; low < 16; low++) {
			unsigned char tmp = propertyMap.get()->at(low + 1);
			for(int high = 0; high < 8; high++) {
				if((tmp & 0x01) == 0x01) {
					ret.get()->insert((unsigned char)(low | ((high + 0x08) << 4)));
				}
				tmp = tmp >> 1;
			}
		}
	}
	return ret;

}

unsigned char EchoUtils::allocateSelfDeviceInstanceCode(
		unsigned short echoClassCode) {

	if (sAllocatedSelfDeviceInstanceCode.find(echoClassCode) == sAllocatedSelfDeviceInstanceCode.end()) {
		sAllocatedSelfDeviceInstanceCode.insert(std::map<unsigned short, unsigned char >::value_type(echoClassCode, 1));
		return 1;
	} else {
		unsigned char code =  sAllocatedSelfDeviceInstanceCode[echoClassCode];
		code += 1;
		sAllocatedSelfDeviceInstanceCode[echoClassCode] += 1;
		return sAllocatedSelfDeviceInstanceCode[echoClassCode];
	}
}

};
