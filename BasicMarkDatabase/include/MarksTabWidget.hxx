/*
 * MarksTabWidget.hxx
 *
 *  Created on: 19-08-2010
 *      Author: evil
 */

#ifndef MARKSTABWIDGET_HXX_
#define MARKSTABWIDGET_HXX_

#include <QtGui/QTabWidget>
#include <Repopulateable.hxx>

#include <BasicMarkDatabase.hxx>

namespace MarkDatabase
{

class MarksTabWidget : public QTabWidget, public Repopulateable
{
Q_OBJECT
Q_DISABLE_COPY(MarksTabWidget)

public:
	MarksTabWidget( BasicMarkDatabase* database, QWidget* parent = 0 );
	~MarksTabWidget()
	{
		// TODO Auto-generated destructor stub
	}

public slots:
	void update( int index );
	void populate();
	virtual void repopulate();

private:
	BasicMarkDatabase* database;
	int currentTab;
};

}

#endif /* MARKSTABWIDGET_HXX_ */
