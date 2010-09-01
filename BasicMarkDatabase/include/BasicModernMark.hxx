/*
 * BasicModernMark.hxx
 *
 *  Created on: 21-08-2010
 *      Author: evil
 */

#ifndef BASICMODERNMARK_HXX_
#define BASICMODERNMARK_HXX_

#include <AbstractBasicMark.hxx>

#include <QtCore/QLocale>

namespace MarkDatabase
{

class BasicModernMark : public MarkDatabase::AbstractBasicMark
{
public:
	BasicModernMark( BasicMarkDatabase* parent, EventInterface* event, double mark, QString comment =
			QString() ) :
		AbstractBasicMark(parent, event), mark(mark), comment(comment)
	{
	}
	BasicModernMark( BasicMarkDatabase* parent, TypeInterface* type, QDate date, double mark,
					 QString comment = QString() ) :
		AbstractBasicMark(parent, type, date), mark(mark), comment(comment)
	{
	}
	BasicModernMark( BasicMarkDatabase* parent, QDataStream & dataStream ) :
		AbstractBasicMark(parent, dataStream)
	{
		loadBinarySerialization(dataStream);
	}

	virtual ~BasicModernMark()
	{
		// TODO Auto-generated destructor stub
	}

	virtual QString toString() const
	{
		return QLocale::system().toString(mark, 'f', 2);
	}

	virtual QString getComment() const
	{
		return comment;
	}

	virtual void saveBinarySerialization( QDataStream& dataStream ) const
	{
		dataStream << quint64(2); ///< Symbol BasicModernMark
		AbstractBasicMark::saveBinarySerialization(dataStream);
		dataStream << mark << comment;
	}
	virtual void loadBinarySerialization( QDataStream& dataStream )
	{
		dataStream >> mark >> comment;
	}

private:
	double mark;
	QString comment;
};

}

#endif /* BASICMODERNMARK_HXX_ */
