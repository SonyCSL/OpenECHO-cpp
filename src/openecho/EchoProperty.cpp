/*
 * EchoProperty.cpp
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#include "EchoProperty.h"


namespace sonycsl_openecho {

EchoProperty::EchoProperty(const unsigned char _epc)
	: epc(_epc)
	, pdc(0) {
}
EchoProperty::EchoProperty(const unsigned char _epc,
		const std::vector<unsigned char> _edt)
	: epc(_epc)
	, pdc((unsigned char)(_edt.size()))
	, edt(_edt) {
}

EchoProperty::~EchoProperty() {
	// TODO Auto-generated destructor stub
}

int EchoProperty::size() const {
	return ((int)pdc + 2);
}

EchoProperty::EchoProperty(const EchoProperty& property)
	: epc(property.epc)
	, pdc(property.pdc)
	, edt(property.edt) {
}

EchoProperty& EchoProperty::operator =(const EchoProperty& property) {
	epc = property.epc;
	pdc = property.pdc;
	edt = property.edt;

	return (*this);
}

};
