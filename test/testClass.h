/*
 * testClass.h
 *
 *  Created on: 30-08-2010
 *      Author: evil
 */

#ifndef TESTCLASS_H_
#define TESTCLASS_H_
#include <QtCore/QObject>
#include <PluginInterface.hxx>
#include <EventDatabaseInterface.hxx>
#include <BinarySerializable.hxx>

#include <QtCore/QList>

namespace EventDatabase
{

class TestClass : public QObject, public Core::PluginInterface
{
Q_OBJECT
Q_DISABLE_COPY(TestClass)Q_INTERFACES(Core::PluginInterface)

public:
	TestClass()
	{
	}
	virtual ~TestClass();

	virtual void install()
	{
	}
	virtual void uninstall()
	{
	}
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
};

}
using namespace EventDatabase;

#endif /* TESTCLASS_H_ */
