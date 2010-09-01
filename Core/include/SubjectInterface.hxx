/*
 * SubjectInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef SUBJECTINTERFACE_HXX_
#define SUBJECTINTERFACE_HXX_

#include <QtCore/QList>

//#include <TypeInterface.hxx>
//#include <MarkInterface.hxx>

class TypeInterface;
class MarkInterface;

class SubjectInterface
{
public:
	enum State
	{
		INDIARY, DISABLED,
	};
	virtual ~SubjectInterface()
	{
	}

	virtual QString getName() const=0;
	virtual TypeInterface* getType( QString name ) const=0;

	virtual void addType( TypeInterface* type )=0;

	virtual QList< TypeInterface* > getTypesList() const=0;

	virtual QList< MarkInterface* > getMarksList() const=0;

	virtual void setState( State state )=0;

	virtual State getState() const=0;

	virtual qint64 getExpectedTypeID( TypeInterface* type ) const=0; ///< Tworzy niebezpieczne wiązania
	virtual TypeInterface* getTypeByID( qint64 ID ) const=0; ///< Wykorzystuje niebezpieczne wiązania
};

#endif /* SUBJECTINTERFACE_HXX_ */
