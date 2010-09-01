/*
 * AbstractBasicMark.cxx
 *
 *  Created on: 18-08-2010
 *      Author: evil
 */

#include <AbstractBasicMark.hxx>

#include <QtGui/QRadioButton>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QDateEdit>

#include <BasicMarkDatabase.hxx>
#include <NewMarkDialog.hxx>
#include <BasicModernMark.hxx>
#include <BasicClassicMark.hxx>
#include <BasicAbsoluteMark.hxx>

MarkDatabase::AbstractBasicMark::AbstractBasicMark( BasicMarkDatabase* parent, EventInterface* event ) :
	QObject(parent), event(event), type(event->getType()), date(event->getDate()),
			expectedEventID(Core::core->getEventsDatabase()->getExpectedID(event)),
			expectedSubjectID(Core::core->getDatabase()->getExpectedSubjectID(type->getSubject())),
			expectedTypeID(type->getSubject()->getExpectedTypeID(type))
{
}
MarkDatabase::AbstractBasicMark::AbstractBasicMark( BasicMarkDatabase* parent, TypeInterface* type,
													QDate date ) :
	QObject(parent), event(0), type(type), date(date), expectedEventID( -1),
			expectedSubjectID(Core::core->getDatabase()->getExpectedSubjectID(type->getSubject())),
			expectedTypeID(type->getSubject()->getExpectedTypeID(type))
{
}
MarkDatabase::AbstractBasicMark::AbstractBasicMark( BasicMarkDatabase* parent, QDataStream& dataStream ) :
	QObject(parent)
{
	loadBinarySerialization(dataStream);
}

void MarkDatabase::AbstractBasicMark::saveBinarySerialization( QDataStream & dataStream ) const
{
	dataStream << expectedEventID << expectedSubjectID << expectedTypeID << date;
}

void MarkDatabase::AbstractBasicMark::loadBinarySerialization( QDataStream & dataStream )
{
	dataStream >> expectedEventID >> expectedSubjectID >> expectedTypeID >> date;
	if( Core::core->getEventsDatabase() && expectedEventID != -1 )
	{ // Have Events Database
		event = Core::core->getEventsDatabase()->getEventByID(expectedEventID);
	}
	else
	{ // Have not Events Database
		event = 0;
	}
	type = Core::core->getDatabase()->getSubjectByID(expectedSubjectID)->getTypeByID(expectedTypeID);
}

MarkDatabase::AbstractBasicMark* MarkDatabase::AbstractBasicMark::askUser( QWidget* parent,
																		   TypeInterface* type )
{
	NewMarkDialog dialog(parent);
	if( dialog.exec() == QDialog::Accepted )
	{
		BasicModernMark* modernMark = 0;
		BasicClassicMark* classicMark = 0;
		BasicAbsoluteMark* absoluteMark = 0;
		if( dialog.modernRadioButton->isChecked() )
		{
			double markDouble = QLocale::system().toDouble(dialog.markLineEdit->text());
			modernMark
					= new BasicModernMark(
										  dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase()),
										  type, dialog.dateEdit->date(), markDouble,
										  dialog.commentPlainTextEdit->toPlainText());
		}
		else if( dialog.classicRadioButton->isChecked() )
		{
			quint8 markUint8 = QLocale::system().toUShort(dialog.markLineEdit->text().at(0));
			QChar markSign = dialog.markLineEdit->text().length() > 1 ? dialog.markLineEdit->text().at(1)
					: '\0';
			classicMark
					= new BasicClassicMark(
										   dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase()),
										   type, dialog.dateEdit->date(), markUint8, markSign,
										   dialog.commentPlainTextEdit->toPlainText(), 0);
		}
		if( dialog.absoluteCheckBox->isChecked() )
		{
			QStringList markString = dialog.absoluteLineEdit->text().split('/');
			double markTop = QLocale::system().toDouble(markString[0]);
			double markBottom = QLocale::system().toDouble(markString[1]);
			absoluteMark
					= new BasicAbsoluteMark(
											dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase()),
											type, dialog.dateEdit->date(), markTop, markBottom,
											dialog.commentPlainTextEdit->toPlainText(), classicMark,
											modernMark);
		}
		if( absoluteMark )
			return absoluteMark;
		else if( classicMark )
			return classicMark;
		else if( modernMark ) return modernMark;
	}
	else
		return 0;
	return 0;
}
MarkDatabase::AbstractBasicMark* MarkDatabase::AbstractBasicMark::askUser( QWidget* parent,
																		   EventInterface* event )
{
	NewMarkDialog dialog(parent);
	dialog.dateEdit->setDate(event->getDate());
	dialog.disableDateEdit();
	if( dialog.exec() == QDialog::Accepted )
	{
		BasicModernMark* modernMark = 0;
		BasicClassicMark* classicMark = 0;
		BasicAbsoluteMark* absoluteMark = 0;
		if( dialog.modernRadioButton->isChecked() )
		{
			double markDouble = QLocale::system().toDouble(dialog.markLineEdit->text());
			modernMark
					= new BasicModernMark(
										  dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase()),
										  event, markDouble, dialog.commentPlainTextEdit->toPlainText());
		}
		else if( dialog.classicRadioButton->isChecked() )
		{
			quint8 markUint8 = QLocale::system().toUShort(dialog.markLineEdit->text().at(0));
			QChar markSign = dialog.markLineEdit->text().length() > 1 ? dialog.markLineEdit->text().at(1)
					: '\0';
			classicMark
					= new BasicClassicMark(
										   dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase()),
										   event, markUint8, markSign,
										   dialog.commentPlainTextEdit->toPlainText(), 0);
		}
		if( dialog.absoluteCheckBox->isChecked() )
		{
			QStringList markString = dialog.absoluteLineEdit->text().split('/');
			double markTop = QLocale::system().toDouble(markString[0]);
			double markBottom = QLocale::system().toDouble(markString[1]);
			absoluteMark
					= new BasicAbsoluteMark(
											dynamic_cast< MarkDatabase::BasicMarkDatabase* > (Core::core->getMarksDatabase()),
											event, markTop, markBottom,
											dialog.commentPlainTextEdit->toPlainText(), classicMark,
											modernMark);
		}
		if( absoluteMark )
			return absoluteMark;
		else if( classicMark )
			return classicMark;
		else if( modernMark ) return modernMark;
	}
	else
		return 0;
	return 0;
}
