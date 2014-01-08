/*
 * EchoUtils.h
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#ifndef ECHOUTILS_H_
#define ECHOUTILS_H_

#include <memory>
#include <vector>
#include <set>
#include <map>

class EchoUtils {
private:
	EchoUtils();
	~EchoUtils();
	EchoUtils(const EchoUtils& rhs);
	EchoUtils& operator=(const EchoUtils& rhs);
public:
	static long convertToEchoObjectCode(unsigned short echoClassCode, unsigned char instanceCode);
	static std::shared_ptr<std::vector<unsigned char> > convertPropertiesToPropertyMap(std::shared_ptr<std::set<unsigned char> > properties);
	static std::shared_ptr<std::set<unsigned char> > convertPropertyMapToProperties(std::shared_ptr<std::vector<unsigned char> > propertyMap);

private:
	static std::map<unsigned short, unsigned char> sAllocatedSelfDeviceInstanceCode;
public:
	static unsigned char allocateSelfDeviceInstanceCode(unsigned short echoClassCode);
};

#endif /* ECHOUTILS_H_ */
