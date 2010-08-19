/*
 * BasicMarkDatabase.cxx
 *
 *  Created on: 17-08-2010
 *      Author: evil
 */

#include <QtCore/QtPlugin>

#include <BasicMarkDatabase.hxx>
#include <Core.hxx>

#include <AbstractBasicMark.hxx>
#include <BasicStringMark.hxx>
#include <MarksTabWidget.hxx>

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
		case 1:
			mark = new MarkDatabase::BasicStringMark(this, dataStream);
			break;
		default:
			throw Exception(tr("Unsupported mark typy in input file"));
			break;
		}
		marksList << mark;
	}
}

}

Q_EXPORT_PLUGIN2(ued_basic_mark_database,MarkDatabase::BasicMarkDatabase)
