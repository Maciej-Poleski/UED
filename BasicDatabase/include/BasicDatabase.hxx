/*
 * BasicDatabase.hxx
 *
 *  Created on: 07-08-2010
 *      Author: evil
 */

#ifndef BASICDATABASE_HXX_
#define BASICDATABASE_HXX_

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtGui/QWidget>
#include <QtGui/QMenu>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>

#include <DatabaseInterface.hxx>
#include <PluginInterface.hxx>
#include <SubjectInterface.hxx>
#include <BinarySerializable.hxx>
#include <Storeable.hxx>

namespace Core
{

class BasicDatabase : public virtual QObject,
					  public Core::PluginInterface,
					  public DatabaseInterface,
					  public BinarySerializable,
					  public Storeable
{
Q_OBJECT
Q_DISABLE_COPY(BasicDatabase)Q_INTERFACES(Core::PluginInterface)

public:
	BasicDatabase()
	{
		qDebug() << "Tworzenie BasicDatabase";
	}
	virtual ~BasicDatabase()
	{
		uninstall();
	}

	virtual void addSubject( SubjectInterface *subject )
	{
		subjectsList << subject;
		emit subjectAdded();
	}

	virtual QList< SubjectInterface* > getSubjectsList() const
	{
		return subjectsList;
	}

	virtual void install();
	virtual void uninstall();

	virtual int getVersion() const
	{
		return VERSION;
	}

	virtual QString getName() const
	{
		return NAME;
	}

	virtual QStringList getFilesNames() const
	{
		return QStringList();
	}

	virtual QStringList getPureLibraryFilesNames() const
	{
		return QStringList(getName().toLower().replace('.', '_'));
	}

	virtual void saveBinarySerialization( QDataStream& ) const;
	virtual void loadBinarySerialization( QDataStream& );

	virtual qint64 getExpectedSubjectID( SubjectInterface* subject ) const
	{
		return subjectsList.indexOf(subject);
	}

	virtual SubjectInterface* getSubjectByID( qint64 ID ) const
	{
		return subjectsList[ID];
	}

signals:
	void typeAdded( SubjectInterface* );
	void subjectAdded(); //TODO: Change signal name

public slots:
	void addType( SubjectInterface* );
	void store() const;
	void restore();

private:
	QList< SubjectInterface* > subjectsList;
	QTabWidget* centralWidget;
	QList< QMenu* > menusList;

private slots:
	void populate();
	void populateSubject( TypeInterface* );
	void dispatchTabClose( int );
};

class AddTypeButton : public QPushButton
{
Q_OBJECT
Q_DISABLE_COPY(AddTypeButton)

public:
	AddTypeButton( SubjectInterface* subject, const QString & text, QWidget *parent = 0 ) :
		QPushButton(text, parent), subject(subject)
	{
		connect(this, SIGNAL(clicked()), this, SLOT(click()));
	}

signals:
	void clicked( SubjectInterface* );

private slots:
	void click()
	{
		emit clicked(subject);
	}
private:
	SubjectInterface* subject;
};

class AddSubjectWidget : public QWidget
{
Q_OBJECT
Q_DISABLE_COPY(AddSubjectWidget)

	QLabel *label;
	QPushButton *button;
	QLineEdit *lineEdit;

	BasicDatabase* database;

public:
	AddSubjectWidget( BasicDatabase *database );

	void setF()
	{
		lineEdit->setFocus();
	}
private slots:
	void addSubject();
};

}

#endif /* BASICDATABASE_HXX_ */
