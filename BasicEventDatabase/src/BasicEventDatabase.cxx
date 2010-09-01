/*
 * BasicEventDatabase.cxx
 *
 *  Created on: 26-08-2010
 *      Author: evil
 */

#include <BasicEventDatabase.hxx>

#include <EventsWidget.hxx>
#include <Core.hxx>

#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtCore/QtPlugin>

namespace EventDatabase
{

BasicEventDatabase::BasicEventDatabase()
{
}

BasicEventDatabase::~BasicEventDatabase()
{
	uninstall();
}

void BasicEventDatabase::uninstall()
{
	Core::core->setEventsDatabase(0);
	Core::core->getUpdateManager()->unregisterPlugin(this);
	Core::core->getMainWindow()->delTab1(widget);
	delete widget;
}

void BasicEventDatabase::install()
{
	delete Core::core->getEventsDatabase();
	Core::core->setEventsDatabase(this);
	Core::core->getUpdateManager()->registerPlugin(this);
	widget = new EventsWidget(this);
	Core::core->getMainWindow()->addTab1(widget, tr("Events"));
	restore();
}

void BasicEventDatabase::store() const
{
	QFile file(qApp->applicationDirPath() + "/BasicEventDatabase.store");
	file.open(QFile::WriteOnly);
	QDataStream dataStream( &file);
	saveBinarySerialization(dataStream);
}

void BasicEventDatabase::restore()
{
	QFile file(qApp->applicationDirPath() + "/BasicEventDatabase.store");
	if( file.open(QFile::ReadOnly) )
	{
		QDataStream dataStream( &file);
		loadBinarySerialization(dataStream);
	}
}

void BasicEventDatabase::addEvent( EventInterface* event )
{
	if( dynamic_cast< BasicEvent* > (event) == 0 )
		throw Exception(tr("This type of event is not supported in BasicEventDatabase"));

	eventsList << dynamic_cast< BasicEvent* > (event);
	emit eventAdded(dynamic_cast< BasicEvent* > (event));
}

void BasicEventDatabase::saveBinarySerialization( QDataStream & dataStream ) const
{
	dataStream << qint64(eventsList.count());
	foreach(BasicEvent* event, eventsList)
		{
			event->saveBinarySerialization(dataStream);
		}
}

void BasicEventDatabase::loadBinarySerialization( QDataStream & dataStream )
{
	qint64 count;
	dataStream >> count;
	while( count-- )
	{
		BasicEvent* event = new BasicEvent(dataStream, this);
		eventsList << event;
	}
}

}

Q_EXPORT_PLUGIN2(ued_basic_event_database, EventDatabase::BasicEventDatabase)
