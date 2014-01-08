/*
 * EchoProperty.h
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#ifndef ECHOPROPERTY_H_
#define ECHOPROPERTY_H_

#include "OpenECHO.h"

class EchoProperty {
public:
	unsigned char epc;
	unsigned char pdc;
	std::vector<unsigned char> edt;
public:
	EchoProperty(const unsigned char _epc);
	EchoProperty(const unsigned char _epc, const std::vector<unsigned char> _edt);
	virtual ~EchoProperty();
	EchoProperty(const EchoProperty& property);
	EchoProperty &operator =(const EchoProperty &property);
	int size();
};

#endif /* ECHOPROPERTY_H_ */
