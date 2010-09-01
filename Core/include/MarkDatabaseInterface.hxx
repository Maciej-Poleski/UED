/*
 * MarkDatabaseInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef MARKDATABASEINTERFACE_HXX_
#define MARKDATABASEINTERFACE_HXX_

#include <QtCore/QList>

#include <TypeInterface.hxx>
#include <MarkInterface.hxx>
#include <EventInterface.hxx>
#include <SubjectInterface.hxx>

class MarkDatabaseInterface
{
public:
	virtual ~MarkDatabaseInterface()
	{
	}

	virtual void addMark( MarkInterface* mark )=0;

	virtual MarkInterface* getMark( EventInterface* event ) const=0;

	virtual QList< MarkInterface* > getMarksList( QString subject ) const=0;
	virtual QList< MarkInterface* > getMarksList( QString subject, QString type ) const=0;

	virtual QList< MarkInterface* > getMarksList( SubjectInterface* subject ) const=0;
	virtual QList< MarkInterface* > getMarksList( TypeInterface* type ) const=0;

	virtual qint64 getExpectedID( MarkInterface* mark ) const=0; ///< Tworzy niebezpieczne wiązania
	virtual MarkInterface* getMarkByID( qint64 ID ) const=0; ///< Wykorzystuje niebezpieczne wiązania

	/** Pyta użytkownika o ocene i zwraca stworzony obiekt.
	 * @return true jeżeli dodano nową ocene. */
	virtual bool askUser( QWidget* parent, EventInterface* event )=0;

	/** Pyta użytkownika o ocene i zwraca stworzony obiekt.
	 * @return true jeżeli dodano nową ocene. */
	virtual bool askUser( QWidget* parent, TypeInterface* type )=0;

};

#endif /* MARKDATABASEINTERFACE_HXX_ */
