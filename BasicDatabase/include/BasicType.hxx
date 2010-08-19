/*
 * BasicType.hxx
 *
 *  Created on: 08-08-2010
 *      Author: evil
 */

#ifndef BASICTYPE_HXX_
#define BASICTYPE_HXX_

#include <QtCore/QString>
#include <QtCore/QList>

#include <TypeInterface.hxx>
#include <BasicSubject.hxx>
#include <MarkInterface.hxx>
#include <BinarySerializable.hxx>

#include <MarkDatabaseInterface.hxx>
#include <Core.hxx>

namespace Core
{

namespace Database
{

class BasicType : public QObject, public TypeInterface, public BinarySerializable
{
Q_OBJECT
Q_DISABLE_COPY(BasicType)
	;
public:
	BasicType( BasicSubject* subject, QString name ) :
		QObject(subject), parentSubject(subject), name(name), state(SELECTABE)
	{
	}

	BasicType( BasicSubject* subject, QDataStream & dataStream ) :
		QObject(subject), parentSubject(subject)
	{
		loadBinarySerialization(dataStream);
	}

	virtual ~BasicType()
	{
	}

	virtual QString getName() const
	{
		return name;
	}

	virtual QList< MarkInterface* > getMarksList() const
	{
		return core->getMarksDatabase()->getMarksList(const_cast< BasicType* > (this));
	}

	virtual SubjectInterface* getSubject() const
	{
		return parentSubject;
	}

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

private:
	SubjectInterface* const parentSubject;
	QString name;
	State state;
};

}

}

#endif /* BASICTYPE_HXX_ */
