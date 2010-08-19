/*
 * BasicType.cxx
 *
 *  Created on: 08-08-2010
 *      Author: evil
 */

#include <BasicType.hxx>
#include <Exception.hxx>

void Core::Database::BasicType::saveBinarySerialization( QDataStream & dataStream ) const
{
	dataStream << name;
	switch( state )
	{
	case SELECTABE:
		dataStream << quint64(1);
		break;
	case UNSELECTABLE:
		dataStream << quint64(2);
		break;
	default:
		dataStream << quint64(0);
		break;
	}

}

void Core::Database::BasicType::loadBinarySerialization( QDataStream & dataStream )
{
	dataStream >> name;
	quint64 s;
	dataStream >> s;
	switch( s )
	{
	case 1:
		state = SELECTABE;
		break;
	case 2:
		state = UNSELECTABLE;
		break;
	case 0:
		throw Exception(tr("Input file is corrupted!"));
		break;
	}
}
