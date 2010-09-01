/*
 * BasicDatabase.cxx
 *
 *  Created on: 07-08-2010
 *      Author: evil
 */

#include <QtCore/QtPlugin>
#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtGui/QInputDialog>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>

#include <BasicDatabase.hxx>
#include <BasicType.hxx>
#include <BasicSubject.hxx>
#include <Core.hxx>
#include <MainWindow.hxx>

namespace Core
{

void BasicDatabase::populateSubject( TypeInterface* type )
{
	SubjectInterface* subject = type->getSubject();
	QWidget *widget = centralWidget->currentWidget();
	foreach(QObject* child,widget->children())
			delete child;
	QVBoxLayout *layout = new QVBoxLayout();
	foreach(TypeInterface* type,subject->getTypesList())
		{
			QLabel *label = new QLabel(type->getName());
			layout->addWidget(label, 0, Qt::AlignTop);
		}
	AddTypeButton *button = new AddTypeButton(subject, tr("Add Type"));
	layout->addWidget(button, 1, Qt::AlignBottom);
	widget->setLayout(layout);
	connect(button, SIGNAL(clicked(SubjectInterface*)), this, SLOT(addType(SubjectInterface*)));
}

void BasicDatabase::populate()
{
	while( centralWidget->count() > 0 )
	{
		centralWidget->widget(0)->deleteLater();
		centralWidget->removeTab(0);
	}
	foreach(SubjectInterface* subjectI,subjectsList)
		{
			if( subjectI->getState() == SubjectInterface::DISABLED )
				continue;
			Database::BasicSubject *subject = dynamic_cast< Database::BasicSubject* > (subjectI); // Always working
			connect(subject, SIGNAL(typeAdded(TypeInterface*)), this, SLOT(populateSubject(TypeInterface*)));
			QWidget *widget = new QWidget();
			centralWidget->addTab(widget, subject->getName());
			QVBoxLayout *layout = new QVBoxLayout();
			foreach(TypeInterface* type,subject->getTypesList())
				{
					QLabel *label = new QLabel(type->getName());
					layout->addWidget(label, 0, Qt::AlignTop);
				}
			AddTypeButton *button = new AddTypeButton(subject, tr("Add Type"));
			layout->addWidget(button, 1, Qt::AlignBottom);
			widget->setLayout(layout);
			connect(button, SIGNAL(clicked(SubjectInterface*)), this, SLOT(addType(SubjectInterface*)));
		}
	AddSubjectWidget *widget = new AddSubjectWidget(this);
	centralWidget->addTab(widget, tr("Add Subject"));
	centralWidget->setCurrentWidget(widget);
	widget->setF();
}

void BasicDatabase::addType( SubjectInterface* subject )
{
	QString typeName = QInputDialog::getText(centralWidget, tr("Add type"), tr("Additional type name for ")
			+ subject->getName() + ":");
	if( typeName.isEmpty() )
		return;
	Database::BasicType* type = new Database::BasicType(dynamic_cast< Database::BasicSubject* > (subject),
		typeName); // Always working
	subject->addType(type);
}

void BasicDatabase::install()
{
	delete core->getDatabase();
	core->setDatabase(this);
	core->getUpdateManager()->registerPlugin(this);
	centralWidget = new QTabWidget();
	centralWidget->setTabsClosable(true);
	connect(centralWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(dispatchTabClose(int)));
	//centralWidget->setMovable(true); TODO: Implementation of this feature
	core->getMainWindow()->addTab1(centralWidget, tr("Database Management"));
	restore();
	populate();
	connect(this, SIGNAL(subjectAdded()), this, SLOT(populate()));
	MainWindow* mainWindow = core->getMainWindow();
	foreach(QMenu* menu,menusList)
			mainWindow->menuBar()->addMenu(menu);

}

void BasicDatabase::dispatchTabClose( int index )
{
	if( dynamic_cast< AddSubjectWidget* > (centralWidget->widget(index)) )
		return;
	if( QMessageBox::question(centralWidget, tr("Are you sure?"), tr("This operation will remove ")
			+ centralWidget->tabText(index) + tr(" from diary.\nContinue?"), QMessageBox::Ok
			| QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok )
	{
		int i = 0;
		while( subjectsList[i]->getState() == SubjectInterface::DISABLED )
			++i;
		for( ; index > 0 ; --index )
		{
			++i;
			while( subjectsList[i]->getState() == SubjectInterface::DISABLED )
				++i;
		}
		subjectsList[i]->setState(SubjectInterface::DISABLED);
		emit subjectAdded();
	}
}

void BasicDatabase::uninstall()
{
	core->setDatabase(0);
	core->getUpdateManager()->unregisterPlugin(this);
	// TODO: usuwanie menu
}

void BasicDatabase::store() const
{
	QFile file(qApp->applicationDirPath() + "/BasicDatabase.store");
	file.open(QFile::WriteOnly);
	QDataStream dataStream( &file);
	saveBinarySerialization(dataStream);
}

void BasicDatabase::restore()
{
	QFile file(qApp->applicationDirPath() + "/BasicDatabase.store");
	if( file.open(QFile::ReadOnly) )
	{
		QDataStream dataStream( &file);
		loadBinarySerialization(dataStream);
	}
}

void BasicDatabase::saveBinarySerialization( QDataStream& dataStream ) const
{
	dataStream << quint64(subjectsList.count());
	foreach(SubjectInterface* subjectI,subjectsList)
		{
			Database::BasicSubject *subject = dynamic_cast< Database::BasicSubject* > (subjectI); // Always working
			subject->saveBinarySerialization(dataStream);
		}
}
void BasicDatabase::loadBinarySerialization( QDataStream&dataStream )
{
	quint64 count;
	dataStream >> count;
	while( count-- )
	{
		Database::BasicSubject* subject = new Database::BasicSubject(dataStream, this);
		subjectsList << subject;
	}
}

}

Core::AddSubjectWidget::AddSubjectWidget( BasicDatabase *database ) :
	QWidget(0), database(database)
{
	label = new QLabel(tr("Name:"));
	button = new QPushButton(tr("Add"));
	connect(button, SIGNAL(clicked()), this, SLOT(addSubject()));
	lineEdit = new QLineEdit();
	QHBoxLayout *hBoxLayout = new QHBoxLayout();
	hBoxLayout->addWidget(label);
	hBoxLayout->addWidget(lineEdit);
	QVBoxLayout *vBoxLayout = new QVBoxLayout();
	vBoxLayout->addLayout(hBoxLayout);
	vBoxLayout->addWidget(button);
	setLayout(vBoxLayout);
	connect(lineEdit, SIGNAL(returnPressed()), button, SLOT(click()));
}

void Core::AddSubjectWidget::addSubject()
{
	Database::BasicSubject* subject = new Database::BasicSubject(lineEdit->text(), database);
	database->addSubject(subject);
}

Q_EXPORT_PLUGIN2(ued_basic_database,Core::BasicDatabase)
