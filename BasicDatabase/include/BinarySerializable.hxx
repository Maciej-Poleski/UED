/*
 * BinarySerializable.hxx
 *
 *  Created on: 15-08-2010
 *      Author: evil
 */

#ifndef BINARYSERIALIZABLE_HXX_
#define BINARYSERIALIZABLE_HXX_

#include <QtCore/QDataStream>

class BinarySerializable
{
public:
	virtual ~BinarySerializable() {}

	virtual void saveBinarySerialization(QDataStream&) const=0;
	virtual void loadBinarySerialization(QDataStream&)=0;
};

#endif /* BINARYSERIALIZABLE_HXX_ */
