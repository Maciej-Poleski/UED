/*
 * AbstractBasicMark.cxx
 *
 *  Created on: 18-08-2010
 *      Author: evil
 */

#include <AbstractBasicMark.hxx>

#include <BasicMarkDatabase.hxx>

MarkDatabase::AbstractBasicMark::AbstractBasicMark( BasicMarkDatabase* parent, EventInterface* event ) :
	QObject(parent), event(event), type(event->getType()), date(event->getDate()),
			expectedEventID(Core::core->getEventsDatabase()->getExpectedID(event)),
			expectedSubjectID(Core::core->getDatabase()->getExpectedSubjectID(type->getSubject())),
			expectedTypeID(type->getSubject()->getExpectedTypeID(type))
{
}
MarkDatabase::AbstractBasicMark::AbstractBasicMark( BasicMarkDatabase* parent, TypeInterface* type,
													QDate date ) :
	QObject(parent), event(0), type(type), date(date), expectedEventID( -1),
			expectedSubjectID(Core::core->getDatabase()->getExpectedSubjectID(type->getSubject())),
			expectedTypeID(type->getSubject()->getExpectedTypeID(type))
{
}
MarkDatabase::AbstractBasicMark::AbstractBasicMark( BasicMarkDatabase* parent, QDataStream& dataStream ) :
	QObject(parent)
{
	loadBinarySerialization(dataStream);
}

void MarkDatabase::AbstractBasicMark::saveBinarySerialization( QDataStream & dataStream ) const
{
	dataStream << expectedEventID << expectedSubjectID << expectedTypeID << date;
}

void MarkDatabase::AbstractBasicMark::loadBinarySerialization( QDataStream & dataStream )
{
	dataStream >> expectedEventID >> expectedSubjectID >> expectedTypeID >> date;
	if( Core::core->getEventsDatabase() && expectedEventID != -1 )
	{ // Have Events Database
		event = Core::core->getEventsDatabase()->getEventByID(expectedEventID);
	}
	else
	{ // Have not Events Database
		event = 0;
	}
	type = Core::core->getDatabase()->getSubjectByID(expectedSubjectID)->getTypeByID(expectedTypeID);
}
