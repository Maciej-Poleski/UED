/*
 * BasicClassicMark.hxx
 *
 *  Created on: 21-08-2010
 *      Author: evil
 */

#ifndef BASICCLASSICMARK_HXX_
#define BASICCLASSICMARK_HXX_

#include "AbstractBasicMark.hxx"

#include <QtCore/QtGlobal>
#include <QtCore/QChar>
#include <QtCore/QLocale>

#include <BasicModernMark.hxx>

namespace MarkDatabase
{

class BasicClassicMark : public MarkDatabase::AbstractBasicMark
{
public:
	BasicClassicMark( BasicMarkDatabase* parent, EventInterface* event, quint8 mark, QChar sign,
					  QString comment = QString(), BasicModernMark* modernMark = 0 ) :
		AbstractBasicMark(parent, event), mark(mark), sign(sign), comment(comment), modernMark(modernMark)
	{
	}
	BasicClassicMark( BasicMarkDatabase* parent, TypeInterface* type, QDate date, quint8 mark, QChar sign,
					  QString comment = QString(), BasicModernMark* modernMark = 0 ) :
		AbstractBasicMark(parent, type, date), mark(mark), sign(sign), comment(comment),
				modernMark(modernMark)
	{
	}
	BasicClassicMark( BasicMarkDatabase* parent, QDataStream & dataStream ) :
		AbstractBasicMark(parent, dataStream)
	{
		loadBinarySerialization(dataStream);
	}

	virtual ~BasicClassicMark()
	{
		//delete modernMark;
	}

	virtual QString toString() const
	{
		if( modernMark ) return modernMark->toString();
		return QLocale::system().toString(mark) + sign;
	}

	virtual QString getComment() const
	{
		return comment;
	}

	virtual void saveBinarySerialization( QDataStream& dataStream ) const
	{
		dataStream << quint64(3); ///< Symbol BasicClassicMark
		AbstractBasicMark::saveBinarySerialization(dataStream);
		dataStream << mark << sign << comment;
		if( modernMark )
		{
			dataStream << QBool(true);
			modernMark->saveBinarySerialization(dataStream);
		}
		else
			dataStream << QBool(false);
	}
	virtual void loadBinarySerialization( QDataStream& dataStream )
	{
		dataStream >> mark >> sign >> comment;
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
	}

private:
	quint8 mark;
	QChar sign;
	QString comment;

	BasicModernMark* modernMark;
};

}

#endif /* BASICCLASSICMARK_HXX_ */
