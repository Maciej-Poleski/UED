/*
 * TypeInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef TYPEINTERFACE_HXX_
#define TYPEINTERFACE_HXX_

#include <QtCore/QList>

//#include <MarkInterface.hxx>
//#include <SubjectInterface.hxx>

class MarkInterface;
class SubjectInterface;

class TypeInterface
{
public:
	typedef enum
	{
		SELECTABE, UNSELECTABLE,
	} State;
	virtual ~TypeInterface()
	{
	}

	virtual QString getName() const=0;

	virtual QList< MarkInterface* > getMarksList() const=0;

	virtual SubjectInterface* getSubject() const=0;

	virtual void setState( State state )=0;

	virtual State getState() const=0;
};

#endif /* TYPEINTERFACE_HXX_ */
