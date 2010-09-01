/*
 * BasicMark.hxx
 *
 *  Created on: 18-08-2010
 *      Author: evil
 */

#ifndef BASICMARK_HXX_
#define BASICMARK_HXX_

#include <QtCore/QObject>
#include <MarkInterface.hxx>
#include <BinarySerializable.hxx>

#include <QtCore/QDate>

#include <EventInterface.hxx>
#include <TypeInterface.hxx>
#include <Core.hxx>
#include <Exception.hxx>

namespace MarkDatabase
{

class BasicMarkDatabase;

class AbstractBasicMark : public QObject, public MarkInterface, public BinarySerializable
{
public:
	AbstractBasicMark( BasicMarkDatabase* parent, EventInterface* event );
	AbstractBasicMark( BasicMarkDatabase* parent, TypeInterface* type, QDate date );
	AbstractBasicMark( BasicMarkDatabase* parent, QDataStream& dataStream );

	virtual ~AbstractBasicMark()
	{
	}
	virtual EventInterface* getEvent() const
	{
		return event;
	}
	virtual QDate getDate() const
	{
		return date;
	}
	virtual TypeInterface* getType() const
	{
		return type;
	}

	virtual void bindToEvent( EventInterface* event )
	{
		//if( event ) throw Exception("Attemping to re-bind event to mark");
		this->event = event;
		this->expectedEventID = Core::core->getEventsDatabase()->getExpectedID(event);
	}

	virtual QString toString() const=0;
	virtual QString getComment() const=0;

	/** Pyta użytkownika o ocene i zwraca stworzony obiekt. */
	static AbstractBasicMark* askUser( QWidget* parent, EventInterface* event );

	/** Pyta użytkownika o ocene i zwraca stworzony obiekt. */
	static AbstractBasicMark* askUser( QWidget* parent, TypeInterface* type );

	virtual void saveBinarySerialization( QDataStream& ) const; ///< Zawsze należy implementować!
	virtual void loadBinarySerialization( QDataStream& ); ///< Zawsze należy implementować!

protected:
	EventInterface* event; ///< Element obowiązkowy
	TypeInterface* type; ///< Element obowiązkowy
	QDate date; ///< Element obowiązkowy
	int expectedEventID; ///< Bardzo niestabilne! NIE WOLNO MODERNIZOWAĆ MODUŁÓW!
	int expectedSubjectID; ///< Bardzo niestabilne! NIE WOLNO MODERNIZOWAĆ MODUŁÓW!
	int expectedTypeID; ///< Bardzo niestabilne! NIE WOLNO MODERNIZOWAĆ MODUŁÓW!
};

}

#endif /* BASICMARK_HXX_ */
