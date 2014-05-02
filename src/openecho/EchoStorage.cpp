/*
 * EchoStorage.cpp
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#include "EchoStorage.h"

namespace sonycsl_openecho {

EchoStorage::EchoStorage() {
	mTID = 0;

}

EchoStorage::~EchoStorage() {
	// TODO Auto-generated destructor stub
}

unsigned short EchoStorage::getInitialTID() {
	return mTID;
}

void EchoStorage::setNextTID(unsigned short tid) {
	mTID = tid;
}

};
