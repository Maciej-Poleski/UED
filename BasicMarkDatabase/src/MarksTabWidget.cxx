/*
 * MarksTabWidget.cxx
 *
 *  Created on: 19-08-2010
 *      Author: evil
 */

#include <MarksTabWidget.hxx>
#include <Core.hxx>
#include <SubjectTab.hxx>
#include <SubjectInterface.hxx>

namespace MarkDatabase
{

MarksTabWidget::MarksTabWidget( BasicMarkDatabase* database, QWidget* parent ) :
	QTabWidget(parent), database(database), currentTab( -1)
{
	populate();
	connect(this, SIGNAL(currentChanged(int)), this, SLOT(update(int)));
}

void MarksTabWidget::populate()
{
	foreach(SubjectInterface* subject,Core::core->getDatabase()->getSubjectsList())
		{
			if( subject->getState() == SubjectInterface::DISABLED ) continue;
			SubjectTab* tab = new SubjectTab(database, subject, this, true);
			addTab(tab, subject->getName());
		}
	dynamic_cast< SubjectTab* > (currentWidget())->update();
	currentTab = currentIndex();
}

void MarksTabWidget::repopulate()
{
	SubjectInterface* subject = dynamic_cast< SubjectTab* > (currentWidget())->getSubject();
	fprintf(stderr, "C");
	while( count() > 0 )
	{
		QWidget *page = widget(0);
		removeTab(0);
		delete page;
	}
	fprintf(stderr, "A");
	populate();
	fprintf(stderr, "B");
	for( int i = 0 ; i < count() ; ++i )
	{
		if( dynamic_cast< SubjectTab* > (widget(i))->getSubject() == subject )
		{
			setCurrentIndex(i);
			break;
		}
	}
}

void MarksTabWidget::update( int index )
{
	dynamic_cast< SubjectTab* > (widget(index))->update();
}

}
