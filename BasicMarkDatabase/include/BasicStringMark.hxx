/*
 * BasicStringMark.hxx
 *
 *  Created on: 18-08-2010
 *      Author: evil
 */

#ifndef BASICSTRINGMARK_HXX_
#define BASICSTRINGMARK_HXX_

#include <AbstractBasicMark.hxx>
#include <BinarySerializable.hxx>

#include <QtCore/QDataStream>

#include <BasicMarkDatabase.hxx>

namespace MarkDatabase
{

class BasicStringMark : public AbstractBasicMark
{
	QString mark;
public:
	BasicStringMark( BasicMarkDatabase* parent, EventInterface* event, QString mark ) :
		AbstractBasicMark(parent, event), mark(mark)
	{
	}
	BasicStringMark( BasicMarkDatabase* parent, TypeInterface* type, QDate date, QString mark ) :
		AbstractBasicMark(parent, type, date), mark(mark)
	{
	}
	BasicStringMark( BasicMarkDatabase* parent, QDataStream & dataStream ) :
		AbstractBasicMark(parent, dataStream)
	{
		loadBinarySerialization(dataStream);
	}
	virtual ~BasicStringMark()
	{
	}

	virtual QString toString() const
	{
		return mark;
	}

	virtual void saveBinarySerialization( QDataStream& dataStream ) const
	{
		dataStream << quint64(1); ///< Symbol BasicStringMark
		AbstractBasicMark::saveBinarySerialization(dataStream);
		dataStream << mark;
	}
	virtual void loadBinarySerialization( QDataStream& dataStream )
	{
		AbstractBasicMark::loadBinarySerialization(dataStream);
		dataStream >> mark;
	}
};

}

#endif /* BASICSTRINGMARK_HXX_ */
