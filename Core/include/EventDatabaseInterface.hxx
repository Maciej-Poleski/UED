/*
 * DatabesaInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef EVENTDATABASEINTERFACE_HXX_
#define EVENTDATABASEINTERFACE_HXX_

#include <EventInterface.hxx>

class EventDatabaseInterface
{
public:
	virtual ~EventDatabaseInterface()
	{
	}

	virtual void addEvent( EventInterface* event )=0;
	virtual int getExpectedID( EventInterface* event ) const=0; ///< Powoduje znaczną niestabilność wiązanie events - marks
	virtual EventInterface* getEventByID( int ID ) const=0;
};

#endif /* DATABESAINTERFACE_HXX_ */
