#ifndef EVENTSWIDGET_H
#define EVENTSWIDGET_H

#include <QtGui/QWidget>
#include "ui_EventsWidget.h"
#include <Repopulateable.hxx>

namespace EventDatabase
{
class BasicEvent;
class BasicEventDatabase;
}

class EventsWidget : public QWidget, private Ui::EventsWidget, public Repopulateable
{
Q_OBJECT

public:
	EventsWidget( EventDatabase::BasicEventDatabase* database, QWidget *parent = 0 );
	~EventsWidget();

private:
	EventDatabase::BasicEventDatabase* database;

public slots:
	void repopulate();

private slots:
	void populate();
	void addEvent(); ///< Przygotowuje i dodaje nowy event do bazy
	void populateTypeComboBox();
	void makeExecuted( EventDatabase::BasicEvent* event );

private:
	void populateTableWidget();
	void populateAddEventBar();
};

#endif // EVENTSWIDGET_H
