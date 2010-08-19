/*
 * BasicSubject.cxx
 *
 *  Created on: 08-08-2010
 *      Author: evil
 */

#include <QtCore/QtGlobal>

#include <BasicSubject.hxx>
#include <BasicType.hxx>
#include <TypeInterface.hxx>
#include <Exception.hxx>

namespace Core
{
namespace Database
{

TypeInterface* BasicSubject::getType( QString name ) const
{
	foreach(TypeInterface* type,typesList)
		{
			if( type->getName() == name ) return type;
		}
	return 0;
}

QList< MarkInterface* > BasicSubject::getMarksList() const
{
	QList< MarkInterface* > result;
	foreach(TypeInterface* type,typesList)
			result << type->getMarksList();
	return result;
}

void BasicSubject::saveBinarySerialization( QDataStream& dataStream ) const
{
	dataStream << name;
	switch( state )
	{
	case INDIARY:
		dataStream << quint64(1);
		break;
	case DISABLED:
		dataStream << quint64(2);
		break;
	default:
		dataStream << quint64(0);
		break;
	}
	dataStream << quint64(typesList.count());
	foreach(TypeInterface* typeI,typesList)
		{
			BasicType* type = dynamic_cast< BasicType* > (typeI); // Always working
			type->saveBinarySerialization(dataStream);
		}
}
void BasicSubject::loadBinarySerialization( QDataStream& dataStream )
{
	dataStream >> name;
	quint64 s;
	dataStream >> s;
	switch( s )
	{
	case 1:
		state = INDIARY;
		break;
	case 2:
		state = DISABLED;
		break;
	default:
		throw Exception(tr("Input file is corrupted!"));
		break;
	}
	quint64 count;
	dataStream >> count;
	while( count-- )
	{
		BasicType *type = new BasicType(this, dataStream);
		typesList << type;
	}
}

}
}
