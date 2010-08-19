/*
 * Library.cxx
 *
 *  Created on: 02-08-2010
 *      Author: evil
 */

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QLibrary>
#include <QtCore/QDir>
#include <QtCore/QtPlugin>

#include <Library.hxx>
#include <Core.hxx>

void Library::install()
{
	Core::core->getUpdateManager()->registerPlugin(this);
}

void Library::uninstall()
{
	Core::core->getUpdateManager()->unregisterPlugin(this);
}

int Library::getVersion() const
{
	return VERSION;
}

QString Library::getName() const
{
	return NAME;
}

QStringList Library::getFilesNames() const
{
	return QStringList();
}

QStringList Library::getPureLibraryFilesNames() const
{
	QStringList result;
	result << QString(NAME).toLower().replace('.', '_');
	return result;
}

Q_EXPORT_PLUGIN2(ued_library,Library)
