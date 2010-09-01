#include "../include/EventsWidget.hxx"

#include <Core.hxx>
#include <SubjectInterface.hxx>
#include <TypeInterface.hxx>
#include <BasicEvent.hxx>
#include <BasicEventDatabase.hxx>
#include <ExecuteButton.hxx>
#include <MarkDatabaseInterface.hxx>

#include <QtCore/QDate>
#include <QtCore/QtGlobal>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

EventsWidget::EventsWidget( BasicEventDatabase* database, QWidget *parent ) :
	QWidget(parent), database(database)
{
	setupUi(this);
	connect(database, SIGNAL(eventAdded(BasicEvent*)), this, SLOT(repopulate()));
}

EventsWidget::~EventsWidget()
{

}

void EventsWidget::repopulate()
{
	populate();
}

void EventsWidget::populate()
{
	populateTableWidget();
	populateAddEventBar();
}

void EventsWidget::populateTableWidget()
{
	tableWidget->clear();
	qint64 eventsCount = database->eventsCount();
	qint64 rows = 0;
	QStringList header;
	header << tr("Date") << tr("Subject") << tr("Type") << tr("State") << tr("Comment");
	tableWidget->setColumnCount(5);
	tableWidget->setHorizontalHeaderLabels(header);
	tableWidget->horizontalHeader()->setStretchLastSection(true);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

	for( int i = 0 ; i < eventsCount ; ++i )
	{
		if( database->getEventByID(i)->getState() != EventInterface::REVOKED )
			++rows;
	}
	tableWidget->setRowCount(rows);
	qint64 currentRow = 0;
	for( int i = 0 ; i < eventsCount ; ++i )
	{
		EventDatabase::BasicEvent *event =
				dynamic_cast< EventDatabase::BasicEvent* > (database->getEventByID(i));
		if( event->getState() == EventInterface::REVOKED )
			continue;
		tableWidget ->setItem(currentRow, 0,
			new QTableWidgetItem(event->getDate().toString(tr("dd-MM-yyyy"))));
		tableWidget ->setItem(currentRow, 1, new QTableWidgetItem(event->getSubject()->getName()));
		tableWidget ->setItem(currentRow, 2, new QTableWidgetItem(event->getType()->getName()));
		ExecuteButton* button = new ExecuteButton(
			dynamic_cast< EventDatabase::BasicEvent* > (database->getEventByID(i)));
		connect(button, SIGNAL(clicked(EventDatabase::BasicEvent*)), this,
			SLOT(makeExecuted(EventDatabase::BasicEvent*)));
		if( event->getState() == EventInterface::EXECUTED )
		{
			QTableWidgetItem* item = new QTableWidgetItem(tr("EXECUTED"));
			item->setToolTip(event->getMark()->toString());
			tableWidget ->setItem(currentRow, 3, item);
		}
		else
			tableWidget ->setCellWidget(currentRow, 3, button);
		tableWidget ->setItem(currentRow, 4, new QTableWidgetItem(
			dynamic_cast< EventDatabase::BasicEvent* > (event)->getComment()));
		++currentRow;
	}
}

void EventsWidget::populateAddEventBar()
{
	subjectComboBox->clear();
	subjectComboBox->addItem(tr("Select Subject"));
	foreach(SubjectInterface *subject,Core::core->getDatabase()->getSubjectsList())
		{
			subjectComboBox ->addItem(subject->getName(), Core::core->getDatabase()->getExpectedSubjectID(
				subject));
		}
	connect(subjectComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(populateTypeComboBox()));
	typeComboBox->clear();
	dateEdit->setDate(QDate::currentDate());
	dateEdit->setCalendarPopup(true);
	commentLineEdit->clear();
#if QT_VERSION >= 0x040700
	commentLineEdit->setPlaceholderText(tr("Comment")); // Wymagane Qt 4.7
#endif
	connect(addButton, SIGNAL(clicked()), this, SLOT(addEvent()));
}

void EventsWidget::populateTypeComboBox()
{
	typeComboBox->clear();
	typeComboBox->addItem(tr("Select Type"));
	if( subjectComboBox->currentIndex() == 0 )
		return;
	SubjectInterface * subject = Core::core->getDatabase()->getSubjectByID(subjectComboBox->itemData(
		subjectComboBox->currentIndex()).toLongLong());
	foreach(TypeInterface* type,subject->getTypesList())
		{
			typeComboBox->addItem(type->getName(), subject->getExpectedTypeID(type));
		}
}

void EventsWidget::addEvent()
{
	if( subjectComboBox->currentIndex() == 0 || typeComboBox->currentIndex() == 0 )
		return;
	TypeInterface * type = Core::core->getDatabase()->getSubjectByID(subjectComboBox->itemData(
		subjectComboBox->currentIndex()).toLongLong())->getTypeByID(typeComboBox->itemData(
		typeComboBox->currentIndex()).toLongLong());
	BasicEvent *event = new EventDatabase::BasicEvent(type, dateEdit->date(), commentLineEdit->text(),
		database);
	database->addEvent(event);
}

void EventsWidget::makeExecuted( EventDatabase::BasicEvent* event )
{
	bool marksDatabaseIsAvailable = ( Core::core->getMarksDatabase() ) ? true : false;
	if( marksDatabaseIsAvailable )
	{
		MarkDatabaseInterface* marksDatabase = Core::core->getMarksDatabase();
		if( marksDatabase->askUser(this, event) )
		{
			event->setState(EventInterface::EXECUTED);
			populateTableWidget();
		}
	}
	else
	{
		event->setState(EventInterface::EXECUTED);
		populateTableWidget();
	}
}
