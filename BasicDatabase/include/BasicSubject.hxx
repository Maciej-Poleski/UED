/*
 * BasicSubject.hxx
 *
 *  Created on: 08-08-2010
 *      Author: evil
 */

#ifndef BASICSUBJECT_HXX_
#define BASICSUBJECT_HXX_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QDataStream>

#include <BasicDatabase.hxx>
#include <SubjectInterface.hxx>
#include <BinarySerializable.hxx>

namespace Core
{

namespace Database
{

class BasicSubject : public QObject, public SubjectInterface, public BinarySerializable
{
Q_OBJECT
Q_DISABLE_COPY(BasicSubject)
public:
	BasicSubject( QString name, BasicDatabase *database ) :
		QObject(database), name(name), state(INDIARY)
	{
	}

	BasicSubject( QDataStream & dataStream, BasicDatabase* database ) :
		QObject(database)
	{
		loadBinarySerialization(dataStream);
	}

	virtual ~BasicSubject()
	{
	}

	virtual QString getName() const
	{
		return name;
	}
	virtual TypeInterface* getType( QString name ) const;

	virtual void addType( TypeInterface* type )
	{
		typesList << type;
		emit typeAdded(type);
	}

	virtual QList< TypeInterface* > getTypesList() const
	{
		return typesList;
	}

	virtual QList< MarkInterface* > getMarksList() const;

	virtual void setState( State state )
	{
		this->state = state;
	}

	virtual State getState() const
	{
		return state;
	}

	virtual void saveBinarySerialization( QDataStream& ) const;
	virtual void loadBinarySerialization( QDataStream& );

	virtual qint64 getExpectedTypeID( TypeInterface* type ) const
	{
		return typesList.indexOf(type);
	}

	virtual TypeInterface* getTypeByID( qint64 ID ) const
	{
		return typesList[ID];
	}

signals:
	void typeAdded( TypeInterface* );

private:
	QString name;
	State state;
	QList< TypeInterface* > typesList;
};

}

}

#endif /* BASICSUBJECT_HXX_ */
