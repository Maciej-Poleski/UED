/*
 * BasicAbsoluteMark.hxx
 *
 *  Created on: 21-08-2010
 *      Author: evil
 */

#ifndef BASICABSOLUTEMARK_HXX_
#define BASICABSOLUTEMARK_HXX_

#include "AbstractBasicMark.hxx"

#include <BasicClassicMark.hxx>
#include <BasicModernMark.hxx>

namespace MarkDatabase
{

/** Przechowuje ocenę absolutną oraz oceną klasyczną lub nowoczesną. */
class BasicAbsoluteMark : public MarkDatabase::AbstractBasicMark
{
public:
	BasicAbsoluteMark( BasicMarkDatabase* parent, EventInterface* event, double top, double bottom,
					   QString comment = QString(), BasicClassicMark *classicMark = 0,
					   BasicModernMark* modernMark = 0 ) :
		AbstractBasicMark(parent, event), top(top), bottom(bottom), comment(comment), modernMark(modernMark),
				classicMark(classicMark)
	{
	}
	BasicAbsoluteMark( BasicMarkDatabase* parent, TypeInterface* type, QDate date, double top, double bottom,
					   QString comment = QString(), BasicClassicMark *classicMark = 0,
					   BasicModernMark* modernMark = 0 ) :
		AbstractBasicMark(parent, type, date), top(top), bottom(bottom), comment(comment),
				modernMark(modernMark), classicMark(classicMark)
	{
	}
	BasicAbsoluteMark( BasicMarkDatabase* parent, QDataStream & dataStream ) :
		AbstractBasicMark(parent, dataStream)
	{
		loadBinarySerialization(dataStream);
	}

	virtual ~BasicAbsoluteMark()
	{
		//delete modernMark;
		//delete classicMark;
	}

	virtual QString toString() const
	{
		if( classicMark ) return classicMark->toString();
		if( modernMark ) return modernMark->toString();
		return QString() + top + '/' + bottom;
	}

	virtual QString getComment() const
	{
		return comment;
	}

	virtual void saveBinarySerialization( QDataStream& dataStream ) const
	{
		dataStream << quint64(4); ///< Symbol BasicAbstractMark
		AbstractBasicMark::saveBinarySerialization(dataStream);
		dataStream << top << bottom << comment;
		if( modernMark )
		{
			dataStream << QBool(true);
			modernMark->saveBinarySerialization(dataStream);
		}
		else
			dataStream << QBool(false);
		if( classicMark )
		{
			dataStream << QBool(true);
			classicMark->saveBinarySerialization(dataStream);
		}
		else
			dataStream << QBool(false);
	}
	virtual void loadBinarySerialization( QDataStream& dataStream )
	{
		dataStream >> top >> bottom >> comment;
		bool m;
		dataStream >> m;
		if( m )
		{
			quint64 t;
			dataStream >> t;
			modernMark = new BasicModernMark(0, dataStream);
		}
		else
			modernMark = 0;
		dataStream >> m;
		if( m )
		{
			quint64 t;
			dataStream >> t;
			classicMark = new BasicClassicMark(0, dataStream);
		}
		else
			classicMark = 0;
	}

private:
	double top; ///< Licznik
	double bottom; ///< Mianownik
	QString comment;

	BasicModernMark *modernMark;
	BasicClassicMark *classicMark;
};

}

#endif /* BASICABSOLUTEMARK_HXX_ */
