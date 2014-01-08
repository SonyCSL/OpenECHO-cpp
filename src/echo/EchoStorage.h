/*
 * EchoStorage.h
 *
 *  Created on: 2013/10/22
 *      Author: Fumiaki
 */

#ifndef ECHOSTORAGE_H_
#define ECHOSTORAGE_H_

#include <map>

class EchoStorage {
protected:
	unsigned short mTID;
public:
	EchoStorage();
	virtual ~EchoStorage();

	// TID
	unsigned short getInitialTID();
	void setNextTID(unsigned short tid);

};

#endif /* ECHOSTORAGE_H_ */
