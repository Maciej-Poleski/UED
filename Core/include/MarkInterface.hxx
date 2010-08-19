/*
 * MarkInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef MARKINTERFACE_HXX_
#define MARKINTERFACE_HXX_

#include <QtCore/QDate>

//#include <EventInterface.hxx>
#include <TypeInterface.hxx>
//#include <SubjectInterface.hxx>

class EventInterface;
class SubjectInterface;

class MarkInterface
{
public:
	virtual ~MarkInterface()
	{
	}

	virtual EventInterface* getEvent() const=0;

	virtual QDate getDate() const=0;

	virtual TypeInterface* getType() const=0;

	virtual SubjectInterface* getSubject() const
	{
		return getType()->getSubject();
	}

	/**
	 * Korzystaj mądrze.
	 * @param event
	 */
	virtual void bindToEvent( EventInterface* event )=0;

	virtual QString toString() const=0;
};

#endif /* MARKINTERFACE_HXX_ */
