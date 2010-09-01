/*
 * BasicEvent.cxx
 *
 *  Created on: 22-08-2010
 *      Author: evil
 */

#include "../include/BasicEvent.hxx"

namespace EventDatabase
{

void BasicEvent::saveBinarySerialization( QDataStream& dataStream ) const
{
	bool marksDatabaseIsAvailable = ( Core::core->getMarksDatabase() ) ? true : false;
	dataStream << ( marksDatabaseIsAvailable ? ( Core::core->getMarksDatabase()->getExpectedID(mark) )
			: qint64( -1) );
	dataStream << Core::core->getDatabase()->getExpectedSubjectID(type->getSubject());
	dataStream << type->getSubject()->getExpectedTypeID(type);
	dataStream << date << comment;
	switch( state )
	{
	case QUEUED:
		dataStream << quint64(1);
		break;
	case EXECUTED:
		dataStream << quint64(2);
		break;
	case REVOKED:
		dataStream << quint64(3);
		break;
	default:
		throw Exception(tr("Unknown event state"));
		break;
	}
}

void BasicEvent::loadBinarySerialization( QDataStream& dataStream )
{
	bool marksDatabaseIsAvailable = ( Core::core->getMarksDatabase() ) ? true : false;
	dataStream >> expectedMarkID;
	qint64 expectedSubjectID;
	dataStream >> expectedSubjectID;
	qint64 expectedTypeID;
	dataStream >> expectedTypeID;
	dataStream >> date >> comment;
	quint64 inputState;
	dataStream >> inputState;
	switch( inputState )
	{
	case quint64(1):
		state = QUEUED;
		break;
	case quint64(2):
		state = EXECUTED;
		break;
	case quint64(3):
		state = REVOKED;
		break;
	default:
		throw Exception(tr("Unknown event in input file"));
		break;
	}
	if( expectedMarkID >= 0 && marksDatabaseIsAvailable )
		mark = Core::core->getMarksDatabase()->getMarkByID(expectedMarkID);
	else
		mark = 0;
	if( expectedSubjectID >= 0 && expectedTypeID >= 0 )
		type = Core::core->getDatabase()->getSubjectByID(expectedSubjectID)->getTypeByID(expectedTypeID);
	else
		type = 0;
}
}
