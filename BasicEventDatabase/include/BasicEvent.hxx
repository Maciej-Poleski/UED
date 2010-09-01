/*
 * BasicEvent.hxx
 *
 *  Created on: 22-08-2010
 *      Author: evil
 */

#ifndef BASICEVENT_HXX_
#define BASICEVENT_HXX_

#include <QtCore/QObject>
#include <EventInterface.hxx>
#include <BinarySerializable.hxx>

#include <MarkInterface.hxx>
#include <TypeInterface.hxx>
#include <Exception.hxx>
#include <Core.hxx>

#include <QtCore/QDate>
#include <QtCore/QString>

namespace EventDatabase
{

class BasicEvent : public virtual QObject, public EventInterface, public BinarySerializable
{
public:
	BasicEvent( TypeInterface* type, QDate date, QString comment = QString(), QObject* parent = 0 ) :
		QObject(parent), mark(0), expectedMarkID( -1), type(type), date(date), comment(comment),
				state(QUEUED)
	{
	}
	BasicEvent( QDataStream & dataStream, QObject* parent = 0 ) :
		QObject(parent)
	{
		loadBinarySerialization(dataStream);
	}
	virtual ~BasicEvent()
	{
		// TODO Auto-generated destructor stub
	}

	virtual MarkInterface* getMark() const
	{
		return mark;
	}

	virtual TypeInterface* getType() const
	{
		return type;
	}

	virtual QDate getDate() const
	{
		return date;
	}

	QString getComment() const
	{
		return comment;
	}

	virtual void setMark( MarkInterface* mark )
	{
		//if( this->mark )
		//throw Exception(tr("Overriding mark in event is forbiden"));
		this->mark = mark;
	}

	virtual void setState( State state )
	{
		this->state = state;
	}

	virtual State getState() const
	{
		return state;
	}

	virtual void saveBinarySerialization( QDataStream& dataStream ) const;

	virtual void loadBinarySerialization( QDataStream& dataStream );

private:
	MarkInterface* mark;
	qint64 expectedMarkID;
	TypeInterface* type;
	QDate date;
	QString comment;
	State state;
};

}

#endif /* BASICEVENT_HXX_ */
