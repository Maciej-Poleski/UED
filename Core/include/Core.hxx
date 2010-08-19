#ifndef CORE_H
#define CORE_H

#include <QtGui/QApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <PluginInterface.hxx>
#include <UpdateManagerInterface.hxx>
#include <DatabaseInterface.hxx>
#include <MarkDatabaseInterface.hxx>
#include <EventDatabaseInterface.hxx>
#include <Exception.hxx>
#include <MainWindow.hxx>

#include <cstdio>

#ifdef Q_OS_WIN32
#define CORE_EXECUTABLE "Core.exe"
#elif defined(Q_OS_UNIX)
#define CORE_EXECUTABLE "Core"
#endif

#ifdef Q_OS_UNIX
#ifndef DISABLE_FORK
#define ENABLE_FORK
#endif
#endif

#ifdef ENABLE_FORK
#include <unistd.h>
#endif

/// Oznacza rozwiązanie tymczasowe - wkrótce zostanie usunięte
#define temporary
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
Q_DISABLE_COPY ( Core )Q_INTERFACES ( Core::PluginInterface )

public:
	Core( int &argc, char**argv ) throw( Exception );
	~Core() throw();
	int run();

	virtual void uninstall();
	virtual void install();
	virtual int getVersion() const;
	virtual QString getName() const;
	virtual QStringList getFilesNames() const;
	virtual QStringList getPureLibraryFilesNames() const;

	/** Ustawia handlera do Menadżera aktualizacji. Używaj tylko jeżeli wiesz co robisz. */
	void setUpdateManager( UpdateManagerInterface* updateManager )
	{
		this->updateManager = updateManager;
	}

	void setDatabase( DatabaseInterface* database )
	{
		this->database = database;
	}

	void setMarksDatabase( MarkDatabaseInterface* marksDatabase )
	{
		this->marksDatabase = marksDatabase;
	}

	void setEventsDatabase( EventDatabaseInterface* eventsDatabase )
	{
		this->eventsDatabase = eventsDatabase;
	}

	void setMainWindow( MainWindow* mainWindow )
	{
		this->mainWindow = mainWindow;
	}

	temporary
	DatabaseInterface* getDatabase() const
	{
		return database;
	}

	temporary
	MarkDatabaseInterface* getMarksDatabase() const
	{
		return marksDatabase;
	}

	temporary
	EventDatabaseInterface* getEventsDatabase() const
	{
		return eventsDatabase;
	}

	temporary
	QMainWindow* getMainWindow() const
	{
		return mainWindow;
	}

	temporary
	QNetworkAccessManager* getNetworkAccessManager()
	{
		return networkAccessManager;
	}

	temporary
	UpdateManagerInterface* getUpdateManager()
	{
		return updateManager;
	}

	temporary
	MainWindow* getMainWindow()
	{
		return mainWindow;
	}

	/** Ładuje i instaluje plugin-y.
	 * @note TODO Wyjątki tej funkcji
	 */
	void loadPlugins();

	temporary
	void deletePlugins()
	{
		delete database;
		database = 0;
	}

public slots:
	temporary
	void doUpdate();
	void about();

private:
	UpdateManagerInterface* updateManager; ///< Menadżer aktualizacji, komponent obowiązkowy.
	QNetworkAccessManager* networkAccessManager; ///< Menadżer dostępu do sieci. Co nieco do wydelegowania.
	DatabaseInterface* database; ///< Baza danych (CORE)
	MarkDatabaseInterface* marksDatabase; ///< Baza ocen
	EventDatabaseInterface* eventsDatabase; ///< Baza wydarzeń

	MainWindow *mainWindow; ///< Głowne okno aplikacji


	void initializeQt();
	void loadLocalization();
};

inline int Core::run()
{
#ifdef ENABLE_FORK
	if( fork() == 0 )
#endif
		return exec();
#ifdef ENABLE_FORK
	else
		return 0;
#endif
}

}

#endif // CORE_H
