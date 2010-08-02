#include <QtCore/QtPlugin>
#include "Core.hxx"
#include <cstdio>
Q_IMPORT_PLUGIN(ued_basic_update_manager)

namespace Core
{
    #ifdef Q_OS_WIN32
    #define CORE_EXECUTABLE "Core.exe"
    #elif defined(Q_OS_UNIX)
    #define CORE_EXECUTABLE "Core"
    #endif

    static const char* NAME = "UED.Core"; ///< Unikalna nazwa plugin-u.
    static const char *FILES[ ] =
    { CORE_EXECUTABLE };
    /** Użyj QLibrary aby uzyskać właściwy prefiks i sufiks */
    static const char *LIBRARY[ ] =
    { };

    Core *core = 0;

    QStringList Core::getFilesNames() const
    {
	int s = sizeof ( FILES ) / QT_POINTER_SIZE;
	QStringList result;
	for( int i = 0 ; i < s ; ++i )
	{
	    result << FILES[i];
	}
	return result;
    }

    QStringList Core::getLibraryFilesNames() const
    {
	int s = sizeof ( LIBRARY ) / QT_POINTER_SIZE;
	QStringList result;
	for( int i = 0 ; i < s ; ++i )
	{
	    result << QLibrary(LIBRARY[i]).fileName();
	}
	return result;
    }

    void Core::uninstall()
    {
	updateManager->unregisterPlugin(this);
	core = 0; ///< Nie wiem czy ten kod zadziała. EDIT: powinien zadziałać
    }

    void Core::install()
    {
	core = this;
	loadPlugins();

	updateManager->registerPlugin(this); ///< Rejestruje główny moduł w menadżerze aktualizacji

	widget = new QPushButton("Aktualizacja");
	widget->show();
	connect(widget, SIGNAL(clicked()), this, SLOT(doUpdate()));
    }

    void Core::loadPlugins()
    {
	foreach(QObject *pluginInstance, QPluginLoader::staticInstances())
	{
	    PluginInterface* plugin =
	    qobject_cast< PluginInterface* > (pluginInstance);
	    if( plugin )
	    {
		plugin->install();
	    }
	    else
	    {
		// TODO Tutaj przydałby się wyjątek
	    }
	}
	// TODO Ładowanie pluginów dynamicznie linkowanych
    }

    Core::Core( int &argc, char**argv ) throw( Exception ) :
    QApplication(argc, argv)
    {
	if( core ) throw Exception(tr("Core already exist!"));
	networkAccessManager = new QNetworkAccessManager(this);
    }

    Core::~Core() throw()
    {
    }

    int Core::getVersion() const
    {
	return VERSION;
    }

    QString Core::getName() const
    {
	return NAME;
    }

    temporary void Core::doUpdate()
    {
	QList< PluginInterface* > needUpdate = updateManager->checkUpdates();
	if( needUpdate.isEmpty() ) return;
	QString
	message =
	QString::fromUtf8(
	"Dostępne są aktualizacje następujących modułów:\n");
	foreach(PluginInterface* plugin,needUpdate)
	    message += plugin->getName() + "\n";
	message += QString::fromUtf8("Instalować?");
	if( QMessageBox::information(widget,
	    QString::fromUtf8("Dostępne są aktualizacje"),
				     message, QMessageBox::Yes, QMessageBox::No)
	    == QMessageBox::Yes )
	{
	    //TODO Aktualizacja
	}
    }

}
