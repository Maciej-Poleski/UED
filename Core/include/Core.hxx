#ifndef CORE_H
#define CORE_H

#include <QtGui/QApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <PluginInterface.hxx>
#include <UpdateManagerInterface.hxx>
#include <Exception.hpp>

#ifdef Q_OS_UNIX
#ifndef DISABLE_FORK
#define ENABLE_FORK
#endif
#endif

#ifdef ENABLE_FORK
#include <unistd.h>
#endif

#include <QtGui/QtGui>

#define temporary                          ///< Oznacza rozwiązanie tymczasowe - wkrótce zostanie usunięte

namespace Core
{
    
    class Core;
    extern Core* core;
    
    
    /** Jądro UED. Może istnieć tylko jedna instancja tej klasy. Składa się między innymi z:
    *
    * - Numeru wersji
    * - Menadżera aktualizacji
    * - GUI
    * - Podstawowej bazy danych
    */
    class Core : public QApplication, public PluginInterface
    {
	Q_OBJECT
	Q_DISABLE_COPY ( Core )
	Q_INTERFACES ( PluginInterface )
	
	QWidget *widget;
	
	public:
	    Core ( int &argc, char**argv ) throw ( Exception );
	    ~Core() throw();
	    int run();
	    
	    virtual void uninstall();
	    virtual void install();
	    virtual int getVersion() const;
	    virtual QString getName() const;
	    virtual QStringList getFilesNames() const;
	    virtual QStringList getLibraryFilesNames() const;
	    
	    
	    /** Ustawia handlera do Menadżera aktualizacji. Używaj tylko jeżeli wiesz co robisz. */
	    void setUpdateManager(UpdateManagerInterface* updateManager)
	    {
		this->updateManager=updateManager;
	    }
	    
	    temporary QNetworkAccessManager* getNetworkAccessManager()
	    {
		return networkAccessManager;
	    }
	    
	public slots:
	    temporary void doUpdate();
	    
	private:
	    UpdateManagerInterface* updateManager;          ///< Menadżer aktualizacji, komponent obowiązkowy.
	    QNetworkAccessManager*  networkAccessManager;   ///< Menadżer dostępu do sieci. Co nieco do wydelegowania.
	    
	    /** Ładuje i instaluje plugin-y.
	    * @note TODO Wyjątki tej funkcji
	    */
	    void loadPlugins();
    };
    
    inline int Core::run()
    {
	#ifdef ENABLE_FORK
	if (fork()==0)
	    #endif
	    return exec();
	#ifdef ENABLE_FORK
	else
	    return 0;
	#endif
    }
    
}

#endif // CORE_H
