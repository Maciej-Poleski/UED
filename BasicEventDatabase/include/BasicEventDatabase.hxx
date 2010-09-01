/*
 * BasicEventDatabase.hxx
 *
 *  Created on: 26-08-2010
 *      Author: evil
 */

#ifndef BASICEVENTDATABASE_HXX_
#define BASICEVENTDATABASE_HXX_

#include <QtCore/QObject>
#include <PluginInterface.hxx>
#include <EventDatabaseInterface.hxx>
#include <BinarySerializable.hxx>
#include <Storeable.hxx>

#include <BasicEvent.hxx>
#include <EventsWidget.hxx>

#include <QtCore/QList>

namespace EventDatabase
{
class BasicEventDatabase : public QObject,
						   public Core::PluginInterface,
						   public EventDatabaseInterface,
						   public BinarySerializable,
						   public Storeable

{
Q_OBJECT
Q_DISABLE_COPY(BasicEventDatabase)Q_INTERFACES(Core::PluginInterface)

public:
	BasicEventDatabase();
	virtual ~BasicEventDatabase();

	virtual void install();
	virtual void uninstall();
	virtual int getVersion() const
	{
		return VERSION;
	}
	virtual QString getName() const
	{
		return NAME;
	}
	virtual QStringList getFilesNames() const
	{
		return QStringList();
	}
	virtual QStringList getPureLibraryFilesNames() const
	{
		return QStringList(getName().toLower().replace('.', '_'));
	}

	virtual void addEvent( EventInterface* event );

	virtual qint64 getExpectedID( EventInterface* event ) const
	{
		return eventsList.indexOf(dynamic_cast< BasicEvent* > (event));
	}
	virtual EventInterface* getEventByID( qint64 ID ) const
	{
		return eventsList[ID];
	}

	qint64 eventsCount() const
	{
		return eventsList.count();
	}

	virtual void saveBinarySerialization( QDataStream& ) const;
	virtual void loadBinarySerialization( QDataStream& );

signals:
	void eventAdded( BasicEvent* );

private:
	QList< BasicEvent* > eventsList;
	EventsWidget* widget;

	void store() const;
	void restore();
};

}
using namespace EventDatabase;

#endif /* BASICEVENTDATABASE_HXX_ */
