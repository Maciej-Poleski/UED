/*
 * SubjectTab.cxx
 *
 *  Created on: 19-08-2010
 *      Author: evil
 */

#include <SubjectTab.hxx>

#include <QtCore/QString>
#include <QtGui/QLabel>
#include <QtGui/QDialog>
#include <QtGui/QDateEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>

#include <AddMarkButton.hxx>
#include <Core.hxx>
#include <BasicStringMark.hxx>
#include <BasicMarkDatabase.hxx>

namespace MarkDatabase
{

void SubjectTab::populate()
{
	bool eventsDatabaseIsAvailable = Core::core->getEventsDatabase() ? true : false;
	layout = new QGridLayout(this);
	foreach(TypeInterface* type,subject->getTypesList())
		{
			int row = layout->rowCount();
			QLabel* label = new QLabel(type->getName(), this);
			layout ->addWidget(label, row, 0, Qt::AlignLeft);
			QHBoxLayout *marksLayout = new QHBoxLayout();
			foreach(MarkInterface* mark,type->getMarksList())
				{
					QLabel *label = new QLabel(mark->toString(), this);
					label->setToolTip(dynamic_cast< AbstractBasicMark* > (mark)->getComment());
					marksLayout->addWidget(label);
				}
			marksLayout->addStretch(1);
			layout->addLayout(marksLayout, row, 1, Qt::AlignLeft);
			if( !eventsDatabaseIsAvailable )
			{
				AddMarkButton* button = new AddMarkButton(type, tr("Add mark"), this);
				layout->addWidget(button, row, 2, Qt::AlignRight);
				connect(button, SIGNAL(clicked(TypeInterface*)), this, SLOT(addMark(TypeInterface*)));
			}
		}
	layout->setColumnStretch(1, 1);
	layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), layout->rowCount(),
					0, 1, 3, Qt::AlignCenter);
	setLayout(layout);
}

SubjectTab::SubjectTab( BasicMarkDatabase *database, SubjectInterface* subject, QWidget* parent, bool clean ) :
	QWidget(parent), database(database), subject(subject), layout(0)
{
	if( !clean ) populate();
	connect(database, SIGNAL(markAdded(AbstractBasicMark*)), this, SLOT(update()));
}

void SubjectTab::update()
{
	delete layout;
	layout = 0;
	foreach(QObject* object,children())
			delete object;
	populate();
}

void SubjectTab::addMark( TypeInterface* type )
{
#ifdef USE_OBSOLETE_ADD_MARK
	///< TODO: Solidna implementacja tej funkcji
	QDialog *dialog = new QDialog(this);
	QLabel *dateLabel = new QLabel(tr("Date"), dialog);
	QLabel *markLabel = new QLabel(tr("Mark"), dialog);
	QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(), dialog);
	dateEdit->setCalendarPopup(true);
	QLineEdit* lineEdit = new QLineEdit(dialog);
	QPushButton *button = new QPushButton(tr("OK"), dialog);
	connect(button, SIGNAL(clicked()), dialog, SLOT(accept()));
	QHBoxLayout *line1Layout = new QHBoxLayout();
	line1Layout->addWidget(dateLabel);
	line1Layout->addWidget(dateEdit);
	QHBoxLayout *line2Layout = new QHBoxLayout();
	line2Layout->addWidget(markLabel);
	line2Layout->addWidget(lineEdit);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addLayout(line1Layout);
	layout->addLayout(line2Layout);
	layout->addWidget(button);
	dialog->setLayout(layout);
	dialog->setFixedSize(dialog->minimumSizeHint());
	if( dialog->exec() == QDialog::Accepted )
	{
		BasicStringMark *mark = new BasicStringMark(database, type, dateEdit->date(), lineEdit->text());
		Core::core->getMarksDatabase()->addMark(mark);
	}
#else
	AbstractBasicMark* mark = AbstractBasicMark::askUser(this, type);
	if( mark ) Core::core->getMarksDatabase()->addMark(mark);
#endif
}

}
