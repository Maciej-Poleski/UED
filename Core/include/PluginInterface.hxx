#ifndef PLUGININTERFACE_HXX
#define PLUGININTERFACE_HXX

#include <QtCore/QObject>
#include <QtCore/QString>

/** Interfejs obowiązkowy dla wszystkich plugin-ów. */
class PluginInterface
{
    public:
	virtual ~PluginInterface() {};
	
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
	virtual QStringList getLibraryFilesNames() const=0;
};

Q_DECLARE_INTERFACE(PluginInterface,"UED.core.PluginInterface/1.0")

#endif // PLUGININTERFACE_HXX