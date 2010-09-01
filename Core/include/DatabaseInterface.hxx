/*
 * DatabaseInterface.hxx
 *
 *  Created on: 06-08-2010
 *      Author: evil
 */

#ifndef DATABASEINTERFACE_HXX_
#define DATABASEINTERFACE_HXX_

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtCore/QList>

#include <SubjectInterface.hxx>

class DatabaseInterface
{
public:
	virtual ~DatabaseInterface()
	{
	}

	virtual void addSubject( SubjectInterface *subject )=0;

	virtual SubjectInterface* getSubject( QString name ) const
	{
		foreach (SubjectInterface* subject,getSubjectsList())
				if( subject->getName() == name ) return subject;
		return 0;
	}

	virtual QList< SubjectInterface* > getSubjectsList() const=0;

	virtual qint64 getExpectedSubjectID(SubjectInterface* subject) const=0; ///< Tworzy niebezpieczne wiązania
	virtual SubjectInterface* getSubjectByID(qint64 ID) const=0; ///< Wykorzystuje niebezpieczne wiązania

};

#endif /* DATABASEINTERFACE_HXX_ */
