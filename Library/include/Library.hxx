/*
 * Library.hxx
 *
 *  Created on: 02-08-2010
 *      Author: evil
 */

#ifndef LIBRARY_HXX_
#define LIBRARY_HXX_

#include <QtCore/QObject>

#include <PluginInterface.hxx>

class Library : public QObject, public Core::PluginInterface
{
Q_OBJECT
Q_DISABLE_COPY(Library)
Q_INTERFACES(Core::PluginInterface)

public:
	Library( QObject *parent = 0 ) :
		QObject(parent)
	{
	}
	~Library()
	{
		uninstall();
	}

	virtual void install();
	virtual void uninstall();
	virtual int getVersion() const;
	virtual QString getName() const;
	virtual QStringList getFilesNames() const;
	virtual QStringList getPureLibraryFilesNames() const;

};

#endif /* LIBRARY_HXX_ */
