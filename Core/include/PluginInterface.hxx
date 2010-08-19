#ifndef PLUGININTERFACE_HXX
#define PLUGININTERFACE_HXX

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QLibrary>

namespace Core
{

/** Interfejs obowiązkowy dla wszystkich plugin-ów. */
class PluginInterface
{
public:
	virtual ~PluginInterface()
	{
	}

public:
	/** Instaluje plugin, całokształt działalności */
	virtual void install()=0;

	/** Odinstalowuje plugin, całokształt działalności */
	virtual void uninstall()=0;

	/** Przeinstalowuje plugin, całokształt działalności */
	virtual void reinstall()
	{
		uninstall();
		install();
	}

	/** Zwraca numer wersji tego plugin-u. */
	virtual int getVersion() const=0;

	/** Zwraca unikalną nazwę tego plugin-u. */
	virtual QString getName() const=0;

	/** Zwraca listę nazw plików składowych tego plugin-u. */
	virtual QStringList getFilesNames() const=0;

	/** Zwraca listę nazw dynamicznie ładowanych bibliotek w postaci odpowidniej dla tej platformy. */
	virtual QStringList getLibraryFilesNames() const;

	/** Zwraca listę nazw dynamicznie ładowanych bibliotek w postaci niezależnej od platformy. */
	virtual QStringList getPureLibraryFilesNames() const=0;
};

inline QStringList PluginInterface::getLibraryFilesNames() const
{
	QStringList result;
	QStringList input = getPureLibraryFilesNames();
	foreach(QString name,input)
		{
			QLibrary library(qApp->applicationDirPath() + "/" + name); // FIXME Przetestować na windowsie.
			library.load();
			result << library.fileName();
			library.unload();
		}
	return result;
}

}

Q_DECLARE_INTERFACE(Core::PluginInterface,"UED.core.PluginInterface/1.0")

#endif // PLUGININTERFACE_HXX
