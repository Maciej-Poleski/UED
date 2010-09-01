/*
 * BasicMarkDatabase.cxx
 *
 *  Created on: 17-08-2010
 *      Author: evil
 */

#include <QtCore/QtPlugin>

#include <BasicMarkDatabase.hxx>
#include <Core.hxx>

#include <QtCore/QFile>

#include <AbstractBasicMark.hxx>
#include <BasicStringMark.hxx>
#include <MarksTabWidget.hxx>
#include <BasicModernMark.hxx>
#include <BasicClassicMark.hxx>
#include <BasicAbsoluteMark.hxx>

namespace MarkDatabase
{

BasicMarkDatabase::BasicMarkDatabase()
{
	// TODO Auto-generated constructor stub

}

BasicMarkDatabase::~BasicMarkDatabase()
{
	uninstall();
}

void BasicMarkDatabase::uninstall()
{
	Core::core->setMarksDatabase(0);
	Core::core->getUpdateManager()->unregisterPlugin(this);
	Core::core->getMainWindow()->delTab1(widget);
	delete widget;
}

void BasicMarkDatabase::install()
{
	delete Core::core->getMarksDatabase();
	Core::core->setMarksDatabase(this);
	Core::core->getUpdateManager()->registerPlugin(this);
	widget = new MarksTabWidget(this, Core::core->getMainWindow());
	Core::core->getMainWindow()->addTab1(widget, tr("Marks Database Management"));
	restore();
}

void BasicMarkDatabase::saveBinarySerialization( QDataStream & dataStream ) const
{
	dataStream << quint64(marksList.count());
	foreach(MarkInterface* markI,marksList)
		{
			MarkDatabase::AbstractBasicMark *mark = dynamic_cast< AbstractBasicMark* > (markI); // Always working
			mark->saveBinarySerialization(dataStream);
		}
}

void BasicMarkDatabase::store() const
{
	QFile file(qApp->applicationDirPath() + "/BasicMarkDatabase.store");
	file.open(QFile::WriteOnly);
	QDataStream dataStream( &file);
	saveBinarySerialization(dataStream);
}

static void bindMarksToEvents()
{
	if( Core::core->getEventsDatabase() == 0 )
		return;
	MarkDatabase::BasicMarkDatabase* marksDatabase =
			dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase());

	for( qint64 i = 0 ; i < marksDatabase->marksCound() ; ++i )
	{
		if( marksDatabase->getMarkByID(i)->getEvent() )
			marksDatabase->getMarkByID(i)->getEvent()->setMark(marksDatabase->getMarkByID(i));
	}
}

void BasicMarkDatabase::restore()
{
	QFile file(qApp->applicationDirPath() + "/BasicMarkDatabase.store");
	if( file.open(QFile::ReadOnly) )
	{
		QDataStream dataStream( &file);
		loadBinarySerialization(dataStream);
	}
	bindMarksToEvents();
}

void BasicMarkDatabase::loadBinarySerialization( QDataStream & dataStream )
{
	quint64 count;
	dataStream >> count;
	while( count-- )
	{
		MarkDatabase::AbstractBasicMark *mark;
		quint64 symbol;
		dataStream >> symbol;
		switch( symbol )
		{
		case quint64(1):
			mark = new MarkDatabase::BasicStringMark(this, dataStream);
			break;
		case quint64(2):
			mark = new MarkDatabase::BasicModernMark(this, dataStream);
			break;
		case quint64(3):
			mark = new MarkDatabase::BasicClassicMark(this, dataStream);
			break;
		case quint64(4):
			mark = new MarkDatabase::BasicAbsoluteMark(this, dataStream);
			break;
		default:
			throw Exception(tr("Unsupported mark type in input file"));
			break;
		}
		marksList << mark;
	}
}

bool BasicMarkDatabase::askUser( QWidget* parent, EventInterface* event )
{
	AbstractBasicMark* mark = AbstractBasicMark::askUser(parent, event);
	if( mark )
	{
		addMark(mark);
		event->setMark(mark);
		mark->bindToEvent(event);
		return true;
	}
	return false;
}

bool BasicMarkDatabase::askUser( QWidget* parent, TypeInterface* type )
{
	AbstractBasicMark* mark = AbstractBasicMark::askUser(parent, type);
	if( mark )
	{
		addMark(mark);
		return true;
	}
	return false;
}

}

Q_EXPORT_PLUGIN2(ued_basic_mark_database,MarkDatabase::BasicMarkDatabase)
