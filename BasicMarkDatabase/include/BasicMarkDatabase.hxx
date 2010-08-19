/*
 * BasicMarkDatabase.hxx
 *
 *  Created on: 17-08-2010
 *      Author: evil
 */

#ifndef BASICMARKDATABASE_HXX_
#define BASICMARKDATABASE_HXX_

#include <QtCore/QObject>
#include <PluginInterface.hxx>
#include <MarkDatabaseInterface.hxx>
#include <BinarySerializable.hxx>

#include <QtCore/QList>

#include <AbstractBasicMark.hxx>
#include <Exception.hxx>

namespace MarkDatabase
{

class MarksTabWidget;

class BasicMarkDatabase : public QObject,
						  public Core::PluginInterface,
						  public MarkDatabaseInterface,
						  public BinarySerializable
{
Q_OBJECT
Q_DISABLE_COPY(BasicMarkDatabase)Q_INTERFACES(Core::PluginInterface)

public:
	BasicMarkDatabase();
	virtual ~BasicMarkDatabase();

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

	virtual void addMark( MarkInterface* mark )
	{
		marksList << mark;
		emit markAdded(dynamic_cast< AbstractBasicMark* > (mark)); // Always working
	}

	virtual MarkInterface* getMark( EventInterface* event ) const
	{
		foreach(MarkInterface* mark,marksList)
				if( mark->getEvent() == event ) return mark;
		return 0;
	}

	virtual QList< MarkInterface* > getMarksList( QString subject ) const // This function is not supported.
	{
		throw Exception(tr("This function is not supported"));
	}
	virtual QList< MarkInterface* > getMarksList( QString subject, QString type ) const // This function is not supported.
	{
		throw Exception(tr("This function is not supported"));
	}
	virtual QList< MarkInterface* > getMarksList( SubjectInterface* subject ) const
	{
		QList< MarkInterface* > result;
		foreach(MarkInterface* mark, marksList)
				if( mark->getSubject() == subject ) result << mark;
		return result;
	}
	virtual QList< MarkInterface* > getMarksList( TypeInterface* type ) const
	{
		QList< MarkInterface* > result;
		foreach(MarkInterface* mark, marksList)
				if( mark->getType() == type ) result << mark;
		return result;
	}

	virtual int getExpectedID( MarkInterface* mark ) const
	{
		return marksList.indexOf(mark);
	}
	virtual MarkInterface* getMarkByID( int ID ) const
	{
		return marksList[ID];
	}

	virtual void saveBinarySerialization( QDataStream& ) const;
	virtual void loadBinarySerialization( QDataStream& );

signals:
	void markAdded( AbstractBasicMark* mark );

private:
	QList< MarkInterface* > marksList;
	MarksTabWidget* widget;
};

}

#endif /* BASICMARKDATABASE_HXX_ */
