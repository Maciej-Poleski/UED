/*
 * EventInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef EVENTINTERFACE_HXX_
#define EVENTINTERFACE_HXX_

#include <QtCore/QDate>

//#include <MarkInterface.hxx>
#include <TypeInterface.hxx>
//#include <SubjectInterface.hxx>

class MarkInterface;
class SubjectInterface;

class EventInterface
{
public:
	enum State
	{
		QUEUED, EXECUTED, REVOKED,
	};
	virtual ~EventInterface()
	{
	}

	virtual MarkInterface* getMark() const=0;

	virtual TypeInterface* getType() const=0;

	virtual SubjectInterface* getSubject() const
	{
		return getType()->getSubject();
	}

	virtual QDate getDate() const=0;

	virtual void setMark( MarkInterface* mark )=0;

	virtual void setState( State state )=0;

	virtual State getState() const=0;
};

#endif /* EVENTINTERFACE_HXX_ */
